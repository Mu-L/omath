#pragma once
#include <limits>
#include <numbers>


namespace omath::internal
{

template<typename T>
constexpr
T
asin_compute(const T x)
noexcept
{
    return( // only defined on [-1,1]
            x > T(1) ? \
                std::numeric_limits<T>::quiet_NaN() :
            // indistinguishable from one or zero
            std::numeric_limits<T>::min() > abs(x -  T(1)) ? \
                T(std::numbers::pi_v<T> / 2.f) :
            std::numeric_limits<T>::min() > abs(x) ? \
                T(0) :
            // else
                atan( x/sqrt(T(1) - x*x) ) );
}

template<typename T>
constexpr
T
asin_check(const T x)
noexcept
{
    return( // NaN check
            is_nan(x) ? \
                std::numeric_limits<T>::quiet_NaN() :
            //
            x < T(0) ? \
                - asin_compute(-x) :
                  asin_compute(x) );
}

}

/**
 * Compile-time arcsine function
 *
 * @param x a real-valued input, where \f$ x \in [-1,1] \f$.
 * @return the inverse sine function using \f[ \text{asin}(x) = \text{atan} \left( \frac{x}{\sqrt{1-x^2}} \right) \f]
 */

template<typename T>
constexpr
return_t<T>
asin(const T x)
noexcept
{
    return internal::asin_check( static_cast<return_t<T>>(x) );
}

#endif

