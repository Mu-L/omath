#pragma once

namespace omath::internal
{
    template<typename T>
    [[nodiscard]] constexpr bool is_nan(const T x) noexcept
    {
        return x != x;
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool any_nan(const T1 x, const T2 y) noexcept
    {
        return is_nan(x) || is_nan(y);
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool all_nan(const T1 x, const T2 y) noexcept
    {
        return is_nan(x) && is_nan(y);
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool any_nan(const T1 x, const T2 y, const T3 z) noexcept
    {
        return is_nan(x) || is_nan(y) || is_nan(z);
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool all_nan(const T1 x, const T2 y, const T3 z) noexcept
    {
        return is_nan(x) && is_nan(y) && is_nan(z);
    }
}
