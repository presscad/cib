#pragma once

#include "__zz_cib_internal/__zz_cib_Example-def.h"
#include "__zz_cib_internal/__zz_cib_Example-ids.h"
#include "__zz_cib_internal/__zz_cib_Example-local-proxy-mgr.h"
#include "__zz_cib_internal/__zz_cib_Example-remote-proxy-mgr.h"
#include "__zz_cib_internal/__zz_cib_Example-mtable-helper.h"
#include "__zz_cib_internal/__zz_cib_Example-handle-helper.h"
#include "__zz_cib_internal/__zz_cib_Example-client-type-handler.h"

namespace __zz_cib_ {
template <>
struct __zz_cib_Helper<::SkRefCntBase> : public __zz_cib_MethodTableHelper {
  using __zz_cib_AbiType = typename ::SkRefCntBase::__zz_cib_AbiType;
  using _ProxyClass = ::SkRefCntBase;
  static const __zz_cib_MethodTable* __zz_cib_get_proxy_method_table();
  friend class ::SkRefCntBase;
  Example::__zz_cib_local_proxy_mgr<_ProxyClass> proxyMgr;
  using __zz_cib_methodid = __zz_cib_::__zz_cib_ids::__zz_cib_Class257::__zz_cib_methodid;

  __zz_cib_Helper()
    : __zz_cib_MethodTableHelper(
      __zz_cib_Example_GetMethodTable(__zz_cib_ids::__zz_cib_Class257::__zz_cib_classid))
  {}
  static __zz_cib_Helper& instance() {
    static __zz_cib_Helper helper;
    return helper;
  }

  static __zz_cib_AbiType __zz_cib_new(::SkRefCntBase* __zz_cib_h_) {
    using __zz_cib_proc = __zz_cib_AbiType (__zz_cib_decl *) (::SkRefCntBase*, const __zz_cib_MethodTable*);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::__zz_cib_new>(
      __zz_cib_h_, __zz_cib_get_proxy_method_table()
      );
  }
  static auto __zz_cib_delete(__zz_cib_AbiType __zz_cib_obj) {
    if (__zz_cib_obj) {
      using __zz_cib_proc = void (__zz_cib_decl *) (__zz_cib_AbiType);
      return instance().invoke<__zz_cib_proc, __zz_cib_methodid::__zz_cib_delete>(
        __zz_cib_obj
        );
    }
  }
  template <typename _RT>
  static auto ref(const __zz_cib_AbiType __zz_cib_obj) {
    using __zz_cib_proc = _RT (__zz_cib_decl *) (const __zz_cib_AbiType);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::ref>(
      __zz_cib_obj
      );
  }
  template <typename _RT>
  static auto unref(const __zz_cib_AbiType __zz_cib_obj) {
    using __zz_cib_proc = _RT (__zz_cib_decl *) (const __zz_cib_AbiType);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::unref>(
      __zz_cib_obj
      );
  }
  template <typename _RT>
  static auto internal_dispose(const __zz_cib_AbiType __zz_cib_obj) {
    using __zz_cib_proc = _RT (__zz_cib_decl *) (const __zz_cib_AbiType);
    return instance().invoke<__zz_cib_proc, __zz_cib_methodid::internal_dispose>(
      __zz_cib_obj
      );
  }
  static std::uint32_t __zz_cib_get_class_id(__zz_cib_AbiType* __zz_cib_obj) {
    using __zz_cib_get_class_idProc = std::uint32_t (__zz_cib_decl *) (__zz_cib_AbiType*);
    return instance().invoke<__zz_cib_get_class_idProc, __zz_cib_methodid::__zz_cib_get_class_id>(__zz_cib_obj);
  }
  static ::SkRefCntBase* __zz_cib_create_proxy(__zz_cib_AbiType h);
  static ::SkRefCntBase __zz_cib_obj_from_handle(__zz_cib_AbiType h) {
    return ::SkRefCntBase(h);
  }
  static __zz_cib_AbiType& __zz_cib_get_handle(::SkRefCntBase* __zz_cib_obj) {
    return __zz_cib_obj->__zz_cib_h_;
  }
  static __zz_cib_AbiType const& __zz_cib_get_handle(const ::SkRefCntBase* __zz_cib_obj) {
    return __zz_cib_obj->__zz_cib_h_;
  }
  static __zz_cib_AbiType __zz_cib_release_handle(::SkRefCntBase* __zz_cib_obj) {
    if (__zz_cib_obj->__zz_cib_h_ == nullptr) return nullptr;
    __zz_cib_remove_proxy(__zz_cib_obj->__zz_cib_h_);
    auto h = __zz_cib_obj->__zz_cib_h_;
    __zz_cib_obj->__zz_cib_h_ = nullptr;
    return h;
  }
  static void __zz_cib_release_proxy(::SkRefCntBase* __zz_cib_obj) {
    if (__zz_cib_obj->__zz_cib_h_) {
      using __zz_cib_release_proxyProc = void (__zz_cib_decl *) (__zz_cib_AbiType);
      return instance().invoke<__zz_cib_release_proxyProc, __zz_cib_methodid::__zz_cib_release_proxy>(
      __zz_cib_obj->__zz_cib_h_);
    }
  }
  static _ProxyClass* __zz_cib_from_handle(__zz_cib_AbiType h) {
    auto&  dis   = instance();
    auto* proxy = dis.proxyMgr.findProxy(h);
    if (proxy == nullptr)
      proxy = __zz_cib_create_proxy(h);
    return proxy;
  }
  static void __zz_cib_add_proxy(_ProxyClass* __zz_cib_obj, __zz_cib_AbiType h) {
    auto& dis = instance();
    dis.proxyMgr.addProxy(__zz_cib_obj, h);
  }
  static void __zz_cib_remove_proxy(__zz_cib_AbiType h) {
    auto& dis = instance();
      dis.proxyMgr.removeProxy(h);
  }
};
}
