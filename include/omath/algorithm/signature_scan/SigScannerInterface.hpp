//
// Created by Vlad on 3/2/2025.
//
#pragma once


namespace omath::algorithm
{
    class SigScannerInterface
    {
    public:
        virtual ~SigScannerInterface() = default;

        [[nodiscard]]
        virtual std::optional<std::uintptr_t> FindMatch(const std::string& pattern) const = 0;
    };
} // namespace omath::algorithm
