#include "example.h"

#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-delegate-helper.h"
#include "__zz_cib_Example-generic.h"
#include "__zz_cib_Example-library-type-handler.h"
#include "__zz_cib_Example-class-down-cast.h"

namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::CPoint> : public ::CPoint {
  using __zz_cib_Delegatee = ::CPoint;
  using __zz_cib_ThisClass = __zz_cib_Delegatee;
  static ::CPoint* __zz_cib_decl __zz_cib_copy(::CPoint* __zz_cib_this, const __zz_cib_Delegatee* __zz_cib_obj) {
    return new (__zz_cib_this) __zz_cib_Delegatee(*__zz_cib_obj);
  }
  static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
    __zz_cib_obj->~CPoint();
  }
  static ::CPoint* __zz_cib_decl __zz_cib_new(::CPoint* __zz_cib_this, __zz_cib_AbiType_t<double> _x, __zz_cib_AbiType_t<double> _y, __zz_cib_AbiType_t<double> _z) {
    return new (__zz_cib_this) __zz_cib_Delegatee(    __zz_cib_::__zz_cib_FromAbiType<double>(_x),
    __zz_cib_::__zz_cib_FromAbiType<double>(_y),
    __zz_cib_::__zz_cib_FromAbiType<double>(_z));
  }
  static __zz_cib_AbiType_t<const CPoint&> __zz_cib_decl __zz_cib_OperatorPlusEq(__zz_cib_Delegatee* __zz_cib_obj, __zz_cib_AbiType_t<const CPoint&> p) {
    return __zz_cib_ToAbiType<const CPoint&>(
      __zz_cib_obj->::CPoint::operator +=(
                __zz_cib_::__zz_cib_FromAbiType<const CPoint&>(p)
      )
    );
  }
};
}

namespace __zz_cib_ {
namespace __zz_cib_Class257 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::CPoint>::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::CPoint>::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::CPoint>::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::CPoint>::__zz_cib_OperatorPlusEq)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 4 };
  return &methodTable;
}
}}
