#include "example.h"

#include "__zz_cib_internal/__zz_cib_Example-generic.h"


IF::IF(__zz_cib_AbiType h)
  : __zz_cib_h_(h)
{
  __zz_cib_MyHelper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

IF::IF(IF&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
  __zz_cib_MyHelper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

int IF::ProtectedVirtual() {
  return __zz_cib_::__zz_cib_FromAbiType<int>(
    __zz_cib_MyHelper::ProtectedVirtual<__zz_cib_::__zz_cib_AbiType_t<int>>(
      __zz_cib_::__zz_cib_ToAbiType<decltype(this)>(this)
    )
  );
}

int IF::ProtectedNonVirtual() {
  return __zz_cib_::__zz_cib_FromAbiType<int>(
    __zz_cib_MyHelper::ProtectedNonVirtual<__zz_cib_::__zz_cib_AbiType_t<int>>(
      __zz_cib_::__zz_cib_ToAbiType<decltype(this)>(this)
    )
  );
}

int IF::PublicVirtual() {
  return __zz_cib_::__zz_cib_FromAbiType<int>(
    __zz_cib_MyHelper::PublicVirtual<__zz_cib_::__zz_cib_AbiType_t<int>>(
      __zz_cib_::__zz_cib_ToAbiType<decltype(this)>(this)
    )
  );
}

int IF::PublicNonVirtual() {
  return __zz_cib_::__zz_cib_FromAbiType<int>(
    __zz_cib_MyHelper::PublicNonVirtual<__zz_cib_::__zz_cib_AbiType_t<int>>(
      __zz_cib_::__zz_cib_ToAbiType<decltype(this)>(this)
    )
  );
}

IF::~IF() {
__zz_cib_MyHelper::__zz_cib_release_proxy(this);
auto h = __zz_cib_MyHelper::__zz_cib_release_handle(this);
  __zz_cib_MyHelper::__zz_cib_delete(
    h
  );
}

IF::IF()
  : IF(__zz_cib_MyHelper::__zz_cib_new(
    this))
  {}


A::A(__zz_cib_AbiType h)
  : __zz_cib_h_(h)
{}

A::A(A&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
}

A::A(const A& __zz_cib_param0)
  : A(__zz_cib_MyHelper::__zz_cib_copy(
        __zz_cib_::__zz_cib_ToAbiType<const A&>(__zz_cib_param0)))
  {}

A::~A() {
auto h = __zz_cib_MyHelper::__zz_cib_release_handle(this);
  __zz_cib_MyHelper::__zz_cib_delete(
    h
  );
}

A::A()
  : A(__zz_cib_MyHelper::__zz_cib_new(
    ))
  {}

int A::SetIF(IF* pIF) {
  return __zz_cib_::__zz_cib_FromAbiType<int>(
    __zz_cib_MyHelper::SetIF<__zz_cib_::__zz_cib_AbiType_t<int>>(
      __zz_cib_::__zz_cib_ToAbiType<decltype(this)>(this),
      __zz_cib_::__zz_cib_ToAbiType<IF*>(pIF)
    )
  );
}

::IF* A::GetIF() const {
  return __zz_cib_::__zz_cib_FromAbiType<::IF*>(
    __zz_cib_MyHelper::GetIF<__zz_cib_::__zz_cib_AbiType_t<::IF*>>(
      __zz_cib_::__zz_cib_ToAbiType<decltype(this)>(this)
    )
  );
}

namespace __zz_cib_ {
template<>
class __zz_cib_Generic<::IF> : public ::IF {
  __zz_cib_AbiType __zz_cib_h_;

  using __zz_cib_methodid = __zz_cib_::__zz_cib_ids::__zz_cib_Class257::__zz_cib_methodid;
  static __zz_cib_MethodTableHelper& __zz_cib_get_mtable_helper() {
    static __zz_cib_MethodTableHelper mtableHelper(__zz_cib_Example_GetMethodTable(
      __zz_cib_ids::__zz_cib_Class257::__zz_cib_classid));
    return mtableHelper;
  }
  explicit __zz_cib_Generic(__zz_cib_AbiType h) : ::IF(h), __zz_cib_h_(h) {}
public:
  static ::IF* __zz_cib_from_handle(__zz_cib_AbiType h) {
    return new __zz_cib_Generic(h);
  }
  int ProtectedVirtual() override {
    using __zz_cib_proc = __zz_cib_AbiType_t<int>(__zz_cib_decl *) (__zz_cib_AbiType);
    return __zz_cib_FromAbiType<int>(
      __zz_cib_get_mtable_helper().invoke<__zz_cib_proc, __zz_cib_methodid::ProtectedVirtual>(
        __zz_cib_h_
      )
    );
  }
  int PublicPureVirtual() override {
    using __zz_cib_proc = __zz_cib_AbiType_t<int>(__zz_cib_decl *) (__zz_cib_AbiType);
    return __zz_cib_FromAbiType<int>(
      __zz_cib_get_mtable_helper().invoke<__zz_cib_proc, __zz_cib_methodid::PublicPureVirtual>(
        __zz_cib_h_
      )
    );
  }
  int ProtectedPureVirtual() override {
    using __zz_cib_proc = __zz_cib_AbiType_t<int>(__zz_cib_decl *) (__zz_cib_AbiType);
    return __zz_cib_FromAbiType<int>(
      __zz_cib_get_mtable_helper().invoke<__zz_cib_proc, __zz_cib_methodid::ProtectedPureVirtual>(
        __zz_cib_h_
      )
    );
  }
  int PublicVirtual() override {
    using __zz_cib_proc = __zz_cib_AbiType_t<int>(__zz_cib_decl *) (__zz_cib_AbiType);
    return __zz_cib_FromAbiType<int>(
      __zz_cib_get_mtable_helper().invoke<__zz_cib_proc, __zz_cib_methodid::PublicVirtual>(
        __zz_cib_h_
      )
    );
  }
  int PrivatePureVirtual() override {
    using __zz_cib_proc = __zz_cib_AbiType_t<int>(__zz_cib_decl *) (__zz_cib_AbiType);
    return __zz_cib_FromAbiType<int>(
      __zz_cib_get_mtable_helper().invoke<__zz_cib_proc, __zz_cib_methodid::PrivatePureVirtual>(
        __zz_cib_h_
      )
    );
  }
};
}

namespace __zz_cib_ {
::IF* __zz_cib_Helper<::IF>::__zz_cib_create_proxy(__zz_cib_AbiType h) {
  switch(__zz_cib_get_class_id(&h)) {
  default: break;
  }
  return ::__zz_cib_::__zz_cib_Generic<::IF>::__zz_cib_from_handle(h);
}
}
namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::IF> {
  using __zz_cib_Delegatee = ::IF;
  static __zz_cib_AbiType_t<int> __zz_cib_decl ProtectedVirtual(::IF* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->ProtectedVirtual()
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl PublicPureVirtual(::IF* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->PublicPureVirtual()
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl ProtectedPureVirtual(::IF* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->ProtectedPureVirtual()
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl PublicVirtual(::IF* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->PublicVirtual()
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl PrivatePureVirtual(::IF* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->PrivatePureVirtual()
    );
  }
  static void __zz_cib_decl __zz_cib_delete(::IF* __zz_cib_obj) {
    __zz_cib_Helper<::IF>::__zz_cib_release_handle(__zz_cib_obj);
    delete __zz_cib_obj;
  }
};
};

namespace __zz_cib_ {
namespace __zz_cib_Class257 {
static const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::IF>::ProtectedVirtual),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::IF>::PublicPureVirtual),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::IF>::ProtectedPureVirtual),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::IF>::PublicVirtual),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::IF>::PrivatePureVirtual),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::IF>::__zz_cib_delete)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 6 };
  return &methodTable;
}
}}

namespace __zz_cib_ {
const __zz_cib_MethodTable* __zz_cib_Helper<::IF>::__zz_cib_get_proxy_method_table() {
  return __zz_cib_::__zz_cib_Class257::__zz_cib_GetMethodTable();
}
}

