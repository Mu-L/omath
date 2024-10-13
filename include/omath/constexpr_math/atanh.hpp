#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T atanh_compute(const T x) noexcept
    {
        return log((T(1) + x) / (T(1) - x)) / T(2);
    }

    template<typename T>
    constexpr T atanh_check(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();

        if (T(1) < abs(x))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > (T(1) - abs(x)))
            return sgn(x) * GCLIM<T>::infinity();

        if (GCLIM<T>::min() > abs(x))
            return T(0);

        return atanh_compute(x);
    }
}

/**
 * Compile-time inverse hyperbolic tangent function
 *
 * @param x a real-valued input.
 * @return the inverse hyperbolic tangent function using \f[ \text{atanh}(x) = \frac{1}{2} \ln \left( \frac{1+x}{1-x} \right) \f]
 */

template<typename T>
constexpr return_t<T> atanh(const T x) noexcept
{
    return internal::atanh_check(static_cast<return_t<T>>(x));
}
