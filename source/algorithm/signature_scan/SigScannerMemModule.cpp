//
// Created by Vlad on 3/2/2025.
//
#include "omath/algorithm/signature_scan/SigScannerMemModule.hpp"
#include <Windows.h>


namespace omath::algorithm
{

    SigScannerMemModule::SigScannerMemModule(const std::string_view& moduleName)
    {
        m_ModuleHandle = GetModuleHandleA(moduleName.data());
    }

    std::optional<std::uintptr_t> SigScannerMemModule::FindMatch(const std::string& pattern) const
    {

        return std::nullopt;
    }
} // namespace omath::algorithm
