#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T asin_compute(const T x) noexcept
    {
        if (x > T(1))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > abs(x - T(1)))
            return T(GCEM_HALF_PI);

        if (GCLIM<T>::min() > abs(x))
            return T(0);

        return atan(x / sqrt(T(1) - x * x));
    }

    template<typename T>
    [[nodiscard]]
    constexpr T asin_check(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();
        if (x < T(0))
            return -asin_compute(-x);

        return asin_compute(x);
    }
}

/**
 * Compile-time arcsine function
 *
 * @param x a real-valued input, where \f$ x \in [-1,1] \f$.
 * @return the inverse sine function using \f[ \text{asin}(x) = \text{atan} \left( \frac{x}{\sqrt{1-x^2}} \right) \f]
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> asin(const T x) noexcept
{
    return internal::asin_check(static_cast<return_t<T>>(x));
}
