#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T cos_compute(const T x) noexcept
    {
        return (T(1) - x * x) / (T(1) + x * x);
    }

    template<typename T>
    [[nodiscard]] constexpr T cos_check(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > abs(x))
            return T(1);

        if (GCLIM<T>::min() > abs(x - T(GCEM_HALF_PI)))
            return T(0);

        if (GCLIM<T>::min() > abs(x + T(GCEM_HALF_PI)))
            return T(0);

        if (GCLIM<T>::min() > abs(x - T(GCEM_PI)))
            return -T(1);

        if (GCLIM<T>::min() > abs(x + T(GCEM_PI)))
            return -T(1);

        return cos_compute(tan(x / T(2)));
    }

}

/**
 * Compile-time cosine function
 *
 * @param x a real-valued input.
 * @return the cosine function using \f[ \cos(x) = \frac{1-\tan^2(x/2)}{1+\tan^2(x/2)} \f]
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> cos(const T x) noexcept
{
    return internal::cos_check(static_cast<return_t<T>>(x));
}
