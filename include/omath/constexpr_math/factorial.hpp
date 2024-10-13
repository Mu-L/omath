/*################################################################################
  ##
  ##   Copyright (C) 2016-2024 Keith O'Hara
  ##
  ##   This file is part of the GCE-Math C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * compile-time factorial function
 */

#pragma once

namespace internal
{
    // T should be int, long int, unsigned int, etc.

    template<typename T>
    [[nodiscard]] constexpr T factorial_table(const T x) noexcept
    {
        switch (static_cast<int>(x)) {
            case 0:  return T(1);
            case 1:  return T(1);
            case 2:  return T(2);
            case 3:  return T(6);
            case 4:  return T(24);
            case 5:  return T(120);
            case 6:  return T(720);
            case 7:  return T(5040);
            case 8:  return T(40320);
            case 9:  return T(362880);
            case 10: return T(3628800);
            case 11: return T(39916800);
            case 12: return T(479001600);
            case 13: return T(6227020800);
            case 14: return T(87178291200);
            case 15: return T(1307674368000);
            case 16: return T(20922789888000);
            case 17: return T(355687428096000);
            case 18: return T(6402373705728000);
            case 19: return T(121645100408832000);
            case 20: return T(2432902008176640000);
            default: std::unreachable();
        }
    }


    template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    [[nodiscard]] constexpr T factorial_recur(const T x) noexcept
    {
        return x < T(21) ? factorial_table(x) : x * factorial_recur(x - 1);
    }

    template<typename T, std::enable_if_t<!std::is_integral_v<T>>* = nullptr>
    [[nodiscard]] constexpr T factorial_recur(const T x) noexcept
    {
        return tgamma(x + 1);
    }
}

/**
 * Compile-time factorial function
 *
 * @param x a real-valued input.
 * @return Computes the factorial value \f$ x! \f$.
 * When \c x is an integral type (\c int, <tt>long int</tt>, etc.), a simple recursion method is used, along with table values.
 * When \c x is real-valued, <tt>factorial(x) = tgamma(x+1)</tt>.
 */

template<typename T>
[[nodiscard]] constexpr T factorial(const T x) noexcept
{
    return internal::factorial_recur(x);
}
