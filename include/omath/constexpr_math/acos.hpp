#pragma once

namespace omath::internal
{
    template<typename T>
    [[nodiscard]] constexpr T acos_compute(const T x) noexcept
    {
        if (abs(x) > T(1))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > abs(x - T(1)))
            return T(0);

        if (GCLIM<T>::min() > abs(x))
            return T(GCEM_HALF_PI);

        return atan(sqrt(T(1) - x * x) / x);
    }

    template<typename T>
    [[nodiscard]] constexpr T acos_check(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();

        if (x > T(0))
            return acos_compute(x);

        return T(GCEM_PI) - acos_compute(-x);
    }
}

namespace omath
{
    template<typename T>
    [[nodiscard]] constexpr return_t<T> acos(const T x) noexcept
    {
        return internal::acos_check(static_cast<return_t<T>>(x));
    }
}
