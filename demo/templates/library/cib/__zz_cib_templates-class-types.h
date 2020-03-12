#pragma once

#include "__zz_cib_templates-smart-ptr-detection.h"

#include <functional>
#include <type_traits>

namespace __zz_cib_ {

template <typename _T, typename = void>
struct __zz_cib_UsesMethodTable : std::false_type
{
};

template <typename _T>
struct __zz_cib_UsesMethodTable<_T, std::void_t<typename _T::__zz_cib_AbiType>> : std::true_type
{
};

template <typename _T, typename = void>
struct __zz_cib_SharesLayout : std::false_type
{
};

template <typename _T>
struct __zz_cib_SharesLayout<
  _T,
  std::enable_if_t<std::is_same_v<std::decay_t<_T*>, typename std::decay_t<_T>::__zz_cib_AbiType>, void>>
  : std::true_type
{
};

template <typename _T>
struct __zz_cib_SharesLayout<
  const _T,
  std::enable_if_t<std::is_same_v<std::decay_t<_T*>, typename std::decay_t<_T>::__zz_cib_AbiType>, void>>
  : std::true_type
{
};

template <typename T, typename = void>
struct __zz_cib_IsStdFunction : std::false_type
{
};

template <typename R, typename... Args>
struct __zz_cib_IsStdFunction<std::function<R(Args...)>> : std::true_type
{
};

template <typename _T>
constexpr bool __zz_cib_UsesMethodTable_v = __zz_cib_UsesMethodTable<_T>::value;

template <typename _T>
constexpr bool __zz_cib_SharesLayout_v = __zz_cib_SharesLayout<_T>::value;

template <typename _T>
constexpr bool __zz_cib_IsStdFunction_v = __zz_cib_IsStdFunction<_T>::value;

template <typename _T>
constexpr bool __zz_cib_IsConstructibleClass_v =
  (std::is_class_v<_T> && !std::is_abstract_v<_T> && !__zz_cib_IsSmartPtr_v<_T> && !__zz_cib_IsStdFunction_v<_T>);

template <typename _T>
constexpr bool __zz_cib_IsAbstractClass_v = (std::is_class_v<_T> && std::is_abstract_v<_T>);

} // namespace __zz_cib_
