//
// Created by Vlad on 27.08.2024.
//
#include <complex>
#include <gtest/gtest.h>
#include <omath/Matrix.hpp>
#include <omath/engines/Source/Camera.hpp>
#include <omath/projection/Camera.hpp>
#include <print>

int get_seed()
{
    int hour = std::atoi(__TIME__);
    int min = std::atoi(__TIME__ + 3);
    int sec = std::atoi(__TIME__ + 6);
    return 10000 * hour + 100 * min + sec;
}


TEST(UnitTestProjection, Projection)
{

    const auto seed = get_seed();


    const auto x = omath::Angle<float, 0.f, 180.f, omath::AngleFlags::Clamped>::FromDegrees(90.f);
    auto cam = omath::source::Camera({0, 0, 0}, omath::source::ViewAngles{}, {1920.f, 1080.f}, x, 0.01f, 1000.f);

    const auto projected = cam.WorldToScreen({1000, 0, 50});
    std::print("{} {} {}", projected->x, projected->y, projected->z);
}