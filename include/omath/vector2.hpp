//
// Created by Vlad on 02.09.2024.
//

#pragma once
#include <cmath>
#include <tuple>

#ifdef OMATH_IMGUI_INTEGRATION
#include <imgui.h>
#endif
#include "omath/compile_definitions.hpp"

namespace omath
{

    template<class Type>
        requires std::is_arithmetic_v<Type>
    class Vector2
    {
    public:
        Type x = static_cast<Type>(0);
        Type y = static_cast<Type>(0);

        // Constructors
        constexpr Vector2() = default;

        constexpr Vector2(const Type& x, const Type& y) : x(x), y(y)
        {
        }

        // Equality operators
        [[nodiscard]]
        OMATH_CONSTEXPR bool operator==(const Vector2& src) const
        {
            return x == src.x && y == src.y;
        }

        [[nodiscard]]
        OMATH_CONSTEXPR bool operator!=(const Vector2& src) const
        {
            return !(*this == src);
        }

        // Compound assignment operators
        OMATH_CONSTEXPR Vector2& operator+=(const Vector2& v)
        {

            x += v.x;
            y += v.y;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator-=(const Vector2& v)
        {
            x -= v.x;
            y -= v.y;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator*=(const Vector2& v)
        {
            x *= v.x;
            y *= v.y;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator/=(const Vector2& v)
        {
            x /= v.x;
            y /= v.y;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator*=(const Type& fl)
        {
            x *= fl;
            y *= fl;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator/=(const Type& fl)
        {
            x /= fl;
            y /= fl;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator+=(const Type& fl)
        {
            x += fl;
            y += fl;

            return *this;
        }

        OMATH_CONSTEXPR Vector2& operator-=(const Type& fl)
        {
            x -= fl;
            y -= fl;

            return *this;
        }

        // Basic vector operations
        [[nodiscard]] Type DistTo(const Vector2& vOther) const
        {
            return std::sqrt(DistToSqr(vOther));
        }

        [[nodiscard]] OMATH_CONSTEXPR Type DistToSqr(const Vector2& vOther) const
        {
            return (x - vOther.x) * (x - vOther.x) + (y - vOther.y) * (y - vOther.y);
        }

        [[nodiscard]] OMATH_CONSTEXPR Type Dot(const Vector2& vOther) const
        {
            return x * vOther.x + y * vOther.y;
        }

#ifndef _MSC_VER
        [[nodiscard]] OMATH_CONSTEXPR Type Length() const
        {
            return std::hypot(this->x, this->y);
        }

        [[nodiscard]] OMATH_CONSTEXPR Vector2 Normalized() const
        {
            const Type len = Length();
            return len > 0.f ? *this / len : *this;
        }
#else
        [[nodiscard]] Type Length() const
        {
            return std::hypot(x, y);
        }

        [[nodiscard]] Vector2 Normalized() const
        {
            const Type len = Length();
            return len > 0.f ? *this / len : *this;
        }
#endif
        [[nodiscard]] OMATH_CONSTEXPR Type LengthSqr() const
        {
            return x * x + y * y;
        }

        OMATH_CONSTEXPR Vector2& Abs()
        {
            // FIXME: Replace with std::abs, if it will become OMATH_CONSTEXPRable
            x = x < 0 ? -x : x;
            y = y < 0 ? -y : y;
            return *this;
        }

        [[nodiscard]] OMATH_CONSTEXPR Vector2 operator-() const
        {
            return {-x, -y};
        }

        // Binary arithmetic operators
        [[nodiscard]] OMATH_CONSTEXPR Vector2 operator+(const Vector2& v) const
        {
            return {x + v.x, y + v.y};
        }

        [[nodiscard]] OMATH_CONSTEXPR Vector2 operator-(const Vector2& v) const
        {
            return {x - v.x, y - v.y};
        }

        [[nodiscard]] OMATH_CONSTEXPR Vector2 operator*(const float fl) const
        {
            return {x * fl, y * fl};
        }

        [[nodiscard]] OMATH_CONSTEXPR Vector2 operator/(const float fl) const
        {
            return {x / fl, y / fl};
        }

        // Sum of elements
        [[nodiscard]] OMATH_CONSTEXPR Type Sum() const
        {
            return x + y;
        }

        [[nodiscard]]
        OMATH_CONSTEXPR std::tuple<Type, Type> AsTuple() const
        {
            return std::make_tuple(x, y);
        }

#ifdef OMATH_IMGUI_INTEGRATION
        [[nodiscard]]
        ImVec2 ToImVec2() const
        {
            return {static_cast<float>(this->x), static_cast<float>(this->y)};
        }
#endif
    };
} // namespace omath
