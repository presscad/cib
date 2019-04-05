#pragma once

#include "__zz_cib_Example-handle.h"

#include <map>

namespace __zz_cib_ {

template <typename _ProxyClass, typename _Helper>
class __zz_cib_ObjectCompanion
{
  _ProxyClass& mObj;

public:
  __zz_cib_ObjectCompanion(_ProxyClass& obj)
    : mObj(obj)
  {
  }
  operator __zz_cib_HANDLE*() const
  {
    return _Helper::__zz_cib_get_handle(&mObj);
  }
};

template <typename _ProxyClass, typename _Helper>
class __zz_cib_ObjectCompanion<_ProxyClass*, _Helper>
{
  _ProxyClass* mObj;

public:
  __zz_cib_ObjectCompanion(_ProxyClass* obj)
    : mObj(obj)
  {
  }
  operator __zz_cib_HANDLE*() const
  {
    return mObj ? _Helper::__zz_cib_get_handle(mObj) : nullptr;
  }
};

template <typename _ProxyClass, typename _Helper>
class __zz_cib_ObjectCompanion<_ProxyClass**, _Helper>
{
  _ProxyClass**    mObj;
  __zz_cib_HANDLE* mHandle{nullptr};

public:
  __zz_cib_ObjectCompanion(_ProxyClass** obj)
    : mObj(obj)
  {
  }
  operator __zz_cib_HANDLE**()
  {
    return mObj ? &mHandle : nullptr;
  }
  ~__zz_cib_ObjectCompanion()
  {
    if (mObj)
      *mObj = mHandle ? _Helper::__zz_cib_from_handle(mHandle) : nullptr;
  }
};

template <typename _ProxyClass, typename _Helper>
class __zz_cib_ObjectCompanion<const _ProxyClass**, _Helper>
{
  const _ProxyClass**    mObj;
  const __zz_cib_HANDLE* mHandle{nullptr};

public:
  __zz_cib_ObjectCompanion(const _ProxyClass** obj)
    : mObj(obj)
  {
  }
  operator const __zz_cib_HANDLE**()
  {
    return mObj ? &mHandle : nullptr;
  }
  ~__zz_cib_ObjectCompanion()
  {
    if (mObj)
      *mObj = mHandle ? _Helper::__zz_cib_from_handle(mHandle) : nullptr;
  }
};

template <typename _ProxyClass, typename _Helper>
class __zz_cib_ObjectCompanion<_ProxyClass* const*, _Helper>
{
  _ProxyClass* const* mObj;

public:
  __zz_cib_ObjectCompanion(_ProxyClass* const* obj)
    : mObj(obj)
  {
  }
  operator __zz_cib_HANDLE* const*()
  {
    return mObj ? &_Helper::__zz_cib_get_handle(*mObj) : nullptr;
  }
};

//! Helps converting proxy to handle and vice versa.
//! This actually a variant of CRTP.
template <typename _ProxyClass, typename _Helper>
class __zz_cib_HandleHelper
{
public:
  static _ProxyClass& __zz_cib_from_handle(__zz_cib_HANDLE& h)
  {
    return *__zz_cib_from_handle(&h);
  }
  static const _ProxyClass*& __zz_cib_from_handle(const __zz_cib_HANDLE* h)
  {
    return const_cast<const _ProxyClass*&>(__zz_cib_from_handle(const_cast<__zz_cib_HANDLE*>(h)));
  }
  static const _ProxyClass& __zz_cib_from_handle(const __zz_cib_HANDLE& h)
  {
    return *__zz_cib_from_handle(const_cast<__zz_cib_HANDLE*>(&h));
  }
  static _ProxyClass*& __zz_cib_from_handle(__zz_cib_HANDLE* h)
  {
    auto&  dis   = _Helper::instance();
    auto*& proxy = dis.findProxy(h);
    if (proxy)
      return proxy;
    _Helper::__zz_cib_create_proxy(h);
    return dis.findProxy(h);
  }
  static void __zz_cib_add_proxy(_ProxyClass* __zz_cib_obj, __zz_cib_HANDLE* h)
  {
    auto& dis = _Helper::instance();
    dis.addProxy(__zz_cib_obj, h);
  }
  static void __zz_cib_remove_proxy(__zz_cib_HANDLE* h)
  {
    auto& dis = _Helper::instance();
    dis.removeProxy(h);
  }
  template <typename T>
  static __zz_cib_ObjectCompanion<const T&, _Helper> __zz_cib_handle(const T& __zz_cib_obj)
  {
    return __zz_cib_ObjectCompanion<const T&, _Helper>(__zz_cib_obj);
  }
  template <typename T>
  static __zz_cib_ObjectCompanion<T*, _Helper> __zz_cib_handle(T* __zz_cib_obj)
  {
    return __zz_cib_ObjectCompanion<T*, _Helper>(__zz_cib_obj);
  }

private:
  _ProxyClass*& findProxy(__zz_cib_HANDLE* h)
  {
    static _ProxyClass* nullProxy = nullptr;
    auto                itr       = proxyRepo.find(h);
    return (itr == proxyRepo.end()) ? nullProxy : itr->second;
  }
  void addProxy(_ProxyClass* __zz_cib_obj, __zz_cib_HANDLE* h)
  {
    proxyRepo[h] = __zz_cib_obj;
  }
  void removeProxy(__zz_cib_HANDLE* h)
  {
    proxyRepo.erase(h);
  }

private:
  using ProxyRepo = std::map<__zz_cib_HANDLE*, _ProxyClass*>;
  ProxyRepo proxyRepo;
};

} // namespace __zz_cib_
