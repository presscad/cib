/*
    Generated by cib for ABI compatibility and stability.
    For copyright details refer to the copyright statement of library that contains this file.
*/

#pragma once

#include <type_traits>

namespace __zz_cib_ {

template <typename>
class __zz_cib_Generic
{
};

template <typename _T, typename = void>
struct __zz_cib_ProxyType
{
  class __zz_cib_OpaqueProxy;
  using __zz_cib_Proxy = __zz_cib_OpaqueProxy*;
};

template <typename _T>
struct __zz_cib_ProxyType<_T, std::void_t<typename _T::__zz_cib_OpaqueProxy>>
{
  using __zz_cib_Proxy = typename _T::__zz_cib_OpaqueProxy*;
};

// template <typename _T>
// struct __zz_cib_ProxyType<_T, std::void_t<decltype(__zz_cib_ProxyManagerDelegator(static_cast<_T*>(nullptr), 0))>>
// {
//   using __zz_cib_Proxy = decltype(__zz_cib_ProxyManagerDelegator(static_cast<_T*>(nullptr), 0));
// };

template <typename _T>
using __zz_cib_Proxy_t = typename __zz_cib_ProxyType<_T>::__zz_cib_Proxy;

} // namespace __zz_cib_
