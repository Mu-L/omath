//
// Created by Vlad on 16.09.2024.
//
#include <omath/signature_scan/Scanner.h>
#include <stdexcept>


namespace omath::signature_scan
{
    constexpr uint8_t CharToByte(char input)
    {
        if (input >= 'a' && input <= 'f')
            return static_cast<uint8_t>(input - 'a');
        else if (input >= 'A' && input <= 'F')
            return static_cast<uint8_t>(input - 'A');
        else if (input >= '0' && input <= '9')
            return static_cast<uint8_t>(input - '0');

        throw std::invalid_argument("not hex char");
    }

    constexpr std::optional<uint8_t> HexToByte(char high, char low)
    {
        return static_cast<uint8_t>((CharToByte(high) << 4) | CharToByte(low));
    }

    std::vector<std::optional<uint8_t>> Scanner::GetSignatureBytes(const std::string_view &pattern)
    {
        std::vector<std::optional<uint8_t>> bytes;

        for (size_t i = 0; i < pattern.size();)
        {
            if (pattern[i] == ' ')
            {
                i += 1;
                continue;
            }
            if (pattern[i] == '?')
            {
                bytes.emplace_back(std::nullopt);
                pattern[i + 1] == '?' ? i += 2 : i++;
                continue;
            }
            bytes.emplace_back(HexToByte(pattern[i], pattern[i+1]));
            i += 2;
        }
        return bytes;
    }

    std::expected<uintptr_t, Error>
    Scanner::MaybeFindPatternEntry(const std::string_view &pattern, const std::span<uint8_t> &data)
    {
        const auto sig = GetSignatureBytes(pattern);

        for (int64_t i = 0; i < static_cast<int64_t>(data.size() - sig.size()); i++)
        {
            bool found = true;

            for (std::size_t j = 0; j < sig.size(); j++)
            {
                found = !sig[j].has_value() || sig[j].value() == data[i+j];

                if (not found)
                    break;
            }
            if (found)
                return i;
        }
        return std::unexpected(Error::PATTERN_NOT_FOUND);
    }
}