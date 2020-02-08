#include "int.h"
#include "value.h"

#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-delegate-helper.h"
#include "__zz_cib_Example-proxy.h"
#include "__zz_cib_Example-smart-ptr-helper.h"

namespace __zz_cib_ {
using namespace ::Example;
namespace Example {
using namespace ::Example;
namespace __zz_cib_Class258 {
namespace __zz_cib_Delegator {
using __zz_cib_Delegatee = ::Example::Value<::Example::Int>;
using __zz_cib_ThisClass = __zz_cib_Delegatee;
static ::Example::Value<::Example::Int>* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new __zz_cib_Delegatee(*__zz_cib_obj);
}
static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static ::Example::Value<::Example::Int>* __zz_cib_decl __zz_cib_new(::Example::Int* x) {
  return new __zz_cib_Delegatee(*x);
}
static ::Example::Int* __zz_cib_decl GetValue(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new ::Example::Int(__zz_cib_obj->::Example::Value<::Example::Int>::GetValue());
}
static void __zz_cib_decl SetValue(__zz_cib_Delegatee* __zz_cib_obj, ::Example::Int* x) {
  __zz_cib_obj->::Example::Value<::Example::Int>::SetValue(*x);
}
static bool __zz_cib_decl __zz_cib_OperatorCmpEq(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_ThisClass const * rhs) {
  return __zz_cib_obj->::Example::Value<::Example::Int>::operator ==(*rhs);
}
}
}}}

namespace __zz_cib_ {
using namespace ::Example;
namespace Example {
using namespace ::Example;
namespace __zz_cib_Class258 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::GetValue),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::SetValue),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_OperatorCmpEq)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 6 };
  return &methodTable;
}
}}}
namespace __zz_cib_ {
using namespace ::Example;
namespace Example {
using namespace ::Example;
namespace __zz_cib_Class259 {
namespace __zz_cib_Delegator {
using __zz_cib_Delegatee = ::Example::Value<float>;
using __zz_cib_ThisClass = __zz_cib_Delegatee;
static ::Example::Value<float>* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new __zz_cib_Delegatee(*__zz_cib_obj);
}
static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static ::Example::Value<float>* __zz_cib_decl __zz_cib_new(float x) {
  return new __zz_cib_Delegatee(x);
}
static float __zz_cib_decl GetValue(const __zz_cib_Delegatee* __zz_cib_obj) {
  return __zz_cib_obj->::Example::Value<float>::GetValue();
}
static void __zz_cib_decl SetValue(__zz_cib_Delegatee* __zz_cib_obj, float x) {
  __zz_cib_obj->::Example::Value<float>::SetValue(x);
}
static bool __zz_cib_decl __zz_cib_OperatorCmpEq(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_ThisClass const * rhs) {
  return __zz_cib_obj->::Example::Value<float>::operator ==(*rhs);
}
}
}}}

namespace __zz_cib_ {
using namespace ::Example;
namespace Example {
using namespace ::Example;
namespace __zz_cib_Class259 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::GetValue),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::SetValue),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_OperatorCmpEq)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 6 };
  return &methodTable;
}
}}}
namespace __zz_cib_ {
using namespace ::Example;
namespace Example {
using namespace ::Example;
namespace __zz_cib_Class257 {
namespace __zz_cib_Delegator {
using __zz_cib_Delegatee = ::Example::Value<int>;
using __zz_cib_ThisClass = __zz_cib_Delegatee;
static ::Example::Value<int>* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new __zz_cib_Delegatee(*__zz_cib_obj);
}
static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static ::Example::Value<int>* __zz_cib_decl __zz_cib_new(int x) {
  return new __zz_cib_Delegatee(x);
}
static int __zz_cib_decl GetValue(const __zz_cib_Delegatee* __zz_cib_obj) {
  return __zz_cib_obj->::Example::Value<int>::GetValue();
}
static void __zz_cib_decl SetValue(__zz_cib_Delegatee* __zz_cib_obj, int x) {
  __zz_cib_obj->::Example::Value<int>::SetValue(x);
}
static bool __zz_cib_decl __zz_cib_OperatorCmpEq(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_ThisClass const * rhs) {
  return __zz_cib_obj->::Example::Value<int>::operator ==(*rhs);
}
}
}}}

namespace __zz_cib_ {
using namespace ::Example;
namespace Example {
using namespace ::Example;
namespace __zz_cib_Class257 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::GetValue),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::SetValue),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_OperatorCmpEq)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 6 };
  return &methodTable;
}
}}}
