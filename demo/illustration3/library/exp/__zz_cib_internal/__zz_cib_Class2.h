#pragma once


#include "value.h"

namespace __zz_cib_ { namespace __zz_cib_Class2 {
class __zz_cib_Helper;
struct __zz_cib_Delegator;
}}

template<>
class Value<float>
{
public:
  Value(Value<float>&& rhs);
public:
  Value(Value<float> const & );
  ~Value();
  Value(float value);
  float get() const;

private:
  __ZZ_CIB_CLASS_INTERNAL_DEF(Value, __zz_cib_Class2);
};


namespace __zz_cib_ { namespace __zz_cib_Class2 {
class __zz_cib_Helper : public __zz_cib_::__zz_cib_MethodTableHelper
  , public __zz_cib_::__zz_cib_HandleHelper<::Value<float>, __zz_cib_Helper> {
private:
  using __zz_cib_TYPE = __zz_cib_HANDLE;
  friend class __zz_cib_::__zz_cib_HandleHelper<::Value<float>, __zz_cib_Helper>;
  friend class ::Value<float>;

  __zz_cib_Helper()
    : __zz_cib_::__zz_cib_MethodTableHelper(
      __zz_cib_illustration3_GetMethodTable(__zz_cib_classid))
  {}
  static __zz_cib_Helper& instance() {
    static __zz_cib_Helper helper;
    return helper;
  }

  static __zz_cib_TYPE* __zz_cib_copy_0(__zz_cib_HANDLE const * __zz_cib_param0) {
    using __zz_cib_copyProc = __zz_cib_TYPE* (__zz_cib_decl *) (__zz_cib_HANDLE const * __zz_cib_param0);
    return instance().invoke<__zz_cib_copyProc, __zz_cib_methodid::__zz_cib_copy_0>(
      __zz_cib_param0);
  }
  static void __zz_cib_delete_1(__zz_cib_TYPE* __zz_cib_obj) {
    if (__zz_cib_obj) {
      using __zz_cib_deleteProc = void (__zz_cib_decl *) (__zz_cib_TYPE*);
      return instance().invoke<__zz_cib_deleteProc, __zz_cib_methodid::__zz_cib_delete_1>(
        __zz_cib_obj
        );
    }
  }
  static __zz_cib_TYPE* __zz_cib_new_2(float value) {
    using __zz_cib_newProc = __zz_cib_TYPE* (__zz_cib_decl *) (float value);
    return instance().invoke<__zz_cib_newProc, __zz_cib_methodid::__zz_cib_new_2>(
      value);
  }
  static float get_3(const __zz_cib_TYPE* __zz_cib_obj) {
    using getProc = float (__zz_cib_decl *) (const __zz_cib_TYPE*);
    return instance().invoke<getProc, __zz_cib_methodid::get_3>(
      __zz_cib_obj
      );
  }
  static ::Value<float>* __zz_cib_create_proxy(__zz_cib_HANDLE* h) {
    return new ::Value<float>(h);
  }
public:
    static ::Value<float> __zz_cib_obj_from_handle(__zz_cib_HANDLE* h) {
      return ::Value<float>(h);
    }
    static __zz_cib_HANDLE*& __zz_cib_get_handle(::Value<float>* __zz_cib_obj) {
      return __zz_cib_obj->__zz_cib_h_;
    }
    static __zz_cib_HANDLE* const& __zz_cib_get_handle(const ::Value<float>* __zz_cib_obj) {
      return __zz_cib_obj->__zz_cib_h_;
    }
    static __zz_cib_HANDLE* __zz_cib_release_handle(::Value<float>* __zz_cib_obj) {
      __zz_cib_remove_proxy(__zz_cib_obj->__zz_cib_h_);
      auto h = __zz_cib_obj->__zz_cib_h_;
      __zz_cib_obj->__zz_cib_h_ = nullptr;
      return h;
    }
};
}}

inline Value<float>::Value(__zz_cib_::__zz_cib_HANDLE* h)
  : __zz_cib_h_(h)
{
  __zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

inline Value<float>::Value(Value<float>&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
  __zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_add_proxy(this, __zz_cib_h_);
}

inline Value<float>::Value(::Value<float> const & __zz_cib_param0)
  : Value<float>(__zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_copy_0(__zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_handle(__zz_cib_param0)))
{}

inline Value<float>::~Value() {
  auto h = __zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_delete_1(h);
}

inline Value<float>::Value(float value)
  : Value<float>(__zz_cib_::__zz_cib_Class2::__zz_cib_Helper::__zz_cib_new_2(value))
{}

inline float Value<float>::get() const {
  return __zz_cib_::__zz_cib_Class2::__zz_cib_Helper::get_3(__zz_cib_h_);
}
