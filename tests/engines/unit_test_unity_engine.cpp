//
// Created by Orange on 11/27/2024.
//
#include <gtest/gtest.h>
#include <omath/engines/unity_engine/camera.hpp>
#include <omath/engines/unity_engine/constants.hpp>
#include <omath/engines/unity_engine/formulas.hpp>
#include <print>

TEST(UnitTestUnityEngine, ForwardVector)
{
    const auto forward = omath::unity_engine::ForwardVector({});

    EXPECT_EQ(forward, omath::unity_engine::kAbsForward);
}

TEST(UnitTestUnityEngine, ForwardVectorRotationYaw)
{
    omath::unity_engine::ViewAngles angles;

    angles.yaw = omath::unity_engine::YawAngle::FromDegrees(90.f);

    const auto forward = omath::unity_engine::ForwardVector(angles);
    EXPECT_NEAR(forward.x, omath::unity_engine::kAbsRight.x, 0.00001f);
    EXPECT_NEAR(forward.y, omath::unity_engine::kAbsRight.y, 0.00001f);
    EXPECT_NEAR(forward.z, omath::unity_engine::kAbsRight.z, 0.00001f);
}

TEST(UnitTestUnityEngine, ForwardVectorRotationPitch)
{
    omath::unity_engine::ViewAngles angles;

    angles.pitch = omath::unity_engine::PitchAngle::FromDegrees(-90.f);

    const auto forward = omath::unity_engine::ForwardVector(angles);
    EXPECT_NEAR(forward.x, omath::unity_engine::kAbsUp.x, 0.00001f);
    EXPECT_NEAR(forward.y, omath::unity_engine::kAbsUp.y, 0.00001f);
    EXPECT_NEAR(forward.z, omath::unity_engine::kAbsUp.z, 0.00001f);
}

TEST(UnitTestUnityEngine, ForwardVectorRotationRoll)
{
    omath::unity_engine::ViewAngles angles;

    angles.roll = omath::unity_engine::RollAngle::FromDegrees(-90.f);

    const auto forward = omath::unity_engine::UpVector(angles);
    EXPECT_NEAR(forward.x, omath::unity_engine::kAbsRight.x, 0.00001f);
    EXPECT_NEAR(forward.y, omath::unity_engine::kAbsRight.y, 0.00001f);
    EXPECT_NEAR(forward.z, omath::unity_engine::kAbsRight.z, 0.00001f);
}

TEST(UnitTestUnityEngine, RightVector)
{
    const auto right = omath::unity_engine::RightVector({});

    EXPECT_EQ(right, omath::unity_engine::kAbsRight);
}

TEST(UnitTestUnityEngine, UpVector)
{
    const auto up = omath::unity_engine::UpVector({});
    EXPECT_EQ(up, omath::unity_engine::kAbsUp);
}

TEST(UnitTestUnityEngine, ProjectTargetMovedFromCamera)
{
    OMATH_CONSTEXPR auto fov = omath::projection::FieldOfView::FromDegrees(60.f);
    const auto cam = omath::unity_engine::Camera({0, 0, 0}, {}, {1280.f, 720.f}, fov, 0.01f, 1000.f);


    for (float distance = 0.02f; distance < 100.f; distance += 0.01f)
    {
        const auto projected = cam.WorldToScreen({0, 0, distance});

        EXPECT_TRUE(projected.has_value());

        if (!projected.has_value())
            continue;

        EXPECT_NEAR(projected->x, 640, 0.00001f);
        EXPECT_NEAR(projected->y, 360, 0.00001f);
    }
}
TEST(UnitTestUnityEngine, Project)
{
    OMATH_CONSTEXPR auto fov = omath::projection::FieldOfView::FromDegrees(60.f);

    const auto cam = omath::unity_engine::Camera({0, 0, 0}, {}, {1280.f, 720.f}, fov, 0.03f, 1000.f);
    const auto proj = cam.WorldToScreen({5.f, 3, 10.f});
    std::println("{} {}", proj->x, proj->y);
}

TEST(UnitTestUnityEngine, CameraSetAndGetFov)
{
    OMATH_CONSTEXPR auto fov = omath::projection::FieldOfView::FromDegrees(90.f);
    auto cam = omath::unity_engine::Camera({0, 0, 0}, {}, {1920.f, 1080.f}, fov, 0.01f, 1000.f);

    EXPECT_EQ(cam.GetFieldOfView().AsDegrees(), 90.f);
    cam.SetFieldOfView(omath::projection::FieldOfView::FromDegrees(50.f));

    EXPECT_EQ(cam.GetFieldOfView().AsDegrees(), 50.f);
}

TEST(UnitTestUnityEngine, CameraSetAndGetOrigin)
{
    auto cam = omath::unity_engine::Camera({0, 0, 0}, {}, {1920.f, 1080.f}, {}, 0.01f, 1000.f);

    EXPECT_EQ(cam.GetOrigin(), omath::Vector3<float>{});
    cam.SetFieldOfView(omath::projection::FieldOfView::FromDegrees(50.f));

    EXPECT_EQ(cam.GetFieldOfView().AsDegrees(), 50.f);
}