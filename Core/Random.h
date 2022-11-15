#pragma once
#include <random>

namespace Devel::Random {
    /**
     * @brief Get a random number between min and max
     * @tparam T
     * @param i_nMinimal
     * @param i_nMaximal
     * @return Random number between min and max
     */
    template<typename T>
    T Generate(T i_nMinimal, T i_nMaximal) {
        static std::random_device s_oRandomDevice;
        static std::mt19937 s_oRandomEngine(s_oRandomDevice());
        return std::uniform_int_distribution<T>(i_nMinimal, i_nMaximal)(s_oRandomEngine);
    }

    /**
     * @brief Get a random uuid
     * @return A random uuid
     */
    std::string GenerateUUID() {
        static std::random_device s_oRandomDevice;
        static std::mt19937 s_oRandomEngine(s_oRandomDevice());
        static std::uniform_int_distribution<> distribution1(0, 15);
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