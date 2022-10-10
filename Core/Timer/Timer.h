#pragma once

#include "Core/Typedef.h"

#include <chrono>

namespace Devel {
    class CTimer {
    public:
        CTimer(const bool i_fAutoStart = false) {
            if (i_fAutoStart) {
                this->start();
            } else {
                this->clear();
            }
        }

        ~CTimer() = default;

    public:
        void start();

        void restart() { return this->start(); }

    public:
        bool hasExpired(const uint64 i_nTimeMs) const {
            return this->isStarted() && (this->elapsed() >= i_nTimeMs);
        }

        bool isStarted() const { return this->m_fIsStarted; }

    public:
        uint64 elapsed() const;

    public:
        void clear() { return this->reset(); }

        void reset() { this->m_fIsStarted = false; }

    private:
        bool m_fIsStarted;
#ifdef _WIN32
        std::chrono::time_point<std::chrono::steady_clock> m_oStartTime;
#else
        std::chrono::time_point<std::chrono::system_clock> m_oStartTime;
#endif
    };
} // namespace Devel