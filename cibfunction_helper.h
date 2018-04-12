#pragma once

#include "cibparams.h"

#include "cibfunction.h"
#include "cppdom.h"
#include "cppindent.h"

#include <string>

//////////////////////////////////////////////////////////////////////////

struct CibCppCompound;

class CppProgramEx;

enum class CallType
{
  kAsIs,
  kFromHandle,
  kToHandle
};
/*!
 * Helper class to deal with function-like C++ constructs, viz. constructors, destructors, and regular functions.
 * There is too much similiarity in constructor, destructor, and function but they are different too.
 * cppparser has three different classes for these and it makes sense. But for purpose of cib their similarity
 * is more important than their differences and so CibFunctionHelper provides a uniform interface and behaviour
 * to deal with them uniformly.
 * It is a wrapper class that provides access to underlying objects which are purposfully const.
 */
class CibFunctionHelper
{
private:
  union
  {
    const CppObj*             cppObj_;
    const CibCppConstructor*  ctor_;
    const CibCppDestructor*   dtor_;
    const CibCppFunction*     func_;
  };

public:
  static CppConstructor* CreateConstructor(CppObjProtLevel prot, std::string name, CppParamList* params, CppMemInitList* memInitList, unsigned int attr);
  static CppDestructor* CreateDestructor(CppObjProtLevel prot, std::string name, unsigned int attr);
  static CppFunction* CreateFunction(CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* params, unsigned int attr);

public:
  CibFunctionHelper(const CppObj* cppObj);
  CibFunctionHelper(const CibCppConstructor* ctor) : ctor_(ctor) {}
  CibFunctionHelper(const CibCppDestructor* dtor) : dtor_(dtor) {}
  CibFunctionHelper(const CibCppFunction* func) : func_(func) {}

  operator const CppObj* () const { return cppObj_; }
  CppObjProtLevel protectionLevel() const
  {
    return cppObj_->prot_;
  }
  bool isConstructor() const
  {
    return cppObj_->objType_  == CppObj::kConstructor;
  }
  bool isCopyConstructor() const
  {
    return isConstructor() && ctor_->isCopyConstructor();
  }
  bool isDestructor() const
  {
    return cppObj_->objType_ == CppObj::kDestructor;
  }
  bool isStatic() const
  {
    return (func_->attr_ & kStatic) == kStatic;
  }
  bool isInline() const
  {
    return (func_->attr_ & kInline) == kInline;
  }
  bool isVirtual() const
  {
    return (func_->attr_ & kVirtual) == kVirtual;
  }
  bool isPureVirtual() const
  {
    return (func_->attr_ & kPureVirtual) == kPureVirtual;
  }
  bool isConst() const
  {
    return (func_->attr_ & kConst) == kConst;
  }
  bool isFunction() const
  {
    return !isConstructor() && !isDestructor();
  }
  bool isMethod() const
  {
    return isFunction() && func_->isMethod();
  }
  bool hasDefinition() const
  {
    return func_->defn_ != nullptr;
  }

  CibCppCompound* getOwner() const;

  bool hasParams() const
  {
    return !isDestructor() && func_->params_ && !func_->params_->empty();
  }
  CppParamList* getParams() const
  {
    return isDestructor() ? nullptr : func_->params_;
  }
  CppVarType* retType() const
  {
    return isFunction() ? func_->retType_ : nullptr;
  }

  /// Name of function.
  const std::string& funcName() const
  {
    return func_->name_;
  }

  /// ProcType that is used by client side glue code to define function pointer variable.
  std::string procType(const CibParams& cibParams) const
  {
    return procName(cibParams) + "Proc";
  }

  /// ProcName that is used to name the variable that holds the function pointer.
  std::string procName(const CibParams& cibParams) const
  {
    std::string pname;
    if (isCopyConstructor())
      pname = cibParams.copyCtorCAPIPrefix;
    else if (isConstructor())
      pname = cibParams.ctorCAPIPrefix;
    else if (isDestructor())
      pname = cibParams.dtorCAPIPrefix;
    else
      pname = funcName();

    return pname;
  }

  /// @return signature of this method.
  std::string signature() const;

  /// Emits function arguments for function definition/declaration.
  void emitArgsForDecl(std::ostream& stm, const CppProgramEx& cppProgram, bool resolveTypes = true, bool emitHandle = false) const;
  void emitSignature(std::ostream& stm, const CppProgramEx& cppProgram) const;
  /// Emits function arguments for function call.
  void emitArgsForCall(std::ostream& stm, const CppProgramEx& cppProgram, const CibParams& cibParams, CallType callType) const;
  /// Emits declaration as originally defined/declared.
  void emitOrigDecl(std::ostream& stm, const CppProgramEx& cppProgram, const CibParams& cibParams, CppIndent indentation = CppIndent()) const;
  /// Emits the raw C API definition corresponding to C++ method, meant for library side glue code.
  void emitCAPIDefn(std::ostream& stm, const CppProgramEx& cppProgram, const CibParams& cibParams, const std::string& capiName, bool forProxy, CppIndent indentation = CppIndent()) const;
  void emitCAPIDefnForProxy(std::ostream& stm, const CppProgramEx& cppProgram, const CibParams& cibParams, const std::string& capiName, CppIndent indentation = CppIndent()) const;
  void emitUnknownProxyDefn(std::ostream& stm, const CppProgramEx& cppProgram, const CibParams& cibParams, const std::string& capiName, CppIndent indentation = CppIndent()) const;
  /// Emits the ProcType definition for the C++ method, meant for client side glue code.
  void emitProcType(std::ostream& stm, const CppProgramEx& cppProgram, const CibParams& cibParams, bool forUnknownProxy, CppIndent indentation = CppIndent()) const;
  void emitCAPIReturnType(std::ostream& stm, const CppProgramEx& cppProgram, CppIndent indentation = CppIndent()) const;
};
