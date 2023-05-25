#pragma once

#include <mutex>

/// @namespace Devel::Threading
/// @brief The namespace encapsulating threading related classes and functions in the Devel framework.
namespace Devel::Threading {
    /// @class Devel::Threading::CMutex
    /// @brief A class for handling recursive mutexes.
    ///
    /// This class encapsulates a std::recursive_mutex, providing an interface
    /// for locking and unlocking the mutex.
    ///
    /// <b>Example</b>
    ///
    /// This class must be used when you want to protect a shared resource from
    /// simultaneous access by multiple threads. Here is a simple usage example:
    ///
    /// @code{.cpp}
    ///     #include "CMutex.h"
    ///     #include <thread>
    ///
    ///     Devel::Threading::CMutex mutex;
    ///     int sharedCounter = 0;
    ///
    ///     void incrementCounter() {
    ///         mutex.lock();
    ///         sharedCounter++;
    ///         mutex.unlock();
    ///     }
    ///
    ///     int main() {
    ///         // Launch two threads that both increment the shared counter
    ///         std::thread t1(incrementCounter);
    ///         std::thread t2(incrementCounter);
    ///
    ///         // Wait for both threads to finish
    ///         t1.join();
    ///         t2.join();
    ///
    ///         // Print the final value of the counter
    ///         std::cout << "Final counter value: " << sharedCounter << std::endl;
    ///
    ///         return 0;
    ///     }
    /// @endcode
    class CMutex {
    public:
        /// @brief Default constructor for CMutex.
        CMutex() = default;

        /// @brief Default virtual destructor for CMutex.
        virtual ~CMutex() = default;

    public:
        /// @brief Locks the mutex. If the mutex is currently locked by another
        /// thread, this call will block the calling thread until the mutex is unlocked.
        void lock() const {
            return this->m_oMutex.lock();
        }

        /// @brief Unlocks the mutex.
        void unlock() const {

            return this->m_oMutex.unlock();
        }

        /// @brief Attempts to lock the mutex. If the mutex is not available for
        /// locking, this function returns immediately with a value of false. If
        /// the mutex is available for locking, the function locks the mutex and returns true.
        /// @return True if the mutex was successfully locked, false otherwise.
        bool tryLock() const {
            return this->m_oMutex.try_lock();
        }

    private:
        /// @var std::recursive_mutex m_oMutex
        /// @brief The recursive mutex instance managed by this class.
        mutable std::recursive_mutex m_oMutex;
    };
}
