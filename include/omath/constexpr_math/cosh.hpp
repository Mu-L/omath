#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T cosh_compute(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > abs(x))
            return T(1);

        return (exp(x) + exp(-x)) / T(2);
    }
}

/**
 * Compile-time hyperbolic cosine function
 *
 * @param x a real-valued input.
 * @return the hyperbolic cosine function using \f[ \cosh(x) = \frac{\exp(x) + \exp(-x)}{2} \f]
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> cosh(const T x) noexcept
{
    return internal::cosh_compute(static_cast<return_t<T>>(x));
}
