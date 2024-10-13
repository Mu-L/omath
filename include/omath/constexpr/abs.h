#pragma once

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
