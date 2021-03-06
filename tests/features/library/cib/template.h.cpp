#include "template.h"

#include "__zz_cib_FeatureTests-ids.h"
#include "__zz_cib_FeatureTests-mtable-helper.h"
#include "__zz_cib_FeatureTests-delegate-helper.h"
#include "__zz_cib_FeatureTests-generic.h"
#include "__zz_cib_FeatureTests-library-type-handler.h"
#include "__zz_cib_FeatureTests-class-down-cast.h"

namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::TemplateClassWithOneParam<int>> : public ::TemplateClassWithOneParam<int> {
  using __zz_cib_Delegatee = ::TemplateClassWithOneParam<int>;
  using __zz_cib_ThisClass = __zz_cib_Delegatee;
  static ::TemplateClassWithOneParam<int>* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
    return new __zz_cib_Delegatee(*__zz_cib_obj);
  }
  static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
        delete __zz_cib_obj;
  }
  static ::TemplateClassWithOneParam<int>* __zz_cib_decl __zz_cib_new(__zz_cib_AbiType_t<int> _a1) {
    return new __zz_cib_Delegatee(    __zz_cib_::__zz_cib_FromAbiType<int>(_a1));
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl get(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::TemplateClassWithOneParam<int>::get()
    );
  }
};
}

namespace __zz_cib_ {
namespace __zz_cib_Class257 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithOneParam<int>>::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithOneParam<int>>::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithOneParam<int>>::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithOneParam<int>>::get)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 4 };
  return &methodTable;
}
}}
namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::TemplateClassWithTwoParams<int, float>> : public ::TemplateClassWithTwoParams<int, float> {
  using __zz_cib_Delegatee = ::TemplateClassWithTwoParams<int, float>;
  using __zz_cib_ThisClass = __zz_cib_Delegatee;
  static ::TemplateClassWithTwoParams<int, float>* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
    return new __zz_cib_Delegatee(*__zz_cib_obj);
  }
  static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
        delete __zz_cib_obj;
  }
  static ::TemplateClassWithTwoParams<int, float>* __zz_cib_decl __zz_cib_new(__zz_cib_AbiType_t<int> _a1, __zz_cib_AbiType_t<float> _a2) {
    return new __zz_cib_Delegatee(    __zz_cib_::__zz_cib_FromAbiType<int>(_a1),
    __zz_cib_::__zz_cib_FromAbiType<float>(_a2));
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl get1(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::TemplateClassWithTwoParams<int, float>::get1()
    );
  }
  static __zz_cib_AbiType_t<float> __zz_cib_decl get2(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<float>(
      __zz_cib_obj->::TemplateClassWithTwoParams<int, float>::get2()
    );
  }
};
}

namespace __zz_cib_ {
namespace __zz_cib_Class258 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParams<int, float>>::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParams<int, float>>::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParams<int, float>>::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParams<int, float>>::get1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParams<int, float>>::get2)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 5 };
  return &methodTable;
}
}}
namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::TemplateClassWithTwoParamsAndDefaultParameter<int, int>> : public ::TemplateClassWithTwoParamsAndDefaultParameter<int, int> {
  using __zz_cib_Delegatee = ::TemplateClassWithTwoParamsAndDefaultParameter<int, int>;
  using __zz_cib_ThisClass = __zz_cib_Delegatee;
  static ::TemplateClassWithTwoParamsAndDefaultParameter<int, int>* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
    return new __zz_cib_Delegatee(*__zz_cib_obj);
  }
  static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
        delete __zz_cib_obj;
  }
  static ::TemplateClassWithTwoParamsAndDefaultParameter<int, int>* __zz_cib_decl __zz_cib_new(__zz_cib_AbiType_t<int> _a1, __zz_cib_AbiType_t<int> _a2) {
    return new __zz_cib_Delegatee(    __zz_cib_::__zz_cib_FromAbiType<int>(_a1),
    __zz_cib_::__zz_cib_FromAbiType<int>(_a2));
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl get1(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::TemplateClassWithTwoParamsAndDefaultParameter<int, int>::get1()
    );
  }
  static __zz_cib_AbiType_t<int> __zz_cib_decl get2(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<int>(
      __zz_cib_obj->::TemplateClassWithTwoParamsAndDefaultParameter<int, int>::get2()
    );
  }
};
}

namespace __zz_cib_ {
namespace __zz_cib_Class259 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParamsAndDefaultParameter<int, int>>::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParamsAndDefaultParameter<int, int>>::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParamsAndDefaultParameter<int, int>>::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParamsAndDefaultParameter<int, int>>::get1),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateClassWithTwoParamsAndDefaultParameter<int, int>>::get2)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 5 };
  return &methodTable;
}
}}
namespace __zz_cib_ {
template <>
struct __zz_cib_Delegator<::TemplateTest> : public ::TemplateTest {
  using __zz_cib_Delegatee = ::TemplateTest;
  using __zz_cib_ThisClass = __zz_cib_Delegatee;
  static ::TemplateTest* __zz_cib_decl __zz_cib_copy(const __zz_cib_Delegatee* __zz_cib_obj) {
    return new __zz_cib_Delegatee(*__zz_cib_obj);
  }
  static void __zz_cib_decl __zz_cib_delete(__zz_cib_Delegatee* __zz_cib_obj) {
        delete __zz_cib_obj;
  }
  static ::TemplateTest* __zz_cib_decl __zz_cib_new() {
    return new __zz_cib_Delegatee();
  }
  static __zz_cib_AbiType_t<TemplateClassWithOneParam<int>> __zz_cib_decl getTemplateClassWithOneParam(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<TemplateClassWithOneParam<int>>(
      __zz_cib_obj->::TemplateTest::getTemplateClassWithOneParam()
    );
  }
  static __zz_cib_AbiType_t<TemplateClassWithTwoParams<int, float>> __zz_cib_decl getTemplateClassWithTwoParams(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<TemplateClassWithTwoParams<int, float>>(
      __zz_cib_obj->::TemplateTest::getTemplateClassWithTwoParams()
    );
  }
  static __zz_cib_AbiType_t<TemplateClassWithTwoParamsAndDefaultParameter<int>> __zz_cib_decl getTemplateClassWithTwoParamsAndDefaultParameter(const __zz_cib_Delegatee* __zz_cib_obj) {
    return __zz_cib_ToAbiType<TemplateClassWithTwoParamsAndDefaultParameter<int>>(
      __zz_cib_obj->::TemplateTest::getTemplateClassWithTwoParamsAndDefaultParameter()
    );
  }
};
}

namespace __zz_cib_ {
namespace __zz_cib_Class256 {
const __zz_cib_MethodTable* __zz_cib_GetMethodTable() {
  static const __zz_cib_MTableEntry methodArray[] = {
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateTest>::__zz_cib_copy),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateTest>::__zz_cib_delete),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateTest>::__zz_cib_new),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateTest>::getTemplateClassWithOneParam),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateTest>::getTemplateClassWithTwoParams),
    reinterpret_cast<__zz_cib_MTableEntry> (&__zz_cib_::__zz_cib_Delegator<::TemplateTest>::getTemplateClassWithTwoParamsAndDefaultParameter)
  };
  static const __zz_cib_MethodTable methodTable = { methodArray, 6 };
  return &methodTable;
}
}}
