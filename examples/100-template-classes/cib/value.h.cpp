#include "int.h"
#include "value.h"

#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-delegate-helper.h"
#include "__zz_cib_Example-proxy.h"

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class3 {
namespace __zz_cib_Delegator {
using __zz_cib_Delegatee = ::Example::Value<::Example::Int>;
static ::Example::Value<::Example::Int>* __zz_cib_decl __zz_cib_copy_0(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new __zz_cib_Delegatee(*__zz_cib_obj);
}
static void __zz_cib_decl __zz_cib_delete_1(__zz_cib_Delegatee* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static ::Example::Value<::Example::Int>* __zz_cib_decl __zz_cib_new_2(::Example::Int* x) {
  return new __zz_cib_Delegatee(*x);
}
static ::Example::Int* __zz_cib_decl GetValue_3(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new ::Example::Int(__zz_cib_obj->::Example::Value<::Example::Int>::GetValue());
}
static void __zz_cib_decl SetValue_4(__zz_cib_Delegatee* __zz_cib_obj, ::Example::Int* x) {
  __zz_cib_obj->::Example::Value<::Example::Int>::SetValue(*x);
}
}
}}}

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class3 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_copy_0),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_delete_1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_new_2),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::GetValue_3),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::SetValue_4)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 5 };
  return &methodTable;
}
}}}
namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class4 {
namespace __zz_cib_Delegator {
using __zz_cib_Delegatee = ::Example::Value<int>;
static ::Example::Value<int>* __zz_cib_decl __zz_cib_copy_0(const __zz_cib_Delegatee* __zz_cib_obj) {
  return new __zz_cib_Delegatee(*__zz_cib_obj);
}
static void __zz_cib_decl __zz_cib_delete_1(__zz_cib_Delegatee* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static ::Example::Value<int>* __zz_cib_decl __zz_cib_new_2(int x) {
  return new __zz_cib_Delegatee(x);
}
static int __zz_cib_decl GetValue_3(const __zz_cib_Delegatee* __zz_cib_obj) {
  return __zz_cib_obj->::Example::Value<int>::GetValue();
}
static void __zz_cib_decl SetValue_4(__zz_cib_Delegatee* __zz_cib_obj, int x) {
  __zz_cib_obj->::Example::Value<int>::SetValue(x);
}
}
}}}

namespace __zz_cib_ { namespace Example { namespace __zz_cib_Class4 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_copy_0),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_delete_1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_new_2),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::GetValue_3),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::SetValue_4)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 5 };
  return &methodTable;
}
}}}
