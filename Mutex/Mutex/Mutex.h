#pragma once
#include <mutex>

class CMutex
{
public:
    CMutex() = default;
    virtual ~CMutex() = default;

public:
    void lock() const
    {
        return this->m_oMutex.lock();
    }

    void unlock() const
    {
        return this->m_oMutex.unlock();
    }

    bool tryLock() const
    {
        return this->m_oMutex.try_lock();
    }

private:
    mutable std::recursive_mutex m_oMutex;
};
