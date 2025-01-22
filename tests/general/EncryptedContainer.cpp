//
// Created by Orange on 1/12/2025.
//
#include <gtest/gtest.h>
#include <omath/containers/EncryptedContainer.hpp>

TEST(UnitTestEncContainer, Enc)
{
    constexpr omath::EncryptedContainer<int> val = 1488;

    ASSERT_EQ(val.get(), 1488);
}