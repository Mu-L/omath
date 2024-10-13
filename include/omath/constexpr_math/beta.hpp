#pragma once
/**
 * Compile-time beta function
 *
 * @param a a real-valued input.
 * @param b a real-valued input.
 * @return the beta function using \f[ \text{B}(\alpha,\beta) := \int_0^1 t^{\alpha - 1} (1-t)^{\beta - 1} dt = \frac{\Gamma(\alpha)\Gamma(\beta)}{\Gamma(\alpha + \beta)} \f]
 * where \f$ \Gamma \f$ denotes the gamma function.
 */

template<typename T1, typename T2>
[[nodiscard]] constexpr common_return_t<T1, T2> beta(const T1 a, const T2 b) noexcept
{
    return exp(lbeta(a, b));
}
