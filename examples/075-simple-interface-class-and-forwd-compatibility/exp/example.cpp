#include "example.h"


Interface::Interface(__zz_cib_::__zz_cib_HANDLE* h)
  : __zz_cib_h_(h)
{
  __zz_cib_::Interface::__zz_cib_Helper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

Interface::Interface(Interface&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
  __zz_cib_::Interface::__zz_cib_Helper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

Interface::~Interface() {
  __zz_cib_::Interface::__zz_cib_Helper::__zz_cib_release_proxy(this);
  auto h = __zz_cib_::Interface::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::Interface::__zz_cib_Helper::__zz_cib_delete_2(h);
}

Interface::Interface()
  : Interface(__zz_cib_::Interface::__zz_cib_Helper::__zz_cib_new_0(this))
{}

A::A(__zz_cib_::__zz_cib_HANDLE* h)
  : __zz_cib_h_(h)
{}

A::A(A&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
}

A::A(::A const & __zz_cib_param0)
  : A(__zz_cib_::A::__zz_cib_Helper::__zz_cib_copy_0(__zz_cib_::A::__zz_cib_Helper::__zz_cib_handle(__zz_cib_param0)))
{}

A::~A() {
  auto h = __zz_cib_::A::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::A::__zz_cib_Helper::__zz_cib_delete_1(h);
}

A::A()
  : A(__zz_cib_::A::__zz_cib_Helper::__zz_cib_new_2())
{}

int A::UseInterface(::Interface* pInterface) const {
  return __zz_cib_::A::__zz_cib_Helper::UseInterface_3(__zz_cib_h_, __zz_cib_::Interface::__zz_cib_Helper::__zz_cib_handle(pInterface));
}
namespace __zz_cib_ { namespace Interface {
struct __zz_cib_Delegator {
  using __zz_cib_Delegatee = ::Interface;
  static int __zz_cib_decl Gunc_2(::Interface* __zz_cib_obj) {
    return __zz_cib_obj->Gunc();
  }
  static int __zz_cib_decl Func_0(::Interface* __zz_cib_obj) {
    return __zz_cib_obj->Func();
  }
  static void __zz_cib_decl __zz_cib_delete_1(::Interface* __zz_cib_obj) {
    delete __zz_cib_obj;
  }
};
}}

namespace __zz_cib_ { namespace Interface {
static const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::Func_0),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::__zz_cib_delete_1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_Delegator::Gunc_2)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 3 };
  return &methodTable;
}
}}

namespace __zz_cib_ { namespace Interface {
const __zz_cib_MethodTable* __zz_cib_Helper::__zz_cib_get_proxy_method_table() {
  return __zz_cib_GetMethodTable();
}
}}
