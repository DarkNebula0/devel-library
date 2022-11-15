#pragma once

#include "Core/Typedef.h"

#include <chrono>

namespace Devel {
    /**
     * @brief Timer class
     *
     * The CTimer class is a high-level programming interface for timers.
     */
    class CTimer {
    public:
        /**
         * @brief Default constructor
         *
         * Constructs a new CTimer object.
         * @param i_fAutoStart If true, the timer will be started immediately.
         */
        explicit CTimer(const bool i_fAutoStart = false) {
            if (i_fAutoStart) {
                this->start();
            } else {
                this->clear();
            }
        }

        ~CTimer() = default;

    public:
        /**
         * @brief Start the timer
         */
        void start();

        /**
         * @brief Stop the timer
         */
        void restart() { return this->start(); }

    public:
        /**
         * @brief Checks if the timer is expired
         * @param i_nTimeMs The time / interval in milliseconds
         * @return true if the timer is expired, otherwise false
         */
        [[nodiscard]] bool hasExpired(const uint64 i_nTimeMs) const {
            return this->isStarted() && (this->elapsed() >= i_nTimeMs);
        }

        /**
         * @brief Get current timer state
         * @return true if the timer is started, otherwise false
         */
        [[nodiscard]] bool isStarted() const { return this->m_fIsStarted; }

    public:
        /**
         * @brief Get the elapsed time in milliseconds
         * @return Elapsed time in milliseconds
         */
        [[nodiscard]] uint64 elapsed() const;

    public:
        /**
         * @brief Clear the timer
         */
        void clear() { return this->reset(); }

        /**
         * @brief Reset the timer
         */
        void reset() { this->m_fIsStarted = false; }

    private:
        bool m_fIsStarted{};

#ifdef _WIN32
        std::chrono::time_point<std::chrono::steady_clock> m_oStartTime;
#else
        std::chrono::time_point<std::chrono::system_clock> m_oStartTime;
#endif
    };
} // namespace Devel