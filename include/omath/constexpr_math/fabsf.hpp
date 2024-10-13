#pragma once

/**
 * Compile-time floating-point absolute value function
 *
 * @param x a real-valued input.
 * @return the absolute value of \c x, \f$ |x| \f$, where the return type is a floating point number (float only).
 */

template<typename T>
[[nodiscard]] constexpr float fabsf(const T x) noexcept
{
    return omath::abs(static_cast<float>(x));
}
