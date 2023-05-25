#pragma once

#include "Core/Global.h"
#include "Threading/Mutex/Mutex.h"
/// @namespace Devel::Threading
/// @brief The namespace encapsulating threading related classes and functions in the Devel framework.
namespace Devel::Threading {
    /// @def RecursiveLockGuard(x)
    /// @brief Defines a lock guard for a recursive mutex.
    /// When this macro is used, it creates a lock guard object for the recursive mutex.
    /// @param x The recursive mutex instance to lock.
#define RecursiveLockGuard(x)    CLockGuard CatUniqueVar(locker, __COUNTER__)(x);

    /// @class Devel::Threading::CLockGuard
    /// @brief A lock guard class for a recursive mutex.
    ///
    /// This class provides a convenient way to acquire and release a lock on a recursive mutex.
    ///
    /// Example usage:
    /// @code{.cpp}
    ///     CMutex mutex;
    ///     {
    ///         RecursiveLockGuard(mutex); // Acquires the lock on the mutex
    ///         // Critical section
    ///         // The lock will be automatically released when the lock guard goes out of scope
    ///     }
    /// @endcode
    class CLockGuard {
    public:
        /// @brief Constructs a CLockGuard and acquires the lock on the specified mutex.
        /// @param i_oMutex The recursive mutex to lock.
        CLockGuard(const CMutex &i_oMutex)
                : m_oMutex(i_oMutex) {
            this->m_oMutex.lock();
        }

        /// @brief Destroys the CLockGuard and releases the lock on the mutex.
        ~CLockGuard() {
            this->m_oMutex.unlock();
        }

    private:
        /// @var CMutex &m_oMutex
        /// @brief The recursive mutex to guard.
        const CMutex &m_oMutex;
    };
}