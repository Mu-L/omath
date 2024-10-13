#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr int ceil_resid(const T x, const T x_whole) noexcept
    {
        return x > T(0) && x > x_whole;
    }

    template<typename T>
    [[nodiscard]] constexpr T ceil_int(const T x, const T x_whole) noexcept
    {
        return x_whole + static_cast<T>(ceil_resid(x, x_whole));
    }

    template<typename T>
    [[nodiscard]] constexpr T ceil_check_internal(const T x) noexcept
    {
        return x;
    }

    template<>
    [[nodiscard]] constexpr float ceil_check_internal<float>(const float x) noexcept
    {
        return abs(x) >= 8388608.f
                    ?
                    // if
                    x
                    :
                    // else
                    ceil_int(x, static_cast<float>(static_cast<int>(x)));
    }

    template<>
    [[nodiscard]] constexpr double ceil_check_internal<double>(const double x) noexcept
    {
        return (abs(x) >= 4503599627370496.
                    ?
                    // if
                    x
                    :
                    // else
                    ceil_int(x, double(static_cast<llint_t>(x))));
    }

    template<>
    [[nodiscard]] constexpr long double ceil_check_internal<long double>(const long double x) noexcept
    {
        return (abs(x) >= 9223372036854775808.l
                    ?
                    // if
                    x
                    :
                    // else
                    ceil_int(x, static_cast<long double>(static_cast<ullint_t>(abs(x))) * sgn(x)));
    }

    template<typename T>
    [[nodiscard]] constexpr T ceil_check(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();

        if (!is_finite(x))
            return x;

        if (GCLIM<T>::min() > abs(x))
            return x;

        return ceil_check_internal(x);
    }
}

/**
 * Compile-time ceil function
 *
 * @param x a real-valued input.
 * @return computes the ceiling-value of the input.
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> ceil(const T x) noexcept
{
    return internal::ceil_check(static_cast<return_t<T>>(x));
}
