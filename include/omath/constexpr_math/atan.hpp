#pragma once

namespace internal
{
    // Series

    template<typename T>
    [[nodiscard]] constexpr T atan_series_order_calc(const T xx, const T x_pow, const uint_t order) noexcept
    {
        return T(1) / (T((order - 1) * 4 - 1) * x_pow) - T(1) / (T((order - 1) * 4 + 1) * x_pow * xx);
    }

    template<typename T>
    [[nodiscard]] constexpr T atan_series_order(const T x, const T x_pow, const uint_t order_begin,
                                                const uint_t max_order) noexcept
    {
        // run in reverse order to sum smallest numbers first

        if (max_order == 1)
            return T(GCEM_HALF_PI) - T(1) / x_pow; // use x_pow to avoid a warning

        T xx = x * x;
        T res = atan_series_order_calc(xx, pow(x, 4 * max_order - 5), max_order);

        uint_t depth = max_order - 1;

        while (depth > order_begin)
        {
            res += atan_series_order_calc(xx, pow(x, 4 * depth - 5), depth);

            --depth;
        }

        res += T(GCEM_HALF_PI) - T(1) / x;

        return res;
    }

    template<typename T>
    [[nodiscard]] constexpr T atan_series_main(const T x) noexcept
    {
        if (x < T(3))
            return atan_series_order(x, x, 1U, 10U);

        if (x < T(4))
            return atan_series_order(x, x, 1U, 9U); // O(1/x^39)

        if (x < T(5))
            return atan_series_order(x, x, 1U, 8U); // O(1/x^35)

        if (x < T(7))
            return atan_series_order(x, x, 1U, 7U); // O(1/x^31)

        if (x < T(11))
            return atan_series_order(x, x, 1U, 6U); // O(1/x^27)

        if (x < T(25))
            return atan_series_order(x, x, 1U, 5U); // O(1/x^23)

        if (x < T(100))
            return atan_series_order(x, x, 1U, 4U); // O(1/x^19)

        if (x < T(1000))
            return atan_series_order(x, x, 1U, 3U); // O(1/x^15)

        return atan_series_order(x, x, 1U, 2U); // O(1/x^11)
    }

    // CF


    template<typename T>
    [[nodiscard]] constexpr T atan_cf_recur(const T xx, const uint_t depth_begin, const uint_t max_depth) noexcept
    {
        uint_t depth = max_depth - 1;
        T res = T(2 * (depth + 1) - 1);

        while (depth > depth_begin - 1)
        {
            res = T(2 * depth - 1) + T(depth * depth) * xx / res;

            --depth;
        }

        return res;
    }


    template<typename T>
    [[nodiscard]] constexpr T atan_cf_main(const T x) noexcept
    {
        if (x < T(0.5))
            return x / atan_cf_recur(x * x, 1U, 15U);
        if (x < T(1))
            return x / atan_cf_recur(x * x, 1U, 25U);
        if (x < T(1.5))
            return x / atan_cf_recur(x * x, 1U, 35U);
        if (x < T(2))
            return x / atan_cf_recur(x * x, 1U, 45U);

        return x / atan_cf_recur(x * x, 1U, 52U);
    }


    // choose between series expansion and continued fraction

    template<typename T>
    [[nodiscard]] constexpr T atan_begin(const T x) noexcept
    {
        return x > T(2.5) ? atan_series_main(x) : atan_cf_main(x);
    }

    // check input
    template<typename T>
    [[nodiscard]] constexpr T atan_check(const T x) noexcept
    {
        if (is_nan(x))
            return GCLIM<T>::quiet_NaN();
        if (GCLIM<T>::min() > abs(x))
            return T(0);
        if (x < T(0))
            return -atan_begin(-x);

        return atan_begin(x);
    }

}

/**
 * Compile-time arctangent function
 *
 * @param x a real-valued input.
 * @return the inverse tangent function using \f[ \text{atan}(x) = \dfrac{x}{1 + \dfrac{x^2}{3 + \dfrac{4x^2}{5 + \dfrac{9x^2}{7 + \ddots}}}} \f]
 */

template<typename T>
[[nodiscard]] constexpr return_t<T> atan(const T x) noexcept
{
    return internal::atan_check(static_cast<return_t<T>>(x));
}
