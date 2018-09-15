#include "cibhelper.h"
#include "cibcompound.h"
#include "cibfunction.h"
#include "cibfunction_helper.h"
#include "cibobjfactory.h"
#include "cibutil.h"
#include "cppparser.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

CibHelper::CibHelper(const char* inputPath)
  : cibCppObjTreeCreated_(false)
{
  CibObjFactory objFactory;
  program_.reset(CppParser(&objFactory).loadProgram(inputPath));
  buildCibCppObjTree();
}

CppObj* CibHelper::getCppObjFromTypeName(const std::string& name, const CppCompound* begScope) const
{
  return getCppObjFromTypeName(name, program_->typeTreeNodeFromCppObj(begScope));
}

void CibHelper::buildCibCppObjTree()
{
  for (auto fileDom : program_->getFileDOMs())
    resolveInheritance(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    markClassType(static_cast<CibCppCompound*>(fileDom));
  // detecting facades need detection of interfaces.
  // so just call markClassType() again for all classes to correctly detect all facades.
  for (auto fileDom : program_->getFileDOMs())
    markClassType(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    markNeedsUnknownProxyDefinition(static_cast<CibCppCompound*>(fileDom));
  for (auto fileDom : program_->getFileDOMs())
    static_cast<CibCppCompound*>(fileDom)->identifyMethodsToBridge();
}

CppObj* CibHelper::getCppObjFromTypeName(const std::string& name, const CppTypeTreeNode* typeNode) const
{
  typeNode = program_->findTypeNode(name, typeNode);
  return typeNode && !typeNode->cppObjSet.empty() ? *(typeNode->cppObjSet.begin()) : nullptr;
}

void CibHelper::resolveInheritance(CibCppCompound* cppCompound)
{
  const CppTypeTreeNode& ownerTypeNode = *program_->typeTreeNodeFromCppObj(cppCompound->owner_);
  if (cppCompound->inheritList_)
  {
    for (const auto& inh : *(cppCompound->inheritList_))
    {
      auto* cppObj    = getCppObjFromTypeName(inh.baseName, &ownerTypeNode);
      auto* parentObj = cppObj && cppObj->isClassLike() ? static_cast<CibCppCompound*>(cppObj) : nullptr;
      // assert(parentObj != NULL); // we should actually give warning
      // here.
      if (parentObj == NULL)
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
  // Evaluate the arguments to detect properties of class.
  if (func.hasParams())
  {
    for (auto& param : *(func.getParams()))
    {
      if (param.cppObj->objType_ != CppObj::kVar)
        continue; // TODO: FIXME param can be function pointer too.
      auto* cppObj   = getCppObjFromTypeName(param.varObj->baseType(), func.getOwner());
      auto* paramObj = cppObj && cppObj->isClassLike() ? static_cast<CibCppCompound*>(cppObj) : nullptr;
      if (!paramObj)
        continue;
      paramObj->setShared();
      auto effectivePtrLevel = param.varObj->ptrLevel();
      if (param.varObj->refType() == kByRef)
        ++effectivePtrLevel;
      if (effectivePtrLevel)
      {
        if (paramObj && paramObj->hasVirtualMethod())
        {
          paramObj->setInterfaceLike();
          if ((effectivePtrLevel >= 2 || (func.getOwner()->isInterfaceLike() && func.isVirtual()))
              && paramObj->hasPubliclyDerived())
            paramObj->setFacadeLike();
        }
      }
    }
  }
}
void CibHelper::evaluateReturnType(const CibFunctionHelper& func)
{
  if (func.retType())
  {
    if (func.retType()->ptrLevel() == 1 || func.retType()->refType() == kByRef)
    {
      auto* cppObj    = getCppObjFromTypeName(func.retType()->baseType(), func.getOwner());
      auto* returnObj = cppObj && cppObj->isClassLike() ? static_cast<CibCppCompound*>(cppObj) : nullptr;
      if (!returnObj)
        return;
      returnObj->setShared();
      if (returnObj->hasVirtualMethod() && returnObj->hasPubliclyDerived())
      {
        returnObj->setFacadeLike();
      }
    }
  }
}

void CibHelper::markClassType(CibCppCompound* cppCompound)
{
  auto isInline = true;
  for (auto mem : cppCompound->members_)
  {
    if (mem->objType_ == CppObj::kCompound)
    {
      markClassType(static_cast<CibCppCompound*>(mem));
    }
    else if (mem->isFunctionLike())
    {
      CibFunctionHelper func(mem);
      if (!func.hasDefinition() || func.isVirtual())
        isInline = false;
      if (func.isMethod())
      {
        evaluateArgs(mem);
        evaluateReturnType(mem);
      }
    }
  }
  isInline = isInline || (cppCompound->templSpec_ != nullptr);
  if (isInline && cppCompound->isClassLike())
    cppCompound->setIsInline();
}

void CibHelper::setNeedsUnknownProxyDefinition(CibCppCompound* cppCompound)
{
  cppCompound->setNeedsUnknownProxyDefinition();
  for (auto child : cppCompound->children_[kPublic])
  {
    setNeedsUnknownProxyDefinition(child);
  }
}

void CibHelper::markNeedsUnknownProxyDefinition(CibCppCompound* cppCompound)
{
  for (auto mem : cppCompound->members_)
  {
    if (mem->objType_ == CppObj::kCompound)
    {
      auto compound = static_cast<CibCppCompound*>(mem);
      markNeedsUnknownProxyDefinition(compound);
      if (compound->isInterfaceLike())
      {
        setNeedsUnknownProxyDefinition(compound);
      }
    }
  }
}