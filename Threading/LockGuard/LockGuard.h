#pragma once

#include "Core/Global.h"
#include "Threading/Mutex/Mutex.h"

namespace Devel::Threading {
#define RecursiveLockGuard(x)    CLockGuard CatUniqueVar(locker, __COUNTER__)(x);

    class CLockGuard {
    public:
        CLockGuard(const CMutex &i_oMutex)
                : m_oMutex(i_oMutex) {
            this->m_oMutex.lock();
        }

        ~CLockGuard() {
            this->m_oMutex.unlock();
        }

    private:
        const CMutex &m_oMutex;
    };
}