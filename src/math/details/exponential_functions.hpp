/// @file
/// @brief Contains exponential math functions.
/// @author Fedorov Alexey
/// @date 04.05.2017

// =============================================================================
// MIT License
//
// Copyright (c) 2017-2018 Fedorov Alexey
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// =============================================================================

#ifndef FRAMEWORK_MATH_DETAILS
#error You should include math/math.hpp instead of exponential_functions.hpp
#endif

#ifndef FRAMEWORK_MATH_DETAILS_EXPONENTIAL_FUNCTIONS_HPP
#define FRAMEWORK_MATH_DETAILS_EXPONENTIAL_FUNCTIONS_HPP

#include <cmath>

#include <common/types.hpp>
#include <math/details/vector_type.hpp>

namespace framework
{
namespace math
{
/// @addtogroup math_exponential_functions
/// @{

/// @name pow
/// @{

/// @brief Computes the value of base raised to the power of exponent.
///
/// @param base Value of floating-point or integral type.
/// @param exponent Value of floating-point or integral type.
///
/// @return Value of base raised to the power of exponent e.g. (base ^ exponent).
template <typename T, typename U, typename R = decltype(::std::pow(std::declval<T>(), std::declval<U>()))>
inline R pow(const T& base, const U& exponent)
{
    return ::std::pow(base, exponent);
}

/// @brief Applies the pow function to every component of the vectors.
///
/// @param base Vector of floating-point or integral type.
/// @param exponent Vector of floating-point or integral type.
///
/// @return Vector of values of base that are raised to the power of exponent e.g. (base ^ exponent).
///
/// @see pow
template <uint32 N,
          typename T,
          typename U,
          typename R = decltype(::framework::math::pow(std::declval<T>(), std::declval<U>()))>
inline vector<N, R> pow(const vector<N, T>& base, const vector<N, U>& exponent)
{
    return transform(base, exponent, ::framework::math::pow<T, U>);
}
/// @}

/// @name exp
/// @{

/// @brief Computes Euler's number raised to the given power.
///
/// @param exponent Value of floating-point or integral type.
///
/// @return Euler's number raised to the given power (e ^ exponent).
template <typename T, typename R = decltype(::std::exp(std::declval<T>()))>
inline R exp(const T& exponent)
{
    return ::std::exp(exponent);
}

/// @brief Computes Euler's number raised to the given power.
///
/// @param exponent Vector of floating-point or integral type.
///
/// @return Vector of values that are equal to Euler's number raised to the given power (e ^ exponent).
///
/// @see exp
template <uint32 N, typename T, typename R = decltype(::framework::math::exp(std::declval<T>()))>
inline vector<N, R> exp(const vector<N, T>& exponent)
{
    return transform(exponent, ::framework::math::exp<T>);
}
/// @}

/// @name exp2
/// @{

/// @brief Computes 2 raised to the given power.
///
/// @param exponent Value of floating-point or integral type.
///
/// @return 2 raised to the given power (2 ^ exponent).
template <typename T, typename R = decltype(::std::exp2(std::declval<T>()))>
inline R exp2(const T& exponent)
{
    return ::std::exp2(exponent);
}

/// @brief Computes 2 raised to the given power.
///
/// @param exponent Vector of floating-point or integral type.
///
/// @return Vector of values that are equal to 2 raised to the given power (2 ^ exponent).
///
/// @see exp2
template <uint32 N, typename T, typename R = decltype(::framework::math::exp2(std::declval<T>()))>
inline vector<N, R> exp2(const vector<N, T>& exponent)
{
    return transform(exponent, ::framework::math::exp2<T>);
}
/// @}

/// @name log
/// @{

/// @brief Computes the natural (base e) logarithm of the value.
///
/// @param value Value of floating-point or integral type.
///
/// @return The natural (base-e) logarithm of value (ln(value)).
template <typename T, typename R = decltype(::std::log(std::declval<T>()))>
inline R log(const T& value)
{
    return ::std::log(value);
}

/// @brief Computes component-wise natural (base e) logarithm of the value.
///
/// @param value Vector of floating-point or integral type.
///
/// @return Vector of values that are equal to the natural logarithm of the corresponding component.
///
/// @see log
template <uint32 N, typename T, typename R = decltype(::framework::math::log(std::declval<T>()))>
inline vector<N, R> log(const vector<N, T>& value)
{
    return transform(value, ::framework::math::log<T>);
}
/// @}

/// @name log2
/// @{

/// @brief Computes the binary (base 2) logarithm of the value.
///
/// @param value Value of floating-point or integral type.
///
/// @return The binary (base 2) logarithm of the value.
template <typename T, typename R = decltype(::std::log2(std::declval<T>()))>
inline R log2(const T& value)
{
    return ::std::log2(value);
}

/// @brief Computes component-wise binary (base 2) logarithm of the value.
///
/// @param value Vector of floating-point or integral type.
///
/// @return Vector of values that are equal to the binary logarithm of the corresponding component.
///
/// @see log2
template <uint32 N, typename T, typename R = decltype(::framework::math::log2(std::declval<T>()))>
inline vector<N, R> log2(const vector<N, T>& value)
{
    return transform(value, ::framework::math::log2<T>);
}
/// @}

/// @name sqrt
/// @{

/// @brief Computes the square root of the value.
///
/// @param value Value of floating-point or integral type.
///
/// @return The square root of the value.
template <typename T, typename R = decltype(::std::sqrt(std::declval<T>()))>
inline R sqrt(const T& value)
{
    return ::std::sqrt(value);
}

/// @brief Computes component-wise square root of the value.
///
/// @param value Vector of floating-point or integral type.
///
/// @return Vector of values that are equal to the square root of the corresponding component.
///
/// @see sqrt
template <uint32 N, typename T, typename R = decltype(::framework::math::sqrt(std::declval<T>()))>
inline vector<N, R> sqrt(const vector<N, T>& value)
{
    return transform(value, ::framework::math::sqrt<T>);
}
/// @}

/// @name invsqrt
/// @{

/// @brief Computes the inverse square root of the value.
///
/// @param value Value of floating-point or integral type.
///
/// @return The inverse square root of the value.
template <typename T, typename R = decltype(::std::sqrt(std::declval<T>()))>
inline R invsqrt(const T& value)
{
    return R{1} / ::std::sqrt(value);
}

/// @brief Computes component-wise inverse square root of the value.
///
/// @param value Vector of floating-point or integral type.
///
/// @return Vector of values that are equal to the inverse square root of the corresponding component.
///
/// @see invsqrt
template <uint32 N, typename T, typename R = decltype(::framework::math::invsqrt(std::declval<T>()))>
inline vector<N, R> invsqrt(const vector<N, T>& value)
{
    return transform(value, ::framework::math::invsqrt<T>);
}
/// @}

/// @}

} // namespace math

} // namespace framework

#endif
