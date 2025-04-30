//
// Created by Orange on 11/30/2024.
//
#include <gtest/gtest.h>
#include <omath/angles.hpp>

#include "omath/compile_definitions.hpp"

TEST(UnitTestAngles, RadiansToDeg)
{
    OMATH_CONSTEXPR float rad = 67;

    EXPECT_NEAR(omath::angles::RadiansToDegrees(rad), 3838.82f, 0.01f);
}

TEST(UnitTestAngles, DegreesToRadians)
{
    OMATH_CONSTEXPR float degree = 90;

    EXPECT_NEAR(omath::angles::DegreesToRadians(degree), 1.5708f, 0.01f);
}

TEST(UnitTestAngles, HorizontalFovToVerical)
{
    OMATH_CONSTEXPR float hFov = 90;
    OMATH_CONSTEXPR float aspectRation = 16.0f / 9.0f;
    const auto verticalFov = omath::angles::HorizontalFovToVertical(hFov, aspectRation);

    EXPECT_NEAR(verticalFov, 58.71f, 0.01f);
}

TEST(UnitTestAngles, VerticalToHorizontal)
{
    OMATH_CONSTEXPR float vFov = 58.71;
    OMATH_CONSTEXPR float aspectRation = 16.0f / 9.0f;
    const auto horizontalFov = omath::angles::VerticalFovToHorizontal(vFov, aspectRation);

    EXPECT_NEAR(horizontalFov, 89.99f, 0.01f);
}
TEST(UnitTestAngles, WrapAngle)
{
    const float wrapped = omath::angles::WrapAngle(361.f, 0.f, 360.f);

    EXPECT_NEAR(wrapped, 1.f, 0.01f);
}
TEST(UnitTestAngles, WrapAngleNegativeRange)
{
    const float wrapped = omath::angles::WrapAngle(-90.f, 0.f, 360.f);

    EXPECT_NEAR(wrapped, 270.f, 0.01f);
}