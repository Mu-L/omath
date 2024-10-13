//
// Created by vlad on 10/28/23.
//

#pragma once

#include <cstdint>
#include <functional>

#include "Angles.h"
#include "omath/Vector2.h"


namespace omath
{
    class Vector3 : public Vector2
    {
    public:
        float z = 0.f;
        constexpr Vector3(const float x, const float y, const float z) : Vector2(x, y), z(z) { }
        constexpr Vector3() : Vector2(), z(0.f) {};

        [[nodiscard]] constexpr bool operator==(const Vector3& src) const
        {
            return Vector2::operator==(src) && (src.z == z);
        }

        [[nodiscard]] constexpr bool operator!=(const Vector3& src) const
        {
            return !(*this == src);
        }

        constexpr Vector3& operator+=(const Vector3& v)
        {
            Vector2::operator+=(v);
            z += v.z;

            return *this;
        }

        constexpr Vector3& operator-=(const Vector3& v)
        {
            Vector2::operator-=(v);
            z -= v.z;

            return *this;
        }

        constexpr Vector3& operator*=(float fl)
        {
            Vector2::operator*=(fl);
            z *= fl;

            return *this;
        }

        constexpr Vector3& operator*=(const Vector3& v)
        {
            Vector2::operator*=(v);
            z *= v.z;

            return *this;
        }

        constexpr Vector3& operator/=(const Vector3& v)
        {
            Vector2::operator/=(v);
            z /= v.z;

            return *this;
        }

        constexpr Vector3& operator+=(float fl)
        {
            Vector2::operator+=(fl);
            z += fl;

            return *this;
        }

        constexpr Vector3& operator/=(float fl)
        {
            Vector2::operator/=(fl);
            z /= fl;

            return *this;
        }

        constexpr Vector3& operator-=(float fl)
        {
            Vector2::operator-=(fl);
            z -= fl;

            return *this;
        }

        [[nodiscard]]
        constexpr float DistTo(const Vector3& vOther) const
        {
            return (*this - vOther).Length();
        }

        constexpr Vector3& Abs()
        {
            Vector2::Abs();
            z = omath::abs(z);

            return *this;
        }

        [[nodiscard]] constexpr float DistToSqr(const Vector3& vOther) const
        {
            return (*this - vOther).LengthSqr();
        }

        [[nodiscard]] constexpr float Dot(const Vector3& vOther) const
        {
            return Vector2::Dot(vOther) + z * vOther.z;
        }
        [[nodiscard]] constexpr float Length() const
        {
            return omath::sqrt(Vector2::LengthSqr() + z * z);
        }

        [[nodiscard]] constexpr float LengthSqr() const
        {
            return Vector2::LengthSqr() + z * z;
        }

        [[nodiscard]] float Length2D() const
        {
            return Vector2::Length();
        }

        [[nodiscard]] constexpr Vector3 operator-() const
        {
            return {-x, -y, -z};
        }

        [[nodiscard]] constexpr Vector3 operator+(const Vector3& v) const
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        [[nodiscard]] constexpr Vector3 operator-(const Vector3& v) const
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        [[nodiscard]] constexpr Vector3 operator*(float fl) const
        {
            return {x * fl, y * fl, z * fl};
        }

        [[nodiscard]] constexpr Vector3 operator*(const Vector3& v) const
        {
            return {x * v.x, y * v.y, z * v.z};
        }

        [[nodiscard]] constexpr Vector3 operator/(const float fl) const
        {
            return {x / fl, y / fl, z / fl};
        }

        [[nodiscard]] constexpr Vector3 operator/(const Vector3& v) const
        {
            return {x / v.x, y / v.y, z / v.z};
        }

        [[nodiscard]] constexpr Vector3 Cross(const Vector3 &v) const
        {
            return
            {
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            };
        }
        [[nodiscard]] constexpr float Sum() const
        {
            return Vector3::Sum2D() + z;
        }

        [[nodiscard]] constexpr float Sum2D() const
        {
            return Vector2::Sum();
        }

        [[nodiscard]] constexpr Vector3 ViewAngleTo(const Vector3& other) const
        {
            const float distance = DistTo(other);
            const auto delta = other - *this;

            return
            {
                angles::RadiansToDegrees(omath::asin(delta.z / distance)),
                angles::RadiansToDegrees(omath::atan2(delta.y, delta.x)),
                0.f
            };
        }

        [[nodiscard]] constexpr static Vector3 ForwardVector(const float pitch, const float yaw)
        {
            const auto cosPitch = omath::cos(angles::DegreesToRadians(pitch));
            const auto sinPitch = omath::sin(angles::DegreesToRadians(pitch));

            const auto cosYaw = omath::cos(angles::DegreesToRadians(yaw));
            const auto sinYaw = omath::sin(angles::DegreesToRadians(yaw));


            return
            {
                cosPitch*cosYaw,
                cosPitch*sinYaw,
                sinPitch
            };
        }
        [[nodiscard]] constexpr static Vector3 RightVector(const float pitch, const float yaw, const float roll)
        {
            const auto radPitch = angles::DegreesToRadians(pitch);
            const auto radYaw = angles::DegreesToRadians(yaw);
            const auto radRoll = angles::DegreesToRadians(roll);

            const auto cosPitch = omath::cos(radPitch);
            const auto sinPitch = omath::sin(radPitch);

            const auto cosYaw = omath::cos(radYaw);
            const auto sinYaw = omath::sin(radYaw);

            const auto cosRoll = omath::cos(radRoll);
            const auto sinRoll = omath::sin(radRoll);


            return
            {
                sinRoll*sinPitch*cosYaw + cosRoll*sinYaw,
                sinRoll*sinPitch*sinYaw - cosRoll*cosYaw,
                -sinRoll*cosPitch
            };
        }
        [[nodiscard]] constexpr static Vector3 UpVector(const float pitch, const float yaw, const float roll)
        {
            return RightVector(pitch, yaw, roll).Cross(ForwardVector(pitch, yaw));
        }


        [[nodiscard]] constexpr Vector3 Normalized() const
        {
            const float length = Length();

            return length != 0 ? *this / length : *this;
        }

        [[nodiscard]] std::tuple<float, float, float> AsTuple() const
        {
            return std::make_tuple(x, y, z);
        }
    };
}
// ReSharper disable once CppRedundantNamespaceDefinition
namespace std
{
    template<>
    struct hash<omath::Vector3>
    {
        std::size_t operator()(const omath::Vector3& vec) const noexcept
        {
            std::size_t hash = 0;
            constexpr std::hash<float> hasher;

            hash ^= hasher(vec.x) + 0x9e3779b9 + (hash<<6) + (hash>>2);
            hash ^= hasher(vec.y) + 0x9e3779b9 + (hash<<6) + (hash>>2);
            hash ^= hasher(vec.z) + 0x9e3779b9 + (hash<<6) + (hash>>2);

            return hash;
        }
    };
}
