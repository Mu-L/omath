//
// Created by Orange on 1/12/2025.
//
#pragma once
#include <array>
#include <cstdint>

constexpr int parseTwoDigits(const char* str)
{
    // Converts two characters in str[0..1] to an integer (00..59).
    return (str[0] - '0') * 10 + (str[1] - '0');
}

constexpr int parseFourDigits(const char* str)
{
    // Converts four characters in str[0..3] to an integer (e.g. 2025).
    return (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
}

// Parse month from __DATE__ string: "Mmm DD YYYY"
constexpr int parseMonth(const char* dateStr)
{
    // dateStr[0..2] = "Jan", "Feb", "Mar", ...
    // We'll just do a simple lookup.
    // (You could also do a switch or if/else chain.)
    constexpr const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; ++i)
    {
        // Compare the first 3 chars
        if (dateStr[0] == months[i][0] && dateStr[1] == months[i][1] && dateStr[2] == months[i][2])
        {
            return i + 1; // 1-based month
        }
    }
    return 0; // fallback, shouldn't happen in normal circumstances
}

constexpr int parseDay(const char* dateStr)
{
    // dateStr[4..5] = day
    return parseTwoDigits(dateStr + 4);
}

constexpr int parseYear(const char* dateStr)
{
    // dateStr[7..10] = year
    return parseFourDigits(dateStr + 7);
}

// Parse hour, minute, second from __TIME__ = "HH:MM:SS"
constexpr int parseHour(const char* timeStr)
{
    return parseTwoDigits(timeStr + 0);
}
constexpr int parseMinute(const char* timeStr)
{
    return parseTwoDigits(timeStr + 3);
}
constexpr int parseSecond(const char* timeStr)
{
    return parseTwoDigits(timeStr + 6);
}

//------------------------------
// 2) Combine date/time fields into a single 64-bit seed
//------------------------------
consteval uint64_t makeCompileTimeSeed()
{
    constexpr char dateStr[] = __DATE__; // "Mmm DD YYYY"
    constexpr char timeStr[] = __TIME__; // "HH:MM:SS"

    // Extract fields
    constexpr int month = parseMonth(dateStr);
    constexpr int day = parseDay(dateStr);
    constexpr int year = parseYear(dateStr);
    constexpr int hour = parseHour(timeStr);
    constexpr int minute = parseMinute(timeStr);
    constexpr int second = parseSecond(timeStr);

    uint64_t seed = 0;
    seed |= (static_cast<uint64_t>(year) & 0xFFFF) << 32;
    seed |= (static_cast<uint64_t>(month) & 0xFF) << 24;
    seed |= (static_cast<uint64_t>(day) & 0xFF) << 16;
    seed |= (static_cast<uint64_t>(hour) & 0xFF) << 8;
    seed |= (static_cast<uint64_t>(minute) & 0xFF);
    seed ^= (second << 16);

    return seed;
}


namespace omath
{
    template<typename T, std::uint64_t Key = makeCompileTimeSeed()>
    class EncryptedContainer
    {
    private:
        std::array<std::uint8_t, sizeof(T)> encryptedData_{};

        static constexpr std::uint8_t keyByteAtIndex(const std::size_t i)
        {
            return static_cast<std::uint8_t>((Key >> (8ULL * (i % 8ULL))) & 0xFFULL);
        }

        static constexpr std::array<std::uint8_t, sizeof(T)> encryptBytes(const T& value)
        {
            auto data = std::bit_cast<std::array<std::uint8_t, sizeof(T)>>(value);

            for (std::size_t i = 0; i < data.size(); ++i)
                data[i] = static_cast<std::uint8_t>(data[i] ^ keyByteAtIndex(i));

            return data;
        }

        static constexpr T decryptBytes(const std::array<std::uint8_t, sizeof(T)>& encData)
        {
            auto data = encData;

            for (std::size_t i = 0; i < data.size(); ++i)
                data[i] = static_cast<std::uint8_t>(data[i] ^ keyByteAtIndex(i));


            return std::bit_cast<T>(data);
        }

    public:
        consteval EncryptedContainer(const T& value) : encryptedData_{encryptBytes(value)}
        {
        }

        consteval EncryptedContainer(T&& value) : encryptedData_{encryptBytes(value)}
        {
        }

        constexpr T get() const
        {
            return decryptBytes(encryptedData_);
        }

        constexpr explicit operator T() const
        {
            return get();
        }
    };

} // namespace omath
