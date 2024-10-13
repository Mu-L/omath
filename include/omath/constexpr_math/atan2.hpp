#pragma once


namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T atan2_compute(const T y, const T x) noexcept
    {
        if (any_nan(y, x))
            return GCLIM<T>::quiet_NaN();

        if (GCLIM<T>::min() > abs(x))
        {
            if (GCLIM<T>::min() > abs(y))
            {
                if (neg_zero(y))
                {
                    if (neg_zero(x))
                        return -T(GCEM_PI);

                    return -T(0);
                }
                if (neg_zero(x))
                    return T(GCEM_PI);

                return T(0);
            }

            if (y > T(0))
                return T(GCEM_HALF_PI);

            return -T(GCEM_HALF_PI);
        }

        if (x < T(0))
        {
            if (y < T(0))
                return atan(y / x) - T(GCEM_PI);

            return atan(y / x) + T(GCEM_PI);
        }
        return atan(y / x);
    }

    template<typename T1, typename T2, typename TC = common_return_t<T1, T2> >
    [[nodiscard]] constexpr TC atan2_type_check(const T1 y, const T2 x) noexcept
    {
        return atan2_compute(static_cast<TC>(x), static_cast<TC>(y));
    }
}

/**
 * Compile-time two-argument arctangent function
 *
 * @param y a real-valued input.
 * @param x a real-valued input.
 * @return \f[ \text{atan2}(y,x) = \begin{cases} \text{atan}(y/x) & \text{ if } x > 0 \\ \text{atan}(y/x) + \pi & \text{ if } x < 0 \text{ and } y \geq 0 \\ \text{atan}(y/x) - \pi & \text{ if } x < 0 \text{ and } y < 0 \\ + \pi/2 & \text{ if } x = 0 \text{ and } y > 0 \\ - \pi/2 & \text{ if } x = 0 \text{ and } y < 0 \end{cases} \f]
 * The function is undefined at the origin, however the following conventions are used.
 * \f[ \text{atan2}(y,x) = \begin{cases} +0 & \text{ if } x = +0 \text{ and } y = +0 \\ -0 & \text{ if } x = +0 \text{ and } y = -0 \\ +\pi & \text{ if } x = -0 \text{ and } y = +0 \\ - \pi & \text{ if } x = -0 \text{ and } y = -0 \end{cases} \f]
 */

template<typename T1, typename T2>
[[nodiscard]] constexpr common_return_t<T1, T2> atan2(const T1 y, const T2 x) noexcept
{
    return internal::atan2_type_check(x, y);
}
