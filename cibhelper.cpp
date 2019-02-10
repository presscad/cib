/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "cibhelper.h"
#include "cibcompound.h"
#include "cibfunction.h"
#include "cibfunction_helper.h"
#include "cibidmgr.h"
#include "cibobjfactory.h"
#include "cibutil.h"
#include "cppparser.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

CibHelper::CibHelper(const char* inputPath, CibIdMgr& cibIdMgr)
  : cibCppObjTreeCreated_(false)
  , cibIdMgr_(cibIdMgr)
{
  CibObjFactory objFactory;
  program_.reset(CppParser(&objFactory).loadProgram(inputPath));
  buildCibCppObjTree();
}

void CibHelper::onNewCompound(CibCppCompound* compound, const CibCppCompound* parent) const
{
  program_->addCompound(compound, parent);
  auto* pThis = const_cast<CibHelper*>(this); // TODO: Fix const_cast.
  pThis->markClassType(compound);
}

CppObj* CibHelper::resolveVarType(CppVarType* varType, const CppTypeTreeNode* typeNode)
{
  normalizeConst(varType);
  auto* cppObj = resolveTypename(varType->baseType(), typeNode);
  if (cppObj == nullptr)
    return nullptr;
  if (cppObj->objType_ == CppObj::kTypedefName)
  {
    // TODO: We need to resolve typedefs fully only if it resolves to conpound object uniquely.
    // For cases when typedef uses non-compound types we need to know ptr and ref only.
    auto* typedefObj       = static_cast<CppTypedefName*>(cppObj);
    auto* finalResolvedObj = resolveTypename(typedefObj->var_->baseType(), typeNode);
    if (finalResolvedObj && finalResolvedObj->isClassLike())
    {
      varType->typeModifier_.ptrLevel_ += typedefObj->var_->ptrLevel();
      if (typedefObj->var_->refType() != kNoRef)
        varType->typeModifier_.refType_ = typedefObj->var_->refType();
      varType->baseType_ = typedefObj->var_->baseType();
      return finalResolvedObj;
    }
  }

  return cppObj;
}

CppObj* CibHelper::resolveTypename(const std::string& name, const CppCompound* begScope) const
{
  return resolveTypename(name, program_->typeTreeNodeFromCppObj(begScope));
}

CppObj* CibHelper::resolveVarType(CppVarType* varType, const CppCompound* begScope)
{
  return resolveVarType(varType, program_->typeTreeNodeFromCppObj(begScope));
}

void CibHelper::buildCibCppObjTree()
{
  for (auto fileDom : program_->getFileDOMs())
    resolveInheritance(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    markClassType(static_cast<CibCppCompound*>(fileDom));
  // In some cases detecting facades need detection of interfaces.
  // so just call markClassType() again for all classes to correctly detect all facades.
  for (auto fileDom : program_->getFileDOMs())
    markClassType(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    identifyAbstract(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    identifyPobableFacades(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    markNeedsGenericProxyDefinition(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    static_cast<CibCppCompound*>(fileDom)->identifyMethodsToBridge(*this);
}

CppObj* CibHelper::resolveTypename(const std::string& name, const CppTypeTreeNode* startNode) const
{
  auto templateArgStart = name.find('<');
  auto typeNode         = [&]() {
    if (templateArgStart == name.npos)
    {
      return program_->findTypeNode(name, startNode);
    }
    else
    {
      auto classNameEnd = templateArgStart;
      while (isspace(name[--classNameEnd]))
        ;
      ++classNameEnd;
      return program_->findTypeNode(name.substr(0, classNameEnd), startNode);
    }
  }();

  // TODO: Fix const_cast.
  auto* cppObj =
    typeNode && !typeNode->cppObjSet.empty() ? const_cast<CppObj*>(*(typeNode->cppObjSet.begin())) : nullptr;
  if (cppObj)
  {
    if (cppObj->isClassLike())
    {
      if (templateArgStart != name.npos)
      {
        auto* compound           = static_cast<CibCppCompound*>(cppObj);
        auto* instantiationScope = static_cast<const CibCppCompound*>(*(startNode->cppObjSet.begin()));
        return compound->getTemplateInstantiation(name, instantiationScope, *this);
      }
    }
  }

  return cppObj;
}

void CibHelper::resolveInheritance(CibCppCompound* cppCompound)
{
  const CppTypeTreeNode& ownerTypeNode = *program_->typeTreeNodeFromCppObj(cppCompound);
  if (cppCompound->inheritList_)
  {
    for (const auto& inh : *(cppCompound->inheritList_))
    {
      // TODO: We will have to consider protected inheritance too.
      if (inh.inhType != kPublic)
        continue;
      auto* cppObj    = resolveTypename(inh.baseName, &ownerTypeNode);
      auto* parentObj = cppObj && cppObj->isClassLike() ? static_cast<CibCppCompound*>(cppObj) : nullptr;
      // assert(parentObj != nullptr); // we should actually give warning
      // here.
      if (parentObj == nullptr)
        continue;
      CppObjProtLevel inhType = resolveInheritanceType(inh.inhType, cppCompound->compoundType_);
      cppCompound->parents_[inhType].push_back(parentObj);
      parentObj->children_[inhType].push_back(cppCompound);
    }
  }
  for (const auto mem : cppCompound->members_)
  {
    if (mem->objType_ == CppObj::kCompound)
      resolveInheritance((CibCppCompound*) mem);
  }
}

void CibHelper::evaluateArgs(const CibFunctionHelper& func)
{
  if (func.isTemplated())
    return;
  // Evaluate the arguments to detect properties of class.
  if (func.hasParams())
  {
    for (auto& param : *(func.getParams()))
    {
      if (param.cppObj->objType_ != CppObj::kVar)
        continue; // TODO: FIXME param can be function pointer too.
      auto* cppObj   = resolveVarType(param.varObj->varType_, func.getOwner());
      auto* paramObj = cppObj && cppObj->isClassLike() ? static_cast<CibCppCompound*>(cppObj) : nullptr;
      if (!paramObj)
        continue;
      paramObj->setShared();
      auto effectivePtrLevel = param.varObj->ptrLevel();
      if (param.varObj->refType() == kByRef)
        ++effectivePtrLevel;
      if (effectivePtrLevel)
      {
        if (paramObj && paramObj->hasPublicVirtualMethod())
        {
          paramObj->setInterfaceLike();
          if ((effectivePtrLevel >= 2 || (func.getOwner()->isInterfaceLike() && func.isVirtual())))
            paramObj->setFacadeLike();
        }
      }
    }
  }
}
void CibHelper::evaluateReturnType(const CibFunctionHelper& func)
{
  if (func.isTemplated())
    return;
  if (func.returnType())
  {
    auto* cppObj    = resolveVarType(func.returnType(), func.getOwner());
    auto* returnObj = cppObj && cppObj->isClassLike() ? static_cast<CibCppCompound*>(cppObj) : nullptr;
    if (!returnObj)
      return;
    returnObj->setShared();

    if ((func.returnType()->ptrLevel() == 1) || (func.returnType()->refType() == kByRef))
    {
      if (returnObj->hasPublicVirtualMethod())
      {
        returnObj->setFacadeLike();
        if (func.getOwner()->isInterfaceLike())
          returnObj->setInterfaceLike();
      }
    }
    else
    {
      normalizeConst(func.returnType());
    }
  }
}

void CibHelper::markClassType(CibCppCompound* cppCompound)
{
  if (cppCompound->isTemplated())
  {
    cppCompound->setIsInline();
    return;
  }
  auto isInline    = true;
  auto isEmpty     = true;
  auto isPodStruct = (cppCompound->isStruct() || cppCompound->isUnion());
  for (auto mem : cppCompound->members_)
  {
    if (isPodStruct && !isMemberPublic(mem->protectionLevel(), cppCompound->compoundType_))
      isPodStruct = false;
    if (mem->objType_ == CppObj::kCompound)
    {
      isPodStruct  = false;
      auto* nested = static_cast<CibCppCompound*>(mem);
      markClassType(nested);
      if (isPodStruct)
        isPodStruct = nested->isPodStruct();
    }
    else if (mem->isFunctionLike())
    {
      isPodStruct = false;
      CibFunctionHelper func(mem);
      if (!func.hasDefinition() || func.isVirtual())
        isInline = false;
      evaluateArgs(mem);
      evaluateReturnType(mem);
      if (!(func.getAttr() & kStatic))
        isEmpty = false;
    }
    else if (mem->objType_ == CppObj::kVar)
    {
      const CppVar* var = static_cast<const CppVar*>(mem);
      if (!(var->varType_->typeAttr_ & kStatic))
        isEmpty = false;
      if (isPodStruct)
      {
        auto* cppObj = resolveVarType(var->varType_, cppCompound);
        if (cppObj && cppObj->isClassLike())
          isPodStruct = false;
      }
    }
  }
  isInline = isInline || (cppCompound->templSpec_ != nullptr);
  if (isInline && cppCompound->isClassLike())
    cppCompound->setIsInline();
  if (isEmpty && cppCompound->isClassLike())
    cppCompound->setEmpty();
  if (isPodStruct && cppCompound->templSpec_ == nullptr)
    cppCompound->setPodStruct();
}

void CibHelper::setNeedsGenericProxyDefinition(CibCppCompound* cppCompound)
{
  // TODO: Considers private ctors too.
  // Also for protected ctor/dtor things will be slightly less trivial.
  if (!cppCompound->hasDtor() || !isMemberPrivate(cppCompound->dtor()->protectionLevel(), cppCompound->compoundType_))
    cppCompound->setNeedsGenericProxyDefinition();
}

void CibHelper::markNeedsGenericProxyDefinition(CibCppCompound* cppCompound)
{
  for (auto mem : cppCompound->members_)
  {
    if (mem->objType_ == CppObj::kCompound)
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      markNeedsGenericProxyDefinition(compound);
      if (compound->isInterfaceLike())
      {
        setNeedsGenericProxyDefinition(compound);
      }
    }
  }
}

void CibHelper::identifyAbstract(CibCppCompound* cppCompound)
{
  for (auto mem : cppCompound->members_)
  {
    if (mem->objType_ == CppObj::kCompound)
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      identifyAbstract(compound);
      compound->identifyAbstract(*this);
    }
  }
}

void CibHelper::identifyPobableFacades(CibCppCompound* cppCompound)
{
  for (auto mem : cppCompound->members_)
  {
    if (mem->objType_ == CppObj::kCompound)
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      identifyPobableFacades(compound);
      if (!compound->isFacadeLike() && compound->isAbstract())
      {
        compound->forEachAncestor([compound](const CibCppCompound* ancestor) {
          if (ancestor->isFacadeLike())
            compound->setFacadeLike();
          return ancestor->isFacadeLike();
        });
      }
    }
  }
}
