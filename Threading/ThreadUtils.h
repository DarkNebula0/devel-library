#pragma once

#include "Core/Global.h"
#include <thread>

/// @namespace Devel::Threading::Utils
/// @brief The namespace encapsulating threading related utility functions in the Devel framework.
namespace Devel::Threading::Utils {
    /// @brief Pauses the execution of the current thread for the specified number of milliseconds.
    ///
    /// This function causes the current thread to sleep for the specified duration.
    /// The execution of the thread is suspended, and no CPU time is consumed during the sleep period.
    ///
    /// @param i_nMilliseconds The number of milliseconds to sleep.
    static void sleep(size_t i_nMilliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(i_nMilliseconds));
    }
}