#include "example.h"

#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-proxy.h"

namespace __zz_cib_ { namespace Example { namespace A {
static ::Example::A* __zz_cib_decl __zz_cib_new_0() {
  return new ::Example::A();
}
static ::Example::A* __zz_cib_decl __zz_cib_copy_1(const ::Example::A* __zz_cib_param0) {
  return new ::Example::A(*__zz_cib_param0);
}
static void __zz_cib_decl __zz_cib_delete_2(::Example::A* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static void __zz_cib_decl VirtFunc_4(::Example::A* __zz_cib_obj) {
  __zz_cib_obj->::Example::A::VirtFunc();
}
static void __zz_cib_decl SomeFunc_3(::Example::A* __zz_cib_obj) {
  __zz_cib_obj->::Example::A::SomeFunc();
}
}}}

namespace __zz_cib_ { namespace Example { namespace B {
static ::Example::B* __zz_cib_decl __zz_cib_new_0() {
  return new ::Example::B();
}
static ::Example::B* __zz_cib_decl __zz_cib_copy_1(const ::Example::B* __zz_cib_param0) {
  return new ::Example::B(*__zz_cib_param0);
}
static void __zz_cib_decl __zz_cib_delete_2(::Example::B* __zz_cib_obj) {
  delete __zz_cib_obj;
}
static void __zz_cib_decl VirtFunc_3(::Example::B* __zz_cib_obj) {
  __zz_cib_obj->::Example::B::VirtFunc();
}
static ::Example::A* __zz_cib_decl __zz_cib_cast_to___Example__A_4(::Example::B* __zz_cib_obj) {
  return __zz_cib_obj;
}
}}}

namespace __zz_cib_ { namespace Example { namespace A {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_new_0),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_copy_1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_delete_2),
    reinterpret_cast<__zz_cib_MTableEntry> (&SomeFunc_3),
    reinterpret_cast<__zz_cib_MTableEntry> (&VirtFunc_4)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 5 };
  return &methodTable;
}
}}}
namespace __zz_cib_ { namespace Example { namespace B {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_new_0),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_copy_1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_delete_2),
    reinterpret_cast<__zz_cib_MTableEntry> (&VirtFunc_3),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_cast_to___Example__A_4)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 5 };
  return &methodTable;
}
}}}