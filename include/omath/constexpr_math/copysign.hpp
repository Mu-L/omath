#pragma once

/**
 * Compile-time copy sign function
 *
 * @param x a real-valued input
 * @param y a real-valued input
 * @return replace the signbit of \c x with the signbit of \c y.
 */

template<typename T1, typename T2>
[[nodiscard]] constexpr T1 copysign(const T1 x, const T2 y) noexcept
{
    return (signbit(x) != signbit(y) ? -x : x);
}
