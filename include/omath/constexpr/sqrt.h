#pragma once
#include <limits>

#include "is_inf.h"
#include "is_nan.h"


#ifndef OMATH_SQRT_MAX_ITER
#   define OMATH_SQRT_MAX_ITER 100
#endif


template<typename T>
using return_t = std::conditional_t<std::is_integral_v<T>, double, T>;

namespace omath::internal
{
    template<typename T>
    [[nodiscard]] constexpr T sqrt_recur(const T x, const T xn, const int count) noexcept
    {
        if (abs(xn - x / xn) / (T(1) + xn) < std::numeric_limits<T>::min())
            return xn;

        if (count < OMATH_SQRT_MAX_ITER)
            return sqrt_recur(x, T(0.5) * (xn + x / xn), count + 1);

        return xn;
    }


    template<typename T>
    [[nodiscard]] constexpr T sqrt_simplify(const T x, const T m_val) noexcept
    {
        if (x > T(1e+08))
            return sqrt_simplify(x / T(1e+08), T(1e+04) * m_val);

        if (x > T(1e+06))
            return sqrt_simplify(x / T(1e+06), T(1e+03) * m_val);

        if (x > T(1e+04))
            return sqrt_simplify(x / T(1e+04), T(1e+02) * m_val);

        if (x > T(100))
            return sqrt_simplify(x / T(100), T(10) * m_val);

        if (x > T(4))
            return sqrt_simplify(x / T(4), T(2) * m_val);

        return m_val * sqrt_recur(x, x / T(2), 0);
    }


    template<typename T>
    [[nodiscard]] constexpr T sqrt_check(const T x) noexcept
    {
        if (internal::is_nan(x))
            return std::numeric_limits<T>::quiet_NaN();

        if (x < T(0))
            return std::numeric_limits<T>::quiet_NaN();

        if (internal::is_posinf(x))
            return x;

        if (std::numeric_limits<T>::min() > abs(x))
            return T(0);

        if (std::numeric_limits<T>::min() > abs(T(1) - x))
            return x;

        return sqrt_simplify(x, T(1));
    }
}

namespace omath
{
    template<typename T>
    [[nodiscard]] constexpr std::conditional_t<std::is_integral_v<T>, double, T> sqrt(const T x) noexcept
    {
        return internal::sqrt_check(static_cast<return_t<T>>(x));
    }
}
