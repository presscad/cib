#pragma once

#include "__zz_cib_internal/__zz_cib_Demo-def.h"
#include "__zz_cib_internal/__zz_cib_Demo-ids.h"
#include "__zz_cib_internal/__zz_cib_Demo-local-proxy-mgr.h"
#include "__zz_cib_internal/__zz_cib_Demo-remote-proxy-mgr.h"
#include "__zz_cib_internal/__zz_cib_Demo-mtable-helper.h"
#include "__zz_cib_internal/__zz_cib_Demo-handle-helper.h"

namespace __zz_cib_ { namespace A {
class __zz_cib_Helper : public __zz_cib_MethodTableHelper
  , public __zz_cib_HandleHelper<::A, __zz_cib_Helper> {
private:
  using __zz_cib_TYPE = __zz_cib_HANDLE;
  friend class __zz_cib_HandleHelper<::A, __zz_cib_Helper>;
  static const __zz_cib_MethodTable* __zz_cib_get_proxy_method_table();
  using _ProxyClass = ::A;
  friend class ::A;
  Demo::__zz_cib_local_proxy_mgr<_ProxyClass> proxyMgr;

  __zz_cib_Helper()
    : __zz_cib_MethodTableHelper(
      __zz_cib_Demo_GetMethodTable(__zz_cib_classid))
  {}
  static __zz_cib_Helper& instance() {
    static __zz_cib_Helper helper;
    return helper;
  }

  static __zz_cib_TYPE* __zz_cib_new(::A* __zz_cib_proxy) {
    using __zz_cib_proc = __zz_cib_TYPE* (__zz_cib_decl *) (::A*, const __zz_cib_MethodTable*);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::__zz_cib_new>(
      __zz_cib_proxy, __zz_cib_get_proxy_method_table()
      );
  }
  static __zz_cib_TYPE* __zz_cib_copy(::A* __zz_cib_proxy, __zz_cib_HANDLE const * __zz_cib_param0) {
    using __zz_cib_proc = __zz_cib_TYPE* (__zz_cib_decl *) (::A*, const __zz_cib_MethodTable*, __zz_cib_HANDLE const * __zz_cib_param0);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::__zz_cib_copy>(
      __zz_cib_proxy, __zz_cib_get_proxy_method_table(),
      __zz_cib_param0);
  }
  static void __zz_cib_delete(__zz_cib_TYPE* __zz_cib_obj) {
    if (__zz_cib_obj) {
      using __zz_cib_proc = void (__zz_cib_decl *) (__zz_cib_TYPE*);
      return instance().invoke<__zz_cib_proc, __zz_cib_methodid::__zz_cib_delete>(
        __zz_cib_obj
        );
    }
  }
  static int F(__zz_cib_TYPE* __zz_cib_obj) {
    using __zz_cib_proc = int (__zz_cib_decl *) (__zz_cib_TYPE*);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::F>(
      __zz_cib_obj
      );
  }
  static int F_4(__zz_cib_TYPE* __zz_cib_obj, int __zz_cib_param0) {
    using __zz_cib_proc = int (__zz_cib_decl *) (__zz_cib_TYPE*, int __zz_cib_param0);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::F_4>(
      __zz_cib_obj,
      __zz_cib_param0);
  }
  static int V(__zz_cib_TYPE* __zz_cib_obj) {
    using __zz_cib_proc = int (__zz_cib_decl *) (__zz_cib_TYPE*);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::V>(
      __zz_cib_obj
      );
  }
  static ::A* __zz_cib_create_proxy(__zz_cib_HANDLE* h) {
    return new ::A(h);
  }
public:
  static ::A __zz_cib_obj_from_handle(__zz_cib_HANDLE* h) {
    return ::A(h);
  }
  static __zz_cib_HANDLE*& __zz_cib_get_handle(::A* __zz_cib_obj) {
    return __zz_cib_obj->__zz_cib_h_;
  }
  static __zz_cib_HANDLE* const& __zz_cib_get_handle(const ::A* __zz_cib_obj) {
    return __zz_cib_obj->__zz_cib_h_;
  }
  static __zz_cib_HANDLE* __zz_cib_release_handle(::A* __zz_cib_obj) {
    if (__zz_cib_obj->__zz_cib_h_ == nullptr) return nullptr;
    __zz_cib_remove_proxy(__zz_cib_obj->__zz_cib_h_);
    auto h = __zz_cib_obj->__zz_cib_h_;
    __zz_cib_obj->__zz_cib_h_ = nullptr;
    return h;
  }
  static void __zz_cib_release_proxy(::A* __zz_cib_obj) {
    if (__zz_cib_obj->__zz_cib_h_) {
      using __zz_cib_release_proxyProc = void (__zz_cib_decl *) (__zz_cib_HANDLE*);
      return instance().invoke<__zz_cib_release_proxyProc, __zz_cib_methodid::__zz_cib_release_proxy>(
      __zz_cib_obj->__zz_cib_h_);
    }
  }
  static _ProxyClass* __zz_cib_get_or_create_proxy(__zz_cib_HANDLE* h) {
    auto&  dis   = instance();
    auto* proxy = dis.proxyMgr.findProxy(h);
    if (proxy == nullptr)
      proxy = __zz_cib_create_proxy(h);
    return proxy;
  }
  static void __zz_cib_add_proxy(_ProxyClass* __zz_cib_obj, __zz_cib_HANDLE* h) {
    auto& dis = instance();
    dis.proxyMgr.addProxy(__zz_cib_obj, h);
  }
  static void __zz_cib_remove_proxy(__zz_cib_HANDLE* h) {
    auto& dis = instance();
      dis.proxyMgr.removeProxy(h);
  }
};
}}
