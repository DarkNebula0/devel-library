#include "Timer.h"

void Devel::CTimer::start() {
    this->m_fIsStarted = true;
    this->m_oStartTime = std::chrono::high_resolution_clock::now();
}

uint64 Devel::CTimer::elapsed() const {
    return static_cast<uint64>(this->isStarted() ? std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::high_resolution_clock::now() - this->m_oStartTime).count() : 0);
}