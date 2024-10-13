#pragma once

namespace internal
{
    template<typename T>
    [[nodiscard]] constexpr T binomial_coef_recur(const T n, const T k) noexcept
    {
        if (k == T(0) || n == k)
            return T(1);

        if (n == T(0))
            return T(0);

        return binomial_coef_recur(n - 1, k - 1) + binomial_coef_recur(n - 1, k);
    }


    template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    [[nodiscard]] constexpr T binomial_coef_check(const T n, const T k) noexcept
    {
        return binomial_coef_recur(n, k);
    }

    template<typename T, std::enable_if_t<!std::is_integral_v<T>>* = nullptr>
    [[nodiscard]] constexpr T binomial_coef_check(const T n, const T k) noexcept
    {
        return ( // NaN check; removed due to MSVC problems; template not being ignored in <int> cases
            // (is_nan(n) || is_nan(k)) ? GCLIM<T>::quiet_NaN() :
            //
            static_cast<T>(binomial_coef_recur(static_cast<ullint_t>(n), static_cast<ullint_t>(k))));
    }

    template<typename T1, typename T2, typename TC = common_t<T1, T2> >
    [[nodiscard]] constexpr TC binomial_coef_type_check(const T1 n, const T2 k) noexcept
    {
        return binomial_coef_check(static_cast<TC>(n), static_cast<TC>(k));
    }
}

/**
 * Compile-time binomial coefficient
 *
 * @param n integral-valued input.
 * @param k integral-valued input.
 * @return computes the Binomial coefficient
 * \f[ \binom{n}{k} = \frac{n!}{k!(n-k)!} \f]
 * also known as '\c n choose \c k '.
 */

template<typename T1, typename T2>
[[nodiscard]] constexpr common_t<T1, T2> binomial_coef(const T1 n, const T2 k) noexcept
{
    return internal::binomial_coef_type_check(n, k);
}
