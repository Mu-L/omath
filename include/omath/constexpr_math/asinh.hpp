#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T asinh_compute(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > abs(x))
            return T(0);

        return log(x + sqrt(x * x + T(1)));
    }
}

/**
 * Compile-time inverse hyperbolic sine function
 *
 * @param x a real-valued input.
 * @return the inverse hyperbolic sine function using \f[ \text{asinh}(x) = \ln \left( x + \sqrt{x^2 + 1} \right) \f]
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> asinh(const T x) noexcept
{
    return internal::asinh_compute(static_cast<return_t<T>>(x));
}
