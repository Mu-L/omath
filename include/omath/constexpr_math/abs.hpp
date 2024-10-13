#pragma once

/**
 * Compile-time absolute value function
 *
 * @param x a real-valued input.
 * @return the absolute value of \c x, \f$ |x| \f$, where the return type is the same as the input type.
 */
namespace omath
{
    template<typename T>
    [[nodiscard]] constexpr T abs(const T x) noexcept
    {
        if (x == T(0))
            return T(0);

        return x < T(0) ? -x : x;
    }
}
