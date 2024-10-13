#pragma once
#include <limits>

namespace omath::internal
{
    template<typename T>
    [[nodiscard]] constexpr bool is_neginf(const T x) noexcept
    {
        return x == -std::numeric_limits<T>::infinity();
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool any_neginf(const T1 x, const T2 y) noexcept
    {
        return is_neginf(x) || is_neginf(y);
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool all_neginf(const T1 x, const T2 y) noexcept
    {
        return is_neginf(x) && is_neginf(y);
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool any_neginf(const T1 x, const T2 y, const T3 z) noexcept
    {
        return is_neginf(x) || is_neginf(y) || is_neginf(z);
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool all_neginf(const T1 x, const T2 y, const T3 z) noexcept
    {
        return is_neginf(x) && is_neginf(y) && is_neginf(z);
    }


    template<typename T>
    [[nodiscard]] constexpr bool is_posinf(const T x) noexcept
    {
        return x == std::numeric_limits<T>::infinity();
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool any_posinf(const T1 x, const T2 y) noexcept
    {
        return is_posinf(x) || is_posinf(y);
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool all_posinf(const T1 x, const T2 y) noexcept
    {
        return (is_posinf(x) && is_posinf(y));
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool any_posinf(const T1 x, const T2 y, const T3 z) noexcept
    {
        return is_posinf(x) || is_posinf(y) || is_posinf(z);
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool all_posinf(const T1 x, const T2 y, const T3 z) noexcept
    {
        return is_posinf(x) && is_posinf(y) && is_posinf(z);
    }

    template<typename T>
    [[nodiscard]] constexpr bool is_inf(const T x) noexcept
    {
        return is_neginf(x) || is_posinf(x);
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool any_inf(const T1 x, const T2 y) noexcept
    {
        return is_inf(x) || is_inf(y);
    }

    template<typename T1, typename T2>
    [[nodiscard]] constexpr bool all_inf(const T1 x, const T2 y) noexcept
    {
        return is_inf(x) && is_inf(y);
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool any_inf(const T1 x, const T2 y, const T3 z) noexcept
    {
        return (is_inf(x) || is_inf(y) || is_inf(z));
    }

    template<typename T1, typename T2, typename T3>
    [[nodiscard]] constexpr bool all_inf(const T1 x, const T2 y, const T3 z) noexcept
    {
        return (is_inf(x) && is_inf(y) && is_inf(z));
    }
}
