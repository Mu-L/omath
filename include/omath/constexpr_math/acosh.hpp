#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T acosh_compute(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();
        if (x < T(1))
            return GCLIM<T>::quiet_NaN();
        if (GCLIM<T>::min() > abs(x - T(1)))
            return T(0);

        return log(x + sqrt(x * x - T(1)));
    }
}

/**
 * Compile-time inverse hyperbolic cosine function
 *
 * @param x a real-valued input.
 * @return the inverse hyperbolic cosine function using \f[ \text{acosh}(x) = \ln \left( x + \sqrt{x^2 - 1} \right) \f]
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> acosh(const T x) noexcept
{
    return internal::acosh_compute(static_cast<return_t<T>>(x));
}
