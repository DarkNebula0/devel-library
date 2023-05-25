#pragma once

#include "Core/Typedef.h"

#include <chrono>

/// @namespace Devel
/// @brief A namespace for development related classes and functions.
namespace Devel {
    /// @class Devel::CTimer
    /// @brief A high-precision timer class.
    ///
    /// This class can be used for timekeeping, measuring the elapsed time, checking if a given time duration has expired, etc.
    ///
    /// <b>Example</b>
    ///
    /// This is an example on how to use the `CTimer` class.
    /// @code{.cpp}
    ///     // Create a CTimer instance and auto start the timer
    ///     Devel::CTimer timer(true);
    ///
    ///     // Do some time-consuming operations
    ///     // ...
    ///
    ///     // Check if a certain time period has expired
    ///     if (timer.hasExpired(1000)) {  // Check if 1000 milliseconds have passed
    ///         // Time period has expired, perform an action
    ///         // ...
    ///     } else {
    ///         // Time period has not expired, do nothing or do something else
    ///         // ...
    ///     }
    ///
    ///     // You can also manually start/restart the timer
    ///     timer.start();
    ///
    ///     // Or check if the timer has started
    ///     bool isStarted = timer.isStarted();
    ///
    ///     // Or reset/clear the timer
    ///     timer.reset();
    /// @endcode
    class CTimer {
    public:
        /// @brief Constructor
        /// @param i_fAutoStart If true, the timer starts automatically upon construction.
        explicit CTimer(const bool i_fAutoStart = false) {
            if (i_fAutoStart) {
                this->start();
            } else {
                this->clear();
            }
        }

        /// @brief Default destructor
        ~CTimer() = default;

    public:
        /// @brief Starts or restarts the timer.
        void start();
        /// @brief Restarts the timer.
        void restart() { return this->start(); }

    public:
        /// @brief Checks if a certain amount of time has passed since the timer was started.
        /// @param i_nTimeMs The amount of time (in milliseconds) to check for.
        /// @return True if the elapsed time is equal to or greater than i_nTimeMs.
        [[nodiscard]] bool hasExpired(const uint64 i_nTimeMs) const {
            return this->isStarted() && (this->elapsed() >= i_nTimeMs);
        }

        /// @brief Checks if the timer is running.
        /// @return True if the timer is started.
        [[nodiscard]] bool isStarted() const { return this->m_fIsStarted; }

    public:
        /// @brief Gets the elapsed time since the timer was started.
        /// @return The elapsed time (in milliseconds).
        [[nodiscard]] uint64 elapsed() const;

    public:
        /// @brief Resets the timer.
        /// The timer is stopped and the elapsed time is set to zero.
        void clear() { return this->reset(); }

        /// @brief Resets the timer.
        /// The timer is stopped and the elapsed time is set to zero.
        void reset() { this->m_fIsStarted = false; }

    private:
        /// @var bool m_fIsStarted
        /// @brief A flag indicating whether the timer is started.
        ///
        /// This flag is set to true when the timer starts, and to false when it is stopped or reset.
        bool m_fIsStarted{};

#ifdef _WIN32
        /// @var LARGE_INTEGER m_oStartTime
        /// @brief The time point when the timer was last started.
        ///
        /// This time point is used to calculate the elapsed time. It is set every time the timer starts,
        /// and is expressed in terms of the steady clock, which provides a stable and continuous time representation.
        std::chrono::time_point<std::chrono::steady_clock> m_oStartTime;
#else
        /// @var LARGE_INTEGER m_oStartTime
        /// @brief The time point when the timer was last started.
        ///
        /// This time point is used to calculate the elapsed time. It is set every time the timer starts,
        /// and is expressed in terms of the system clock, which can be adjusted and may not be monotonic.
        std::chrono::time_point<std::chrono::system_clock> m_oStartTime;
#endif
    };
}