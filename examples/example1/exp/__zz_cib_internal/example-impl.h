#include "__zz_cib_Example-def.h"
#include "__zz_cib_Example-ids.h"
#include "__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_Example-handle-helper.h"

namespace __zz_cib_ { namespace Example { namespace A {
class __zz_cib_Helper : public __zz_cib_::__zz_cib_MethodTableHelper
  , public __zz_cib_::__zz_cib_HandleHelper<::Example::A, __zz_cib_Helper> {
private:
  friend class ::Example::A;
  friend class __zz_cib_::__zz_cib_HandleHelper<::Example::A, __zz_cib_Helper>;

  static __zz_cib_HANDLE* __zz_cib_new_0() {
    using __zz_cib_newProc = __zz_cib_HANDLE* (__zz_cib_decl *) ();
    return instance().invoke<__zz_cib_newProc>(
      __zz_cib_methodid::__zz_cib_new_0);
  }
  static __zz_cib_HANDLE* __zz_cib_copy_1(const __zz_cib_HANDLE* __zz_cib_param0) {
    using __zz_cib_copyProc = __zz_cib_HANDLE* (__zz_cib_decl *) (const __zz_cib_HANDLE* __zz_cib_param0);
    return instance().invoke<__zz_cib_copyProc>(
      __zz_cib_methodid::__zz_cib_copy_1,
      __zz_cib_param0);
  }
  static void __zz_cib_delete_2(__zz_cib_HANDLE* __zz_cib_obj) {
    if (__zz_cib_obj) {
      using __zz_cib_deleteProc = void (__zz_cib_decl *) (__zz_cib_HANDLE*);
      return instance().invoke<__zz_cib_deleteProc>(
        __zz_cib_methodid::__zz_cib_delete_2,
        __zz_cib_obj);
    }
  }
  static void SomeFunc_3(__zz_cib_HANDLE* __zz_cib_obj) {
    using SomeFuncProc = void (__zz_cib_decl *) (__zz_cib_HANDLE*);
    return instance().invoke<SomeFuncProc>(
      __zz_cib_methodid::SomeFunc_3,
      __zz_cib_obj);
  }
  __zz_cib_Helper()
    : __zz_cib_::__zz_cib_MethodTableHelper(
      __zz_cib_Example_GetMethodTable(__zz_cib_classid))
  {}
  static const __zz_cib_Helper& instance() {
    static __zz_cib_Helper helper;
    return helper;
  }

  static ::Example::A* __zz_cib_create_proxy(__zz_cib_HANDLE* h) {
    return new ::Example::A(h);
  }
public:
  static ::Example::A __zz_cib_obj_from_handle(__zz_cib_HANDLE* h) {
    return ::Example::A(h);
  }
static __zz_cib_HANDLE* __zz_cib_handle(const ::Example::A* __zz_cib_obj) {
    return __zz_cib_obj->__zz_cib_h_;
  }
static __zz_cib_HANDLE* __zz_cib_handle(const ::Example::A& __zz_cib_obj) {
    return __zz_cib_obj.__zz_cib_h_;
  }
  static __zz_cib_HANDLE* __zz_cib_release_handle(::Example::A* __zz_cib_obj) {
    auto h = __zz_cib_obj->__zz_cib_h_;
    __zz_cib_obj->__zz_cib_h_ = nullptr;
    return h;
  }
};
}}}

inline Example::A::A(__zz_cib_::__zz_cib_HANDLE* h)
  : __zz_cib_h_(h)
{}

inline Example::A::A(A&& rhs)
  : __zz_cib_h_(rhs.__zz_cib_h_)
{
  rhs.__zz_cib_h_ = nullptr;
}

inline Example::A::A()
  : Example::A(__zz_cib_::Example::A::__zz_cib_Helper::__zz_cib_new_0())
{}

inline Example::A::A(const ::Example::A& __zz_cib_param0)
  : Example::A(__zz_cib_::Example::A::__zz_cib_Helper::__zz_cib_copy_1(__zz_cib_::Example::A::__zz_cib_Helper::__zz_cib_handle(__zz_cib_param0)))
{}

inline Example::A::~A() {
  auto h = __zz_cib_::Example::A::__zz_cib_Helper::__zz_cib_release_handle(this);
  __zz_cib_::Example::A::__zz_cib_Helper::__zz_cib_delete_2(h);
}

inline void Example::A::SomeFunc() {
  __zz_cib_::Example::A::__zz_cib_Helper::SomeFunc_3(__zz_cib_h_);
}