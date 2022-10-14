#pragma once

#include "Core/Global.h"
#include <thread>

namespace Devel::Threading::Utils {
    static void sleep(size_t i_nMilliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(i_nMilliseconds));
    }
}