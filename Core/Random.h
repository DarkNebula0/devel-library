#pragma once

#include <random>

namespace Devel::Random {
    template<typename T>
    T Generate(T i_nMinimal, T i_nMaximal) {
        static std::random_device s_oRandomDevice;
        static std::default_random_engine s_oDefaultRandomEngine(s_oRandomDevice());

        return std::uniform_int_distribution<T>(i_nMinimal, i_nMaximal)(s_oDefaultRandomEngine);
    }
}