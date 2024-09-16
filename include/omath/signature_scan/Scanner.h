//
// Created by Vlad on 16.09.2024.
//

#pragma once

#include <expected>
#include <cstdint>
#include <string_view>
#include <vector>
#include <optional>
#include <span>


#include "ErrorCodes.h"

namespace omath::signature_scan
{
    class Scanner
    {
        [[nodiscard]]
        static std::vector<std::optional<uint8_t>> GetSignatureBytes(const std::string_view& pattern);
    protected:
        [[nodiscard]]
        static std::expected<uintptr_t, Error> MaybeFindPatternEntry(const std::string_view& pattern,
                                                                     const std::span<uint8_t>& data);

    public:
        virtual std::expected<uintptr_t, Error> MaybeFindPattern(const std::string_view& pattern) = 0;
    };
}