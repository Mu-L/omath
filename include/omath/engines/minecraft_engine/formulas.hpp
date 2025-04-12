//
// Created by Vladislav on 05.04.2025.
//
#pragma once

#include "omath/engines/minecraft_engine/constants.hpp"


namespace omath::minecraft_engine
{
    [[nodiscard]]
    Vector3<float> ForwardVector(const ViewAngles& angles);

    [[nodiscard]]
    Vector3<float> RightVector(const ViewAngles& angles);

    [[nodiscard]]
    Vector3<float> UpVector(const ViewAngles& angles);

    [[nodiscard]] Mat4x4 CalcViewMatrix(const ViewAngles& angles, const Vector3<float>& cam_origin);

    [[nodiscard]]
    Mat4x4 CalcPerspectiveProjectionMatrix(float fieldOfView, float aspectRatio, float near, float far);
} // namespace omath::opengl_engine
