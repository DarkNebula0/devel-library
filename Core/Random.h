#pragma once
#include <random>

/// @namespace Devel::Random
/// @brief This namespace encapsulates functionalities related to random number and UUID generation.
///
/// <b>Example</b>
///
/// @code{.cpp}
///     int randomInt = Devel::Random::Generate<int>(1, 10);  // Generates a random integer between 1 and 10
///     std::string uuid = Devel::Random::GenerateUUID();  // Generates a random UUID
///     std::cout << "Random integer: " << randomInt << std::endl;
///     std::cout << "UUID: " << uuid << std::endl;
/// @endcode
namespace Devel::Random {
    /// @brief Generates a random number between the given range.
    ///
    /// This function uses the Mersenne Twister algorithm (std::mt19937) for generating random numbers.
    /// @tparam T The numeric type of the minimum and maximum values.
    /// @param i_nMinimal The minimum value of the range.
    /// @param i_nMaximal The maximum value of the range.
    /// @return A random number of type T between the minimum and maximum values.
    template<typename T>
    T Generate(T i_nMinimal, T i_nMaximal) {
        /// @var static std::random_device s_oRandomDevice
        /// @brief The random device used to generate random numbers.
        ///
        /// @var static std::mt19937 s_oRandomEngine
        /// @brief The Mersenne Twister random number generator.
        static std::random_device s_oRandomDevice;


        static std::mt19937 s_oRandomEngine(s_oRandomDevice());
        return std::uniform_int_distribution<T>(i_nMinimal, i_nMaximal)(s_oRandomEngine);
    }

    /// @brief Generates a universally unique identifier (UUID).
    ///
    /// This function generates a UUID string using the random_device and mt19937 from the C++ Standard Library.
    /// @return A UUID string.
    std::string GenerateUUID() {
        static std::random_device s_oRandomDevice;
        static std::mt19937 s_oRandomEngine(s_oRandomDevice());
        static std::uniform_int_distribution<> distribution1(0, 15);

        /// @var static constexpr char s_szHex[]
        /// @brief An array of characters used to represent hexadecimal digits.
        static constexpr char s_szHex[] = "0123456789abcdef";

        std::string sUUID;

        for (int i = 0; i < 36; i++) {
            switch (i) {
                case 8:
                case 13:
                case 18:
                case 23:
                    sUUID += '-';
                    break;
                case 14:
                    sUUID += '4';
                    break;
                case 19:
                    sUUID += s_szHex[distribution1(s_oRandomEngine) & 0x3 | 0x8];
                    break;
                default:
                    sUUID += s_szHex[distribution1(s_oRandomEngine)];
                    break;
            }
        }

        return sUUID;
    }
}