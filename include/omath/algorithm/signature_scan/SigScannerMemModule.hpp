//
// Created by Vlad on 3/2/2025.
//
#pragma once
#include "SigScannerInterface.hpp"


namespace omath::algorithm
{
    class SigScannerMemModule final : public SigScannerInterface
    {
    public:
        explicit SigScannerMemModule(const std::string_view& moduleName);
        ~SigScannerMemModule() override;
        [[nodiscard]] std::optional<std::uintptr_t> FindMatch(const std::string& pattern) const override;

    private:
        void* m_ModuleHandle = nullptr;
    };
} // namespace omath::algorithm
