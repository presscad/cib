#include "example.h"

#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-delegate-helper.h"
#include "__zz_cib_Example-generic.h"
#include "__zz_cib_Example-library-type-handler.h"
#include "__zz_cib_Example-class-down-cast.h"

namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::A> : public ::A {
  using __zz_cib_Delegatee = ::A;
  using __zz_cib_ThisClass = __zz_cib_Delegatee;
  static ::A* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
    return new __zz_cib_Delegatee(*__zz_cib_obj);
  }
  static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
        delete __zz_cib_obj;
  }
  static ::A* __zz_cib_decl __zz_cib_new() {
    return new __zz_cib_Delegatee();
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl fE(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_AbiType_t<E> e) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::A::fE(
                __zz_cib_::__zz_cib_FromAbiType<E>(e)
      )
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl fE_4(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_AbiType_t<EC> e) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::A::fE(
                __zz_cib_::__zz_cib_FromAbiType<EC>(e)
      )
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl fE_5(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_AbiType_t<E8> e) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::A::fE(
                __zz_cib_::__zz_cib_FromAbiType<E8>(e)
      )
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl fE_6(const __zz_cib_Delegatee* __zz_cib_obj, __zz_cib_AbiType_t<EC16> e) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::A::fE(
                __zz_cib_::__zz_cib_FromAbiType<EC16>(e)
      )
    );
  }
};
}

namespace __zz_cib_ {
namespace __zz_cib_Class257 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::fE),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::fE_4),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::fE_5),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::A>::fE_6)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 7 };
  return &methodTable;
}
}}
