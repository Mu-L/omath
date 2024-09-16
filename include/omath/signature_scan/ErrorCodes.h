//
// Created by Vlad on 16.09.2024.
//

#pragma once
#include <cstdint>


namespace omath::signature_scan
{
    enum class Error : uint16_t
    {
        PATTERN_NOT_FOUND = 0,
    };
}