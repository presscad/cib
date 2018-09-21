#include "cib.h"
#include "cibcompound.h"
#include "cibfunction.h"
#include "cibfunction_helper.h"
#include "cibhelper.h"
#include "cibidmgr.h"
#include "cibutil.h"
#include "cppwriter.h"

#include "boost-helper/bfs.h"

//////////////////////////////////////////////////////////////////////////

static CppWriter gCppWriter;

inline void emitType(std::ostream&         stm,
                     const CppVarType*     typeObj,
                     const CibCppCompound* typeResolver,
                     const CibHelper&      helper,
                     EmitPurpose           purpose)
{
  if (typeObj == nullptr)
    return;
  // FIXME: We are assuming that all types will be of some sort of compound object.
  // This will break when there will be some typedefed or enum type is used.
  auto* resolvedCppObj = (typeResolver ? typeResolver->resolveTypeName(typeObj->baseType(), helper) : nullptr);
  auto* resolvedType =
    resolvedCppObj && resolvedCppObj->isClassLike() ? static_cast<const CibCppCompound*>(resolvedCppObj) : nullptr;

  bool isConst    = typeObj->typeAttr_ & kConst;
  bool emitHandle = resolvedType
                    && ((purpose == kProxyProcTypeParam) || (purpose == kProxyProcTypeReturn)
                        || (purpose == kProxyCApiParam) || (purpose == kProxyCApiReturn));
  bool byValToPtr = resolvedType && (purpose & kPurposeGlueCode) && typeObj->isByValue();
  if (byValToPtr && !emitHandle)
    isConst = true;

  if (isConst)
    stm << "const ";
  if (resolvedType != nullptr)
  {
    if (emitHandle)
    {
      stm << "__zz_cib_HANDLE";
    }
    else if (purpose & kPurposeGlueCode)
    {
      stm << resolvedType->longName();
    }
    else
    {
      // TODO: For proxy classes we should emit types as they apear.
      // stm << typeObj->baseType();
      stm << resolvedType->longName();
    }
  }
  else
  {
    if (resolvedCppObj)
    {
      stm << longName(resolvedCppObj);
    }
    else
    {
      stm << typeObj->baseType();
    }
  }
  for (unsigned short i = 0; i < typeObj->ptrLevel(); ++i)
    stm << '*';
  if (typeObj->refType() == kByRef)
  {
    stm << '&';
  }
  else if (typeObj->refType() == kRValRef)
  {
    if (emitHandle)
      stm << '&';
    else
      stm << "&&";
  }
  if (byValToPtr)
    stm << '*';
}

inline void emitParamName(std::ostream& stm, const CppVar* var, size_t paramName, bool makeNameIfMissing = true)
{
  if (!var->name().empty())
  {
    stm << var->name();
  }
  else if (makeNameIfMissing)
  { // Parameter name is missing. Provide our own.
    stm << "__zz_cib_param" << paramName;
  }
}

void CibFunctionHelper::emitArgsForDecl(std::ostream&    stm,
                                        const CibHelper& helper,
                                        bool             resolveTypes,
                                        EmitPurpose      purpose) const
{
  // FIXME for function pointer type params, it currently handles only functions whose parameter is
  // not function-pointer type.

  if (!hasParams())
    return;
  const CibCppCompound* typeResolver = resolveTypes ? getOwner() : nullptr;
  auto                  params       = getParams();
  const char*           sep          = "";
  for (size_t i = 0; i < params->size(); ++i)
  {
    const auto& param = params->at(i);
    stm << sep;
    emitType(stm, param.varObj->varType_, typeResolver, helper, purpose);
    stm << ' ';
    emitParamName(stm, param.varObj, i, (purpose & (kPurposeGlueCode | kPurposeProxyMethodImpl)));
    sep = ", ";
  }
}

void CibFunctionHelper::emitArgsForCall(std::ostream&    stm,
                                        const CibHelper& helper,
                                        const CibParams& cibParams,
                                        CallType         callType) const
{
  // FIXME for function pointer type params, it currently handles only functions whose parameter is
  // not function-pointer type.

  if (!hasParams())
    return;
  const auto* params = getParams();

  for (size_t i = 0; i < params->size(); ++i)
  {
    const auto& param = params->at(i);
    if (params->front() != param)
      stm << ", ";
    // FIXME for enum and other non compound types.
    auto* resolvedCppObj = getOwner()->resolveTypeName(param.varObj->baseType(), helper);
    auto* resolvedType =
      resolvedCppObj && resolvedCppObj->isClassLike() ? static_cast<const CibCppCompound*>(resolvedCppObj) : nullptr;
    if (resolvedType)
    {
      switch (callType)
      {
        case CallType::kFromHandle:
          stm << cibParams.cibInternalNamespace << resolvedType->longName()
              << "::__zz_cib_Helper::__zz_cib_from_handle(";
          emitParamName(stm, param.varObj, i);
          stm << ")";
          break;
        case CallType::kToHandle:
          if (param.varObj->isByRef() || param.varObj->isByRValueRef())
            stm << '*';
          stm << cibParams.cibInternalNamespace << resolvedType->longName() << "::__zz_cib_Helper::__zz_cib_handle(";
          emitParamName(stm, param.varObj, i);
          stm << ")";
          break;
        case CallType::kDerefIfByVal:
          if (param.varObj->isByValue())
            stm << '*';
          emitParamName(stm, param.varObj, i);
          break;
        case CallType::kAsIs:
          emitParamName(stm, param.varObj, i);
          break;
      }
    }
    else
    {
      emitParamName(stm, param.varObj, i);
    }
  }
}

void CibFunctionHelper::emitSignature(std::ostream& stm, const CibHelper& helper, EmitPurpose purpose) const
{
  if (isFunction() && func_->retType_)
  {
    emitType(stm, func_->retType_, getOwner(), helper, purpose);
    stm << ' ';
  }
  stm << funcName() << '(';
  emitArgsForDecl(stm, helper, true, purpose);
  stm << ')';
  if (isConst())
    stm << " const";
}

void CibFunctionHelper::emitOrigDecl(std::ostream&    stm,
                                     const CibHelper& helper,
                                     const CibParams& cibParams,
                                     CppIndent        indentation /* = CppIndent */) const
{
  stm << indentation;
  if (isStatic())
    stm << "static ";
  else if (isVirtual())
    stm << "virtual ";
  else if (isInline())
    stm << "inline ";
  emitSignature(stm, helper);
  if (isPureVirtual())
    stm << " = 0";
  stm << ";\n";
}

void CibFunctionHelper::emitCAPIDefn(std::ostream&      stm,
                                     const CibHelper&   helper,
                                     const CibParams&   cibParams,
                                     const std::string& capiName,
                                     bool               forProxy,
                                     CppIndent          indentation /* = CppIndent */) const
{
  if (forProxy && !isVirtual() && !isDestructor())
    return;
  if (!forProxy)
  {
    if (isConstructorLike() && getOwner()->isAbstract() && !getOwner()->needsUnknownProxyDefinition())
      return;
  }
  auto callType = forProxy ? CallType::kFromHandle : CallType::kDerefIfByVal;
  stm << indentation << "static ";
  if (isConstructor())
    stm << getOwner()->longName() << "*";
  else if (isDestructor())
    stm << "void";
  else
    emitType(stm, func_->retType_, getOwner(), helper, forProxy ? kProxyMethodReturn : kCApiReturn);
  stm << " __zz_cib_decl ";
  stm << capiName << '(';
  if (isConstructor() && getOwner()->needsUnknownProxyDefinition())
  {
    stm << "__zz_cib_PROXY* proxy, __zz_cib_MethodTable mtbl";
    if (hasParams())
      stm << ", ";
  }
  else if (!isStatic() && (isMethod() || isDestructor()))
  {
    if (isConst())
      stm << "const ";
    stm << getOwner()->longName() << "* __zz_cib_obj";
    if (hasParams())
      stm << ", ";
  }
  emitArgsForDecl(stm, helper, true, forProxy ? kProxyCApiParam : kCApiParam);
  stm << ") {\n";
  stm << ++indentation;
  if (isConstructor())
  {
    stm << "return new ";
    if (getOwner()->needsUnknownProxyDefinition())
    {
      stm << "__zz_cib_" << getOwner()->longName() << "::__zz_cib_UnknownProxy::" << getOwner()->name()
          << "(proxy, mtbl";
      if (hasParams())
        stm << ", ";
    }
    else
    {
      stm << getOwner()->longName();
      stm << '(';
    }
    emitArgsForCall(stm, helper, cibParams, callType);
    stm << ");\n";
  }
  else if (isDestructor())
  {
    stm << "delete __zz_cib_obj;\n";
  }
  else
  {
    bool convertFromValue = false;
    if (func_->retType_ && !func_->retType_->isVoid())
    {
      stm << "return ";
      if (func_->retType_->isByValue())
      {
        auto* resolvedCppObj = getOwner()->resolveTypeName(func_->retType_->baseType(), helper);
        auto* resolvedType   = resolvedCppObj && resolvedCppObj->isClassLike()
                               ? static_cast<const CibCppCompound*>(resolvedCppObj)
                               : nullptr;
        convertFromValue = (resolvedType != nullptr);
        if (convertFromValue)
        {
          auto retTypeCompound = static_cast<const CppCompound*>(resolvedType);
          stm << "new ::" << retTypeCompound->fullName() << '(';
        }
      }
    }
    if (!isStatic())
      stm << "__zz_cib_obj->";
    if (!forProxy && !isPureVirtual())
      stm << getOwner()->longName() << "::";
    stm << funcName();
    stm << '(';
    emitArgsForCall(stm, helper, cibParams, callType);
    if (convertFromValue)
      stm << ')';
    stm << ");\n";
  }
  stm << --indentation << "}\n";
}

void CibFunctionHelper::emitUnknownProxyDefn(std::ostream&      stm,
                                             const CibHelper&   helper,
                                             const CibParams&   cibParams,
                                             const std::string& capiName,
                                             CppIndent          indentation /* = CppIndent */) const
{
  if (isVirtual())
  {
    stm << indentation;
    emitSignature(stm, helper, kUnknownProxyProcTypeParam);
    stm << " override";
    stm << " {\n";
    ++indentation;
    if (isDestructor())
    {
      stm << indentation << "if (__zz_cib_proxy) {\n";
      ++indentation;
    }
    emitProcType(stm, helper, cibParams, true, indentation);
    stm << indentation << "auto proc = getProc<" << procType(cibParams) << ">(";
    stm << "__zz_cib_" << getOwner()->longName() << "::__zz_cib_UnknownProxy::__zz_cib_methodid::";
    stm << capiName << ");\n";
    stm << indentation;
    if (!isDestructor())
      stm << "return ";
    stm << "proc(";
    stm << "__zz_cib_proxy";
    if (hasParams())
      stm << ", ";
    emitArgsForCall(stm, helper, cibParams, CallType::kAsIs);
    stm << ");\n";
    if (isDestructor())
    {
      --indentation;
      stm << indentation << "}\n";
    }
    stm << --indentation << "}\n";
  }
  else if (isConstructor())
  {
    stm << indentation << funcName() << "(__zz_cib_PROXY* proxy, __zz_cib_MethodTable mtbl";
    if (hasParams())
      stm << ", ";
    emitArgsForDecl(stm, helper, true, kUnknownProxyMethodParam);
    stm << ")\n";
    ++indentation;
    stm << indentation << ": " << getOwner()->longName() << "::" << funcName() << '(';
    emitArgsForCall(stm, helper, cibParams, CallType::kAsIs);
    stm << ")\n";
    stm << indentation << ", __zz_cib_proxy(proxy)\n";
    stm << indentation << ", __zz_cib_mtbl(mtbl)\n";
    --indentation;
    stm << indentation << "{}\n";
  }
}

void CibFunctionHelper::emitProcType(std::ostream&    stm,
                                     const CibHelper& helper,
                                     const CibParams& cibParams,
                                     bool             forUnknownProxy,
                                     CppIndent        indentation /* = CppIndent */) const
{
  stm << indentation;
  stm << "using " << procType(cibParams) << " = ";
  emitCAPIReturnType(stm, helper, forUnknownProxy);
  stm << " (__zz_cib_decl *) (";
  if (!isStatic() && (isDestructor() || isMethod()))
  {
    if (forUnknownProxy)
      stm << "__zz_cib_PROXY*";
    else
      stm << "__zz_cib_HANDLE*";
    if (hasParams())
      stm << ", ";
  }
  else if (isConstructor() && !forUnknownProxy && getOwner()->needsUnknownProxyDefinition())
  {
    stm << getOwner()->longName() << "*, __zz_cib_MethodTable";
    if (hasParams())
      stm << ", ";
  }
  emitArgsForDecl(stm, helper, true, forUnknownProxy ? kUnknownProxyProcTypeParam : kProxyProcTypeParam);
  stm << ");\n";
}

void CibFunctionHelper::emitCAPIReturnType(std::ostream&    stm,
                                           const CibHelper& helper,
                                           bool             forUnknownProxy,
                                           CppIndent        indentation /* = CppIndent */) const
{
  stm << indentation;
  if (isConstructor())
    stm << "__zz_cib_HANDLE*";
  else if (isDestructor())
    stm << "void";
  else
    emitType(stm, func_->retType_, getOwner(), helper, forUnknownProxy ? kUnknownProxyReturn : kProxyProcTypeReturn);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stm, CppDocComment* cmnt)
{
  stm << cmnt->doc_;
  return stm;
}

void emitInheritanceList(std::ostream& stm, const CibCppCompoundArray& inhList, CppObjProtLevel prot, char& sep)
{
  if (inhList.empty())
    return;
  stm << ' ' << sep << ' ' << prot << ' ' << inhList.front()->longName();
  sep = ',';
  for (CibCppCompoundArray::const_iterator itr = inhList.begin() + 1; itr != inhList.end(); ++itr)
    stm << sep << prot << ' ' << (*itr)->longName();
}

const CppObj* CibCppCompound::resolveTypeName(const std::string& typeName, const CibHelper& helper) const
{
  auto itr = typeNameToCibCppObj_.find(typeName);
  if (itr != typeNameToCibCppObj_.end())
    return itr->second;
  const CppObj* resolvedType     = helper.getCppObjFromTypeName(typeName, this);
  typeNameToCibCppObj_[typeName] = resolvedType;
  return resolvedType;
}

void CibCppCompound::emitUserHeader(const CibHelper& helper, const CibParams& cibParams) const
{
  if (!isCppFile())
    return;

  bfs::path     usrIncPath = cibParams.outputPath / name().substr(cibParams.inputPath.string().length());
  std::ofstream stm(usrIncPath.string(), std::ios_base::out);

  auto firstStatementItr      = std::find_if(members_.begin(), members_.end(), [](const CppObj* mem) -> bool {
    return (mem->objType_ > kCppStatementObjectTypeStarts);
  });
  auto lastPreProcessorRevItr = std::find_if(std::reverse_iterator<decltype(firstStatementItr)>(firstStatementItr),
                                             members_.rend(),
                                             [](const CppObj* mem) -> bool { return (mem->isPreProcessorType()); });
  auto memItr                 = members_.begin();
  if (lastPreProcessorRevItr != members_.rend())
  {
    std::for_each(memItr, lastPreProcessorRevItr.base(), [&stm](const CppObj* mem) { gCppWriter.emit(mem, stm); });
    memItr = lastPreProcessorRevItr.base();

    stm << "\n";
  }

  stm << "#include \"" << implIncludeName(cibParams) << "-predef.h\"\n\n";
  for (; memItr != members_.end(); ++memItr)
  {
    emitDecl(*memItr, stm, helper, cibParams);
  }
  stm << "\n#include \"" << implIncludeName(cibParams) << "-impl.h\"\n";
}

void CibCppCompound::emitPredefHeader(const CibHelper& helper, const CibParams& cibParams) const
{
  if (!isCppFile())
    return;

  auto          implPath = cibParams.outputPath / (getImplPath(cibParams) + "-predef.h");
  std::ofstream stm(implPath.string(), std::ios_base::out);

  stm << "#include \"" << cibParams.cibInternalDirName << "/" << cibParams.cibdefFileName << "\"\n";

  emitHelperDecl(stm, helper, cibParams);
}

void CibCppCompound::emitImplHeader(const CibHelper& helper, const CibParams& cibParams, const CibIdMgr& cibIdMgr) const
{
  if (!isCppFile())
    return;
  auto          implPath = cibParams.outputPath / (getImplPath(cibParams) + "-impl.h");
  std::ofstream stm(implPath.string(), std::ios_base::out);
  stm << "#include \"" << cibParams.cibIdFilename() << "\"\n";
  stm << "#include \"" << cibParams.helperFileName << "\"\n";
  emitHelperDefn(stm, helper, cibParams, cibIdMgr);
  emitDefn(stm, helper, cibParams, cibIdMgr);
}

void CibCppCompound::emitImplSource(std::ostream&    stm,
                                    const CibHelper& helper,
                                    const CibParams& cibParams,
                                    const CibIdMgr&  cibIdMgr,
                                    CppIndent        indentation) const
{
  auto cibIdData = cibIdMgr.getCibIdData(longName() + "::__zz_cib_UnknownProxy");
  for (auto mem : members_)
  {
    if (mem->isNamespaceLike() && isMemberPublic(mem->prot_, compoundType_))
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      compound->emitImplSource(stm, helper, cibParams, cibIdMgr);
    }
  }

  if (isFacadeLike())
    emitFromHandleDefn(stm, cibParams, cibIdMgr, indentation);
  if (needsUnknownProxyDefinition())
  {
    stm << indentation << wrappingNamespaceDeclarations(cibParams) << " namespace " << name() << " {\n";
    ++indentation;
    for (auto func : needsBridging_)
    {
      if (func.isVirtual())
        func.emitCAPIDefn(stm, helper, cibParams, cibIdData->getMethodCApiName(func.signature()), true, indentation);
    }
    --indentation;
    stm << indentation << '}' << closingBracesForWrappingNamespaces() << "\n\n";
    emitMethodTableGetterDefn(stm, helper, cibParams, cibIdMgr, true, indentation);
    stm << '\n';
    stm << indentation << wrappingNamespaceDeclarations(cibParams) << " namespace " << name() << " {\n";
    ++indentation;
    stm << indentation << "__zz_cib_MethodTable "
        << "__zz_cib_Helper::__zz_cib_get_proxy_method_table() {\n";
    ++indentation;
    stm << indentation << "return __zz_cib_GetMethodTable();\n";
    --indentation;
    stm << indentation << "}\n";
    --indentation;
    stm << indentation << '}' << closingBracesForWrappingNamespaces() << "\n\n";
  }
}

void CibCppCompound::emitImplSource(const CibHelper& helper, const CibParams& cibParams, const CibIdMgr& cibIdMgr) const
{
  if (!isCppFile())
    return;
  bfs::path headerPath = name_;
  bfs::path usrSrcPath = cibParams.outputPath / name_.substr(cibParams.inputPath.string().length());
  usrSrcPath.replace_extension(".cpp");
  std::ofstream stm(usrSrcPath.string(), std::ios_base::out);

  emitFacadeDependecyHeaders(stm, helper, cibParams, cibIdMgr, true, CppIndent());
  emitImplSource(stm, helper, cibParams, cibIdMgr);
}

void CibCppCompound::collectFacades(std::set<const CibCppCompound*>& facades) const
{
  for (auto mem : members_)
  {
    if (!isMemberPublic(mem->prot_, compoundType_))
      continue;
    if (mem->isNamespaceLike())
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      compound->collectFacades(facades);
      if (compound->isFacadeLike())
        facades.insert(compound);
    }
  }
}

void CibCppCompound::collectTypeDependencies(const CibHelper& helper, std::set<const CppObj*>& cppObjs) const
{
  for (auto mem : members_)
  {
    if (!isMemberPublic(mem->prot_, compoundType_))
      continue;
    if (mem->isNamespaceLike())
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      compound->collectTypeDependencies(helper, cppObjs);
    }
    else if (mem->isFunctionLike())
    {
      auto addDependency = [&](const std::string& typeName) {
        auto* resolvedCppObj = resolveTypeName(typeName, helper);
        auto* resolvedType   = resolvedCppObj && resolvedCppObj->isClassLike()
                               ? static_cast<const CibCppCompound*>(resolvedCppObj)
                               : nullptr;
        if (resolvedType)
          cppObjs.insert(resolvedType);
      };
      CibFunctionHelper func(mem);
      if (func.retType() && !func.retType()->isVoid())
        addDependency(func.retType()->baseType());
      if (func.hasParams())
      {
        for (auto param : *func.getParams())
        {
          if (param.cppObj->objType_ == kVarType)
            addDependency(param.varObj->baseType());
        }
      }
    }
  }
}

std::set<std::string> CibCppCompound::collectHeaderDependencies(const CibHelper& helper) const
{
  std::set<const CppObj*> cppObjs;
  collectTypeDependencies(helper, cppObjs);
  bfs::path path = getFileDomObj(this)->name();
  return collectHeaderDependencies(cppObjs, path.parent_path().string());
}

const CibCppCompound* CibCppCompound::getFileDomObj(const CppObj* obj)
{
  const CppCompound* parent = obj->objType_ == kCompound ? static_cast<const CppCompound*>(obj) : obj->owner_;
  while (parent->owner_)
    parent = parent->owner_;
  return static_cast<const CibCppCompound*>(parent);
}

std::set<std::string> CibCppCompound::collectHeaderDependencies(const std::set<const CppObj*>& cppObjs,
                                                                const std::string&             dependentPath)
{
  std::set<std::string> headers;
  std::string           parentPath = bfs::path(dependentPath).parent_path().string();

  for (auto obj : cppObjs)
  {
    auto fileDom = getFileDomObj(obj);
    headers.emplace(fileDom->name().substr(parentPath.length() + 1));
  }
  return headers;
}

std::string CibCppCompound::getImplPath(const CibParams& cibParams) const
{
  bfs::path impl         = name();
  auto      implFilename = impl.stem().string();
  impl.remove_filename();
  impl /= implFilename;
  return (bfs::path(cibParams.cibInternalDirName) / bfs::relative(impl, cibParams.inputPath)).string();
}

std::string CibCppCompound::implIncludeName(const CibParams& cibParams) const
{
  auto implIncludeName = getImplPath(cibParams);
  std::replace(implIncludeName.begin(), implIncludeName.end(), '\\', '/');

  return implIncludeName;
}

void CibCppCompound::emitDecl(const CppObj*    obj,
                              std::ostream&    stm,
                              const CibHelper& helper,
                              const CibParams& cibParams,
                              CppIndent        indentation /* = CppIndent */) const
{
  if (obj->isFunctionLike())
  {
    if (objNeedingBridge_.count(obj))
    {
      CibFunctionHelper func = obj;
      func.emitOrigDecl(stm, helper, cibParams, indentation);
    }
    return;
  }
  if (obj->objType_ == CppObj::kCompound)
  {
    auto compound = static_cast<const CibCppCompound*>(obj);
    compound->emitDecl(stm, helper, cibParams, indentation);
  }
  else
  {
    gCppWriter.emit(obj, stm);
  }
}

void CibCppCompound::emitDecl(std::ostream&    stm,
                              const CibHelper& helper,
                              const CibParams& cibParams,
                              CppIndent        indentation /* = CppIndent */) const
{
  if (isInline())
  {
    gCppWriter.emit(this, stm, indentation);
    return;
  }
  if (isNamespaceLike())
  {
    stm << indentation;
    stm << compoundType_;
    stm << ' ' << name();
    if (isClassLike())
    {
      auto emitInheritance = [this, &stm](CppObjProtLevel prot, char& sep) {
        auto itr = parents_.find(prot);
        if (itr != parents_.end())
          emitInheritanceList(stm, itr->second, prot, sep);
      };
      char sep = ':';
      emitInheritance(kPublic, sep);
      if (isInline())
      {
        emitInheritance(kProtected, sep);
        emitInheritance(kPrivate, sep);
      }
    }
    stm << '\n' << indentation++ << "{\n";
  }

  if (isClassLike() && !isInline() && !needsBridging_.empty())
    emitMoveConstructorDecl(stm, indentation);

  CppObjProtLevel         lastProt = kUnknownProt;
  std::set<const CppObj*> memDeclared;
  for (auto mem : members_)
  {
    if (!isInline()
        && !isMemberPublic(mem->prot_, compoundType_)) // We will emit only public members unless class is inline.
      continue;
    if (isClassLike() && lastProt != mem->prot_)
    {
      if (mem->prot_ != kUnknownProt)
        stm << --indentation << mem->prot_ << ":\n";
      ++indentation;
      lastProt = mem->prot_;
    }
    emitDecl(mem, stm, helper, cibParams, indentation);
    memDeclared.insert(mem);
  }
  for (auto func : needsBridging_)
  {
    if (memDeclared.count(func))
      continue;
    if (func.protectionLevel() != lastProt)
    {
      stm << --indentation << func.protectionLevel() << ":\n";
      ++indentation;
    }
    func.emitOrigDecl(stm, helper, cibParams, indentation);
  }

  if (isClassLike())
  {
    if (!isInline())
    {
      // Everything below this is for glue code
      stm << '\n';
      stm << --indentation << "private:\n";
      stm << ++indentation << "__ZZ_CIB_CLASS_INTERNAL_DEF(" << name() << ", " << fullName() << ");\n";
    }
    stm << --indentation << "};\n";
  }
  else if (isNamespaceLike())
  {
    stm << --indentation << "}\n";
  }
}

void CibCppCompound::emitFromHandleDefn(std::ostream&    stm,
                                        const CibParams& cibParams,
                                        const CibIdMgr&  cibIdMgr,
                                        CppIndent        indentation) const
{
  stm << indentation << longName() << "* __zz_cib_" << longName()
      << "::__zz_cib_Helper::__zz_cib_from_handle(__zz_cib_HANDLE* h) {\n";
  ;
  ++indentation;
  stm << indentation << "switch(__zz_cib_get_class_id(h)) {\n";
  forEachDescendent(kPublic, [&](const CibCppCompound* derived) {
    auto cibIdData = cibIdMgr.getCibIdData(derived->longName());
    if (cibIdData)
    {
      stm << indentation << "case __zz_cib_"
          << "::__zz_cib_classid::" << cibIdData->getIdName() << ":\n";
      ++indentation;
      stm << indentation << "return __zz_cib_" << derived->longName()
          << "::__zz_cib_Helper::__zz_cib_from_handle(h);\n";
      --indentation;
    }
  });
  stm << indentation << "}\n";
  stm << indentation << "return nullptr;\n";
  --indentation;
  stm << indentation << "}\n";
}

void CibCppCompound::emitFromHandleDecl(std::ostream& stm, const CibParams& cibParams, CppIndent indentation) const
{
  if (!isFacadeLike() && isAbstract())
    return;
  stm << indentation << "static " << longName() << "* " << cibParams.fromHandle << "(__zz_cib_HANDLE* h)";
  if (isFacadeLike())
  {
    // For Facade classes definition of fromHandle() will be more elaborative.
    // So, it will be defined in cpp file.
    stm << ";\n";
  }
  else if (!isAbstract())
  {
    stm << " {\n";
    ++indentation;
    stm << indentation << "return new " << longName() << "(h);\n";
    --indentation;
    stm << indentation << "}\n";
  }

  // Emit __zz_cib_from_handle() definition for references.
  stm << indentation << longName() << "& __zz_cib_from_handle(__zz_cib_HANDLE& h) {\n";
  ;
  stm << ++indentation << "return *__zz_cib_from_handle(&h);\n";
  stm << --indentation << "}\n";
  // Emit methods for const handle ptr and ref.
  stm << indentation << longName() << " const * __zz_cib_from_handle(const __zz_cib_HANDLE* h) {\n";
  ;
  stm << ++indentation << "return __zz_cib_from_handle(const_cast<__zz_cib_HANDLE*>(h));\n";
  stm << --indentation << "}\n";
  stm << indentation << longName() << " const & __zz_cib_from_handle(const __zz_cib_HANDLE& h) {\n";
  ;
  stm << ++indentation << "return *__zz_cib_from_handle(const_cast<__zz_cib_HANDLE*>(&h));\n";
  stm << --indentation << "}\n";
}

void CibCppCompound::identifyMethodsToBridge()
{
  if (templSpec_)
    return;
  if (name().empty())
    return;
  for (auto mem : members_)
  {
    if (mem->isFunctionLike())
    {
      CibFunctionHelper func(mem);
      if (func.isDestructor())
        setHasDtor();
      else if (func.isCopyConstructor())
        setHasCopyCtor();
      else if (func.isMoveConstructor())
        continue;
      else if (func.isConstructor())
        setHasCtor();
      if (func.funcName().find(':') != std::string::npos)
        continue; // Skip out of class definitions.
      if (func.isTemplated())
        continue;
      if (!isInline()
          && !isMemberPublic(mem->prot_, compoundType_)) // We will emit only public members unless class is inline.
        continue;
      if (isInline()) // If class is inline
      {
        if (func.isStatic() && !func.isInline()) // only non-inline static methods need bridging.
        {
          needsBridging_.push_back(func);
          objNeedingBridge_.insert(mem);
        }
      }
      else
      {
        if (func.isConstructorLike() && isAbstract() && !needsUnknownProxyDefinition())
          continue;
        if (func.isPureVirtual() && !needsUnknownProxyDefinition() && !func.isDestructor())
          continue;
        if (func.hasVariadicParam())
          continue;
        needsBridging_.push_back(func);
        objNeedingBridge_.insert(mem);
      }
    }
    else if (mem->isNamespaceLike())
    {
      if (!isInline()
          && !isMemberPublic(mem->prot_, compoundType_)) // We will emit only public members unless class is inline.
        continue;
      auto compound = static_cast<CibCppCompound*>(mem);
      compound->identifyMethodsToBridge();
    }
  }
  if (!isClassLike())
    return;
  if (!hasCtor() && (!isAbstract() || needsUnknownProxyDefinition()))
  {
    auto ctorProtection = isAbstract() ? kProtected : kPublic;
    auto defaultCtor    = CibFunctionHelper::CreateConstructor(ctorProtection, name(), nullptr, nullptr, 0);
    defaultCtor->owner_ = this;
    addMember(defaultCtor);
    CibFunctionHelper func(defaultCtor);
    needsBridging_.push_back(func);
    objNeedingBridge_.insert(defaultCtor);
  }
  if (!hasDtor() && (!isAbstract() || needsUnknownProxyDefinition()))
  {
    auto defaultDtor    = CibFunctionHelper::CreateDestructor(kPublic, "~" + name(), 0);
    defaultDtor->owner_ = this;
    addMember(defaultDtor);
    CibFunctionHelper func(defaultDtor);
    needsBridging_.push_back(func);
    objNeedingBridge_.insert(defaultDtor);
  }
}

void CibCppCompound::emitHelperDecl(std::ostream&    stm,
                                    const CibHelper& helper,
                                    const CibParams& cibParams,
                                    CppIndent        indentation /* = CppIndent */) const
{
  if (isNamespaceLike() && !needsBridging_.empty())
  {
    stm << '\n'; // Start in new line.
    if (!wrappingNamespaceDeclarations(cibParams).empty())
      stm << indentation << wrappingNamespaceDeclarations(cibParams);
    stm << " namespace " << name() << " {\n";
    stm << ++indentation << "class __zz_cib_Helper;\n";
    stm << --indentation << "}";
    if (!wrappingNamespaceDeclarations(cibParams).empty())
      stm << indentation << closingBracesForWrappingNamespaces() << '\n';
  }

  for (auto mem : members_)
  {
    if (mem->isNamespaceLike())
      static_cast<const CibCppCompound*>(mem)->emitHelperDecl(stm, helper, cibParams);
  }
}

void CibCppCompound::emitHelperDefn(std::ostream&    stm,
                                    const CibHelper& helper,
                                    const CibParams& cibParams,
                                    const CibIdMgr&  cibIdMgr,
                                    CppIndent        indentation /* = CppIndent */) const
{
  if (isNamespaceLike() && !needsBridging_.empty())
  {
    stm << '\n'; // Start in new line.
    stm << indentation << wrappingNamespaceDeclarations(cibParams) << " namespace " << name() << " {\n";
    stm << ++indentation << "class __zz_cib_Helper : public __zz_cib_::__zz_cib_Helper {\n";
    stm << indentation << "private:\n";
    stm << ++indentation << "friend " << compoundType_ << ' ' << longName() << ";\n";
    if (needsUnknownProxyDefinition())
      stm << indentation << "static __zz_cib_MethodTable __zz_cib_get_proxy_method_table();\n";
    stm << '\n'; // Start in new line.
    auto cibIdData = cibIdMgr.getCibIdData(longName());
    for (auto func : needsBridging_)
    {
      if (func.isPureVirtual() && !func.isDestructor())
        continue;
      stm << indentation << "static ";
      func.emitCAPIReturnType(stm, helper, false);
      stm << ' ' << cibIdData->getMethodCApiName(func.signature()) << "(";
      if (!func.isStatic() && (!func.isConstructor() || func.isCopyConstructor()))
      {
        stm << "__zz_cib_HANDLE* __zz_cib_obj";
        if (func.hasParams())
          stm << ", ";
      }
      else if (needsUnknownProxyDefinition() && func.isConstructor())
      {
        stm << longName() << "* __zz_cib_proxy";
        if (func.hasParams())
          stm << ", ";
      }
      func.emitArgsForDecl(stm, helper, true, kProxyProcTypeParam);
      stm << ") {\n";
      ++indentation;
      if (func.isDestructor())
      {
        stm << indentation << "if (__zz_cib_obj) {\n";
        ++indentation;
      }
      func.emitProcType(stm, helper, cibParams, false, indentation);
      stm << indentation << "auto proc = instance().getProc<" << func.procType(cibParams) << ">(";
      stm << "__zz_cib_" << longName() << "::__zz_cib_methodid::";
      stm << cibIdData->getMethodCApiName(func.signature()) << ");\n";
      stm << indentation << "return proc(";
      if (!func.isStatic() && (!func.isConstructor() || func.isCopyConstructor()))
      {
        stm << "__zz_cib_obj";
        if (func.hasParams())
          stm << ", ";
      }
      else if (needsUnknownProxyDefinition() && func.isConstructor())
      {
        stm << "__zz_cib_proxy, __zz_cib_get_proxy_method_table()";
        if (func.hasParams())
          stm << ", ";
      }
      func.emitArgsForCall(stm, helper, cibParams, CallType::kAsIs);
      stm << ");\n";
      if (func.isDestructor())
      {
        --indentation;
        stm << indentation << "}\n";
      }
      stm << --indentation << "}\n";
    }
    forEachAncestor(kPublic, [&](const CibCppCompound* pubParent) {
      auto castProcName = castToBaseName(pubParent, cibParams);
      auto capiName     = cibIdData->getMethodCApiName(castProcName);
      stm << indentation << "static __zz_cib_HANDLE* " << capiName << "(__zz_cib_HANDLE* __zz_cib_obj) {\n";
      stm << ++indentation << "using " << castProcName
          << "Proc = __zz_cib_HANDLE* (__zz_cib_decl *) (__zz_cib_HANDLE* h);\n";
      stm << indentation << "auto proc = instance().getProc<" << castProcName << "Proc>(";
      stm << "__zz_cib_" << longName() << "::__zz_cib_methodid::";
      stm << capiName << ");\n";
      stm << indentation << "return proc(__zz_cib_obj);\n";
      stm << --indentation << "}\n";
    });
    if (!needsBridging_.empty())
    {
      stm << indentation << "__zz_cib_Helper()\n";
      stm << ++indentation << ": __zz_cib_::__zz_cib_Helper(\n";
      stm << ++indentation << "__zz_cib_" << cibParams.moduleName << "_GetMethodTable(\n";
      stm << ++indentation;
      auto classIdName = longName();
      std::transform(
        classIdName.begin(), classIdName.end(), classIdName.begin(), [](char c) -> char { return c == ':' ? '_' : c; });
      stm << cibParams.classIdOwnerSpace() << classIdName << ")) {}\n";
      --indentation;
      --indentation;
      stm << --indentation << "static const __zz_cib_Helper& instance() {\n";
      stm << ++indentation << "static __zz_cib_Helper helper;\n";
      stm << indentation << "return helper;\n";
      stm << --indentation << "}\n";
    }
    stm << '\n'; // Start in new line.
    if (isFacadeLike())
    {
      stm << indentation << "static std::uint32_t __zz_cib_get_class_id(__zz_cib_HANDLE* __zz_cib_obj) {\n";
      stm << ++indentation
          << "using __zz_cib_get_class_idProc = std::uint32_t (__zz_cib_decl *) "
             "(__zz_cib_HANDLE*);\n";
      stm << indentation << "auto proc = instance().getProc<__zz_cib_get_class_idProc>(";
      stm << "__zz_cib_" << longName()
          << "::__zz_cib_methodid::" << cibIdData->getMethodCApiName("__zz_cib_get_class_id") << ");\n";
      stm << indentation << "return proc(__zz_cib_obj);\n";
      stm << --indentation << "}\n";
    }
    stm << --indentation << "public:\n";
    stm << ++indentation << "static __zz_cib_HANDLE* __zz_cib_handle(const " << longName() << "* __zz_cib_obj) {\n";
    stm << ++indentation << "return __zz_cib_obj->__zz_cib_h_;\n";
    stm << --indentation << "}\n";
    stm << indentation << "static __zz_cib_HANDLE* __zz_cib_handle(const " << longName() << "& __zz_cib_obj) {\n";
    stm << ++indentation << "return __zz_cib_obj.__zz_cib_h_;\n";
    stm << --indentation << "}\n";
    emitFromHandleDecl(stm, cibParams, indentation);
    stm << indentation << "static __zz_cib_HANDLE* __zz_cib_release_handle(" << longName() << "* __zz_cib_obj) {\n";
    ++indentation;
    stm << indentation << "auto h = __zz_cib_obj->__zz_cib_h_;\n";
    stm << indentation << "__zz_cib_obj->__zz_cib_h_ = nullptr;\n";
    forEachParent(kPublic, [&stm, &indentation](const CibCppCompound* baseCompound) {
      stm << indentation << "__zz_cib_" << baseCompound->longName()
          << "::__zz_cib_Helper::__zz_cib_release_handle(__zz_cib_obj);\n";
    });
    stm << indentation << "return h;\n";
    stm << --indentation << "}\n";
    if (needsUnknownProxyDefinition())
    {
      stm << indentation << "static void __zz_cib_release_proxy(" << longName() << "* __zz_cib_obj) {\n";
      ++indentation;
      stm << indentation << "if (__zz_cib_obj->__zz_cib_h_) {\n";
      ++indentation;
      stm << indentation << "using __zz_cib_release_proxyProc = void (__zz_cib_decl *) (__zz_cib_HANDLE*);\n";
      stm << indentation << "auto proc = instance().getProc<__zz_cib_release_proxyProc>(";
      stm << "__zz_cib_" << longName()
          << "::__zz_cib_methodid::" << cibIdData->getMethodCApiName("__zz_cib_release_proxy") << ");\n";
      stm << indentation << "proc(__zz_cib_obj->__zz_cib_h_);\n";
      stm << --indentation << "}\n";
      stm << --indentation << "}\n";
    }
    stm << --indentation << "};\n";

    stm << --indentation << closingBracesForWrappingNamespaces() << "}\n";
  }

  for (auto mem : members_)
  {
    if (mem->isNamespaceLike())
      static_cast<const CibCppCompound*>(mem)->emitHelperDefn(stm, helper, cibParams, cibIdMgr);
  }
}

void CibCppCompound::emitHandleConstructorDefn(std::ostream&    stm,
                                               const CibHelper& helper,
                                               const CibParams& cibParams,
                                               const CibIdMgr&  cibIdMgr,
                                               CppIndent        indentation /* = CppIndent */) const
{
  auto cibIdData = cibIdMgr.getCibIdData(longName());

  stm << '\n'; // Start in new line.
  stm << indentation << "inline " << fullName() << "::" << name() << "(__zz_cib_::__zz_cib_HANDLE* h)\n";
  ++indentation;
  char sep = ':';
  forEachParent(kPublic, [&](const CibCppCompound* pubParent) {
    auto capiName = cibIdData->getMethodCApiName(castToBaseName(pubParent, cibParams));
    stm << indentation << sep << ' ' << pubParent->longName() << "::" << pubParent->name() << "(__zz_cib_" << longName()
        << "::__zz_cib_Helper::" << capiName << "(h))\n";
    sep = ',';
  });
  stm << indentation << sep << " __zz_cib_h_(h)";
  stm << --indentation << "\n{}\n";
}

void CibCppCompound::emitMoveConstructorDecl(std::ostream& stm, CppIndent indentation /* = CppIndent */) const
{
  stm << --indentation << "public:\n";
  stm << ++indentation << name() << '(' << name() << "&& rhs);\n";
}

void CibCppCompound::emitMoveConstructorDefn(std::ostream&    stm,
                                             const CibHelper& helper,
                                             const CibParams& cibParams,
                                             const CibIdMgr&  cibIdMgr,
                                             CppIndent        indentation /* = CppIndent */) const
{
  auto cibIdData = cibIdMgr.getCibIdData(longName());

  stm << '\n'; // Start in new line.
  stm << indentation << "inline " << fullName() << "::" << name() << '(' << name() << "&& rhs)\n";
  ++indentation;
  char sep = ':';
  forEachParent(kPublic, [&](const CibCppCompound* pubParent) {
    auto capiName = cibIdData->getMethodCApiName(castToBaseName(pubParent, cibParams));
    stm << indentation << sep << ' ' << pubParent->longName() << "::" << pubParent->name() << "(std::move(rhs))\n";
    sep = ',';
  });
  stm << indentation << sep << " __zz_cib_h_(rhs.__zz_cib_h_)";
  stm << --indentation << "\n{\n";
  stm << ++indentation << "rhs.__zz_cib_h_ = nullptr;\n";
  stm << --indentation << "}\n";
}

void CibCppCompound::emitDefn(std::ostream&    stm,
                              const CibHelper& helper,
                              const CibParams& cibParams,
                              const CibIdMgr&  cibIdMgr,
                              CppIndent        indentation /* = CppIndent */) const
{
  for (CppObjArray::const_iterator memItr = members_.begin(); memItr != members_.end(); ++memItr)
  {
    CppObj* mem = *memItr;
    if (mem->objType_ == CppObj::kCompound)
      static_cast<CibCppCompound*>(mem)->emitDefn(stm, helper, cibParams, cibIdMgr, indentation);
  }

  auto cibIdData = cibIdMgr.getCibIdData(longName());
  if (isClassLike() && !needsBridging_.empty())
  {
    // Emit the ctor to construct from __zz_cib_HANDLE.
    emitHandleConstructorDefn(stm, helper, cibParams, cibIdMgr, indentation);
    emitMoveConstructorDefn(stm, helper, cibParams, cibIdMgr, indentation);
  }
  for (auto func : needsBridging_)
  {
    if (func.isPureVirtual() && !func.isDestructor())
      continue;
    stm << '\n'; // Start in new line.
    stm << indentation << "inline ";
    if (func.isFunction())
    {
      emitType(stm, func.retType(), this, helper, kProxyMethodReturn);
      stm << ' ';
    }
    stm << fullName() << "::" << func.funcName() << '(';
    func.emitArgsForDecl(stm, helper, true, kProxyMethodImplParam);
    stm << ")";
    auto capiName = cibIdData->getMethodCApiName(func.signature());
    if (func.isConstructor())
    {
      stm << '\n';
      stm << ++indentation << ": " << name() << "(__zz_cib_" << longName() << "::__zz_cib_Helper::" << capiName << '(';
      if (needsUnknownProxyDefinition())
      {
        stm << "this";
        if (func.hasParams())
          stm << ", ";
      }
      func.emitArgsForCall(stm, helper, cibParams, CallType::kToHandle);
      stm << "))\n";
      stm << --indentation << "{}\n";
    }
    else
    {
      if (func.isConst())
      {
        stm << " const";
      }
      stm << " {\n";
      ++indentation;
      if (func.isDestructor())
      {
        if (needsUnknownProxyDefinition())
        {
          stm << indentation << "__zz_cib_" << longName() << "::__zz_cib_Helper::__zz_cib_release_proxy(this);\n";
        }
        stm << indentation << "auto h = __zz_cib_" << longName()
            << "::__zz_cib_Helper::__zz_cib_release_handle(this);\n";
      }

      stm << indentation;
      const CibCppCompound* retType = nullptr;
      if (func.isFunction() && func.retType() && !func.retType()->isVoid())
      {
        stm << "return ";
        auto* resolvedCppObj = resolveTypeName(func.retType()->baseType(), helper);
        retType = resolvedCppObj && resolvedCppObj->isClassLike() ? static_cast<const CibCppCompound*>(resolvedCppObj)
                                                                  : nullptr;
        if (retType)
        {
          if (func.retType()->isByValue())
          {
            stm << retType->longName() << "(\n";
          }
          else
          {
            stm << "__zz_cib_" << retType->longName() << "::__zz_cib_Helper::__zz_cib_from_handle(\n";
          }
          stm << ++indentation;
        }
      }
      stm << "__zz_cib_" << longName() << "::__zz_cib_Helper::" << capiName << "(";
      if (func.isDestructor())
      {
        stm << "h";
      }
      else if (!func.isStatic())
      {
        stm << "__zz_cib_h_";
        if (func.hasParams())
          stm << ", ";
      }
      func.emitArgsForCall(stm, helper, cibParams, CallType::kToHandle);
      stm << ')';
      if (retType)
        stm << '\n' << --indentation << ")";
      stm << ";\n";
      stm << --indentation << "}\n";
    }
  }
}

void CibCppCompound::emitUnknownProxyDefn(std::ostream&    stm,
                                          const CibHelper& helper,
                                          const CibParams& cibParams,
                                          const CibIdMgr&  cibIdMgr,
                                          CppIndent        indentation) const
{
  if (!needsUnknownProxyDefinition())
    return;

  stm << indentation++ << wrappingNamespaceDeclarations(cibParams) << " namespace " << name()
      << " { namespace __zz_cib_UnknownProxy {\n";
  stm << indentation << "class " << name() << " : public " << longName() << " {\n";
  ++indentation;
  stm << indentation << "__zz_cib_PROXY* __zz_cib_proxy;\n";
  stm << indentation << "__zz_cib_MethodTable __zz_cib_mtbl;\n\n";
  stm << indentation << "template<typename _ProcType> _ProcType getProc(std::uint32_t procId) const {\n";
  stm << ++indentation << "return reinterpret_cast<_ProcType>(__zz_cib_GetMethodEntry(__zz_cib_mtbl, procId));\n";
  stm << --indentation << "}\n";
  --indentation;
  stm << indentation << "public:\n";
  ++indentation;
  for (auto func : needsBridging_)
  {
    auto cibIdData = cibIdMgr.getCibIdData(longName() + "::__zz_cib_UnknownProxy");
    func.emitUnknownProxyDefn(stm, helper, cibParams, cibIdData->getMethodCApiName(func.signature()), indentation);
  }
  stm << indentation << "void __zz_cib_release_proxy() { __zz_cib_proxy = nullptr; }\n";
  --indentation;
  stm << indentation << "};\n";
  stm << --indentation << closingBracesForWrappingNamespaces() << "}}\n";
}

void CibCppCompound::emitFacadeDependecyHeaders(std::ostream&    stm,
                                                const CibHelper& helper,
                                                const CibParams& cibParams,
                                                const CibIdMgr&  cibIdMgr,
                                                bool             forProxy,
                                                CppIndent        indentation /* = CppIndent */) const
{
  std::set<const CibCppCompound*> facades;
  collectFacades(facades);
  std::set<const CppObj*> dependencies;
  collectTypeDependencies(helper, dependencies);
  dependencies.insert(this);
  for (auto facade : facades)
  {
    dependencies.insert(facade);
    facade->forEachDescendent(kPublic, [&dependencies](const CibCppCompound* obj) { dependencies.insert(obj); });
  }
  for (const auto& header : collectHeaderDependencies(dependencies, getFileDomObj(this)->name()))
    stm << indentation << "#include \"" << header << "\"\n";
  stm << '\n'; // Start in new line.
  if (!facades.empty() && !forProxy)
  {
    // Assuming there is a facade like class in this file
    stm << "#include <typeinfo>\n";
    stm << "#include <typeindex>\n";
    stm << "#include <cstdint>\n";
    stm << "#include <unordered_map>\n\n";
    stm << "extern std::unordered_map<std::type_index, std::uint32_t> __zz_cib_gClassIdRepo;\n\n";
  }
}

void CibCppCompound::emitLibGlueCode(std::ostream&    stm,
                                     const CibHelper& helper,
                                     const CibParams& cibParams,
                                     const CibIdMgr&  cibIdMgr,
                                     CppIndent        indentation /* = CppIndent */) const
{
  if (isCppFile())
  {
    stm << "#include \"__zz_cib_" << cibParams.moduleName << ".h\"\n";
    emitFacadeDependecyHeaders(stm, helper, cibParams, cibIdMgr, false, indentation);
  }
  for (CppObjArray::const_iterator memItr = members_.begin(); memItr != members_.end(); ++memItr)
  {
    CppObj* mem = *memItr;
    if (mem->objType_ == CppObj::kCompound)
    {
      static_cast<CibCppCompound*>(mem)->emitLibGlueCode(stm, helper, cibParams, cibIdMgr, indentation);
    }
  }
  auto cibIdData = cibIdMgr.getCibIdData(longName());
  if (isNamespaceLike() && !needsBridging_.empty())
  {
    if (needsUnknownProxyDefinition())
      emitUnknownProxyDefn(stm, helper, cibParams, cibIdMgr, indentation);
    stm << indentation++ << wrappingNamespaceDeclarations(cibParams) << " namespace " << name() << " {\n";
    for (auto func : needsBridging_)
    {
      func.emitCAPIDefn(stm, helper, cibParams, cibIdData->getMethodCApiName(func.signature()), false, indentation);
    }

    forEachAncestor(kPublic, [&](const CibCppCompound* pubParent) {
      auto castApiName = castToBaseName(pubParent, cibParams);
      stm << indentation << pubParent->longName() << "* __zz_cib_decl " << cibIdData->getMethodCApiName(castApiName)
          << "(" << longName() << "* __zz_cib_obj) {\n";
      stm << ++indentation << "return __zz_cib_obj;\n";
      stm << --indentation << "}\n";
    });

    if (isFacadeLike())
    {
      stm << indentation << "std::uint32_t __zz_cib_decl " << cibIdData->getMethodCApiName("__zz_cib_get_class_id")
          << "(" << longName() << "* __zz_cib_obj) {\n";
      ++indentation;
      stm << indentation << "static bool classIdRepoPopulated = false;\n";
      stm << indentation << "if (!classIdRepoPopulated) {\n";
      ++indentation;
      forEachDescendent(kPublic, [&](const CibCppCompound* compound) {
        auto cibIdData = cibIdMgr.getCibIdData(compound->longName());
        if (cibIdData)
        {
          stm << indentation << "__zz_cib_gClassIdRepo[std::type_index(typeid(" << compound->longName() << "))] = ";
          stm << " __zz_cib_"
              << "::__zz_cib_classid::" << cibIdData->getIdName() << ";\n";
        }
      });
      stm << indentation << "classIdRepoPopulated = true;\n";
      --indentation;
      stm << indentation << "}\n";
      stm << indentation << "return __zz_cib_gClassIdRepo[std::type_index(typeid(*__zz_cib_obj))];\n";
      stm << --indentation << "}\n";
    }
    if (needsUnknownProxyDefinition())
    {
      stm << indentation << "void __zz_cib_decl " << cibIdData->getMethodCApiName("__zz_cib_release_proxy") << "("
          << longName() << "* __zz_cib_obj) {\n";
      ++indentation;
      stm << indentation << "auto unknownProxy = dynamic_cast<__zz_cib_" << longName()
          << "::__zz_cib_UnknownProxy::" << name() << "*>(__zz_cib_obj);\n";
      stm << indentation << "if (unknownProxy)\n";
      ++indentation;
      stm << indentation << "unknownProxy->__zz_cib_release_proxy();\n";
      --indentation;
      --indentation;
      stm << indentation << "}\n";
    }
    stm << --indentation << closingBracesForWrappingNamespaces() << "}\n\n";
  }
}

void CibCppCompound::collectPublicCompounds(std::vector<const CibCppCompound*>& compounds) const
{
  for (auto mem : members_)
  {
    if (!mem->isNamespaceLike())
      continue;
    auto compound = static_cast<const CibCppCompound*>(mem);
    if (!isMemberPublic(mem->prot_, compoundType_))
      continue;
    compound->collectPublicCompounds(compounds);
  }
  if (isNamespaceLike() && !needsBridging_.empty())
  {
    compounds.push_back(this);
  }
}

void CibCppCompound::emitMethodTableGetterDefn(std::ostream&    stm,
                                               const CibHelper& helper,
                                               const CibParams& cibParams,
                                               const CibIdMgr&  cibIdMgr,
                                               bool             forProxy,
                                               CppIndent        indentation /* = CppIndent */) const
{
  for (CppObjArray::const_iterator memItr = members_.begin(); memItr != members_.end(); ++memItr)
  {
    CppObj* mem = *memItr;
    if (mem->objType_ == CppObj::kCompound)
      static_cast<CibCppCompound*>(mem)->emitMethodTableGetterDefn(
        stm, helper, cibParams, cibIdMgr, forProxy, indentation);
  }
  if (isNamespaceLike() && !needsBridging_.empty())
  {
    stm << indentation << wrappingNamespaceDeclarations(cibParams) << " namespace " << name() << " {\n";
    stm << ++indentation;
    if (forProxy)
      stm << "static ";
    stm << "__zz_cib_MethodTable __zz_cib_GetMethodTable() {\n";
    const auto& className = forProxy ? longName() + "::__zz_cib_UnknownProxy" : longName();
    stm << ++indentation
        << "static const __zz_cib_MethodTableHeader tableHeader = { sizeof(__zz_cib_MethodTableHeader), "
        << cibIdMgr.numMethods(className) << " };\n";
    stm << indentation << "static const __zz_cib_MethodEntry methodTable[] = {\n";
    stm << ++indentation << "reinterpret_cast<__zz_cib_MethodEntry> (&tableHeader)";
    CibMethodId nextMethodId = 1;
    nextMethodId             = cibIdMgr.forEachMethod(
      className, [&](CibMethodId methodId, const CibMethodCAPIName& methodName, const CibMethodSignature& methodSig) {
        if (methodId == nextMethodId++)
        {
          stm << ",\n" << indentation << "reinterpret_cast<__zz_cib_MethodEntry> (&" << methodName << ')';
        }
        else
        {
          stm << ",\n" << indentation << "reinterpret_cast<__zz_cib_MethodEntry> (nullptr)";
        }
      });
    stm << '\n';
    stm << --indentation << "};\n";
    stm << indentation << "return methodTable;\n";
    stm << --indentation << "}\n";
    stm << --indentation << '}' << closingBracesForWrappingNamespaces() << '\n';
  }
}
