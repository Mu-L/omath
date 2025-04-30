//
// Created by Orange on 11/30/2024.
//

#pragma once
#include <algorithm>
#include <utility>

#include "compile_definitions.hpp"
#include "omath/angles.hpp"


namespace omath
{
    enum class AngleFlags
    {
        Normalized = 0,
        Clamped = 1,
    };

    template<class Type = float, Type min = Type(0), Type max = Type(360), AngleFlags flags = AngleFlags::Normalized>
        requires std::is_arithmetic_v<Type>
    class Angle
    {
        Type m_angle;
        OMATH_CONSTEXPR explicit Angle(const Type& degrees)
        {
            if constexpr (flags == AngleFlags::Normalized)
                m_angle = angles::WrapAngle(degrees, min, max);

            else if constexpr (flags == AngleFlags::Clamped)
                m_angle = std::clamp(degrees, min, max);
            else
            {
                static_assert(false);
                std::unreachable();
            }
        }

    public:
        [[nodiscard]]
        OMATH_CONSTEXPR static Angle FromDegrees(const Type& degrees)
        {
            return Angle{degrees};
        }
        OMATH_CONSTEXPR Angle() : m_angle(0)
        {
        }
        [[nodiscard]]
        OMATH_CONSTEXPR static Angle FromRadians(const Type& degrees)
        {
            return Angle{angles::RadiansToDegrees<Type>(degrees)};
        }

        [[nodiscard]]
        OMATH_CONSTEXPR const Type& operator*() const
        {
            return m_angle;
        }

        [[nodiscard]]
        OMATH_CONSTEXPR Type AsDegrees() const
        {
            return m_angle;
        }

        [[nodiscard]]
        OMATH_CONSTEXPR Type AsRadians() const
        {
            return angles::DegreesToRadians(m_angle);
        }

        [[nodiscard]]
        Type Sin() const
        {
            return std::sin(AsRadians());
        }

        [[nodiscard]]
        Type Cos() const
        {
            return std::cos(AsRadians());
        }

        [[nodiscard]]
        Type Tan() const
        {
            return std::tan(AsRadians());
        }

        [[nodiscard]]
        Type Atan() const
        {
            return std::atan(AsRadians());
        }

        [[nodiscard]]
        Type Cot() const
        {
            return Cos() / Sin();
        }

        OMATH_CONSTEXPR Angle& operator+=(const Angle& other)
        {
            if OMATH_CONSTEXPR (flags == AngleFlags::Normalized)
                m_angle = angles::WrapAngle(m_angle + other.m_angle, min, max);

            else if OMATH_CONSTEXPR (flags == AngleFlags::Clamped)
                m_angle = std::clamp(m_angle + other.m_angle, min, max);
            else
            {
                static_assert(false);
                std::unreachable();
            }

            return *this;
        }

        [[nodiscard]]
        OMATH_CONSTEXPR std::partial_ordering operator<=>(const Angle& other) const = default;

        OMATH_CONSTEXPR Angle& operator-=(const Angle& other)
        {
            return operator+=(-other);
        }

        [[nodiscard]]
        OMATH_CONSTEXPR Angle& operator+(const Angle& other)
        {
            if OMATH_CONSTEXPR (flags == AngleFlags::Normalized)
                return {angles::WrapAngle(m_angle + other.m_angle, min, max)};

            else if OMATH_CONSTEXPR (flags == AngleFlags::Clamped)
                return {std::clamp(m_angle + other.m_angle, min, max)};

            else
                static_assert(false);

            std::unreachable();
        }

        [[nodiscard]]
        OMATH_CONSTEXPR Angle& operator-(const Angle& other)
        {
            return operator+(-other);
        }

        [[nodiscard]]
        OMATH_CONSTEXPR Angle operator-() const
        {
            return Angle{-m_angle};
        }
    };
} // namespace omath
