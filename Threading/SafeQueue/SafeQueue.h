#pragma once

#include <queue>

#include "Threading/LockGuard/LockGuard.h"
#include "Core/Typedef.h"
#include "Core/Global.h"
#include "Core/Exceptions.h"

/// @def SafeQueueLockGuard(x)
/// @brief Defines a lock guard for a safe queue.
/// When this macro is used, it creates a lock guard object for the safe queue's mutex.
/// @param x The safe queue instance to lock.
#define SafeQueueLockGuard(x)    RecursiveLockGuard(x.mutex())

/// @def SafeQueueLock(x)
/// @brief Defines a lock for a safe queue.
/// When this macro is used, it locks the safe queue's mutex.
/// @param x The safe queue instance to lock.
#define SafeQueueLock(x)        x.mutex().lock()

/// @def SafeQueueUnlock(x)
/// @brief Defines an unlock for a safe queue.
/// When this macro is used, it unlocks the safe queue's mutex.
/// @param x The safe queue instance to unlock.
#define SafeQueueUnlock(x)        x.mutex().unlock()

/// @namespace Devel::Threading
/// @brief The namespace encapsulating threading related classes and functions in the Devel framework.
namespace Devel::Threading {
    /// @class Devel::Threading::CSafeQueue<T>
    /// @brief A thread-safe implementation of a queue.
    ///
    /// This class provides a thread-safe queue implementation using std::queue internally.
    /// It allows multiple threads to enqueue and dequeue elements from the queue concurrently.
    ///
    /// @tparam T The type of elements stored in the queue.
    ///
    /// <b>Example</b>
    ///
    /// This example shows how to use the CSafeQueue class to manage access to a shared counter variable in a multi-threaded environment.
    /// The CSafeQueue ensures that only one thread can access the shared counter at a time, preventing data races and ensuring thread-safety.
    /// Each thread dequeues a value from the safe queue and increments the shared counter by that value.
    /// Finally, the example prints the final value of the shared counter after all threads have finished.
    ///
    /// @code{.cpp}
    /// #include "Threading/SafeQueue.h"
    /// #include <iostream>
    /// #include <thread>
    ///
    /// /// Shared resource - counter variable
    /// int sharedCounter = 0;
    ///
    /// /// Safe queue for managing access to the shared resource
    /// Devel::Threading::CSafeQueue<int> safeQueue;
    ///
    /// /// Function executed by threads to increment the shared counter
    /// void incrementCounter() {
    /// int value;
    /// while (true) {
    /// // Dequeue a value from the safe queue
    /// value = safeQueue.dequeue();
    ///
    /// // Exit the loop if the value is a termination signal
    /// if (value == -1) {
    /// break;
    /// }
    ///
    /// // Increment the shared counter
    /// sharedCounter++;
    /// }
    /// }
    ///
    /// int main() {
    /// // Create multiple threads
    /// const int numThreads = 4;
    /// std::vectorstd::thread threads(numThreads);
    ///
    /// // Enqueue values in the safe queue to increment the counter
    /// for (int i = 0; i < numThreads; i++) {
    /// safeQueue.enqueue(1);
    /// }
    ///
    /// // Start the threads
    /// for (int i = 0; i < numThreads; i++) {
    /// threads[i] = std::thread(incrementCounter);
    /// }
    ///
    /// // Wait for all threads to finish
    /// for (int i = 0; i < numThreads; i++) {
    /// threads[i].join();
    /// }
    ///
    /// // Print the final value of the counter
    /// std::cout << "Final counter value: " << sharedCounter << std::endl;
    ///
    /// // Clear the safe queue
    /// safeQueue.clear();
    ///
    /// return 0;
    /// }
    /// @endcode
    template<class T>
    class CSafeQueue {
    public:
        /// @brief Returns a const reference to the mutex associated with the safe queue.
        /// @return The mutex object.
        const CMutex &mutex() const {
            return this->m_oMutex;
        }

        /// @brief Returns the number of elements in the safe queue.
        /// @return The number of elements.
        size_t size() const {
            return this->m_aQueue.size();
        }

        /// @brief Checks if the safe queue is empty.
        /// @return True if the safe queue is empty, false otherwise.
        bool isEmpty() const {
            return this->m_aQueue.empty();
        }

    public:
        /// @brief Enqueues an element into the safe queue.
        /// @param i_tValue The element to enqueue.
        void enqueue(const T &i_tValue) {
            RecursiveLockGuard(this->m_oMutex);
            this->m_aQueue.push(i_tValue);
        }

        /// @brief Enqueues an rvalue reference to an element into the safe queue.
        /// @param i_tValue The rvalue reference to an element to enqueue.
        void enqueue(T &&i_tValue) {
            RecursiveLockGuard(this->m_oMutex);
            this->m_aQueue.push(std::move(i_tValue));
        }

    public:
        /// @brief Dequeues and returns an element from the safe queue.
        /// @param i_fMove If true, the returned element is moved, otherwise a copy is made.
        /// @return The dequeued element.
        T dequeue(const bool i_fMove = true) {
            RecursiveLockGuard(this->m_oMutex);

            T tValue = this->front(i_fMove);
            this->pop();

            return tValue;
        }

    public:
        /// @brief Returns a reference to the front element of the safe queue without removing it.
        /// @param i_fMove If true, the front element is moved, otherwise a copy is made.
        /// @return The reference to the front element.
        T front(const bool i_fMove = false) {
            RecursiveLockGuard(this->m_oMutex);

            if (this->isEmpty()) {
                throw NoEntryFoundException;
            }

            return (i_fMove ? std::move(this->m_aQueue.front()) : this->m_aQueue.front());
        }

        /// @brief Removes the front element from the safe queue.
        void pop() {
            RecursiveLockGuard(this->m_oMutex);

            if (this->isEmpty()) {
                throw NoEntryFoundException;
            }

            this->m_aQueue.pop();
        }

        /// @brief Removes all elements from the safe queue.
        void clear() {
            RecursiveLockGuard(this->m_oMutex);

            try {
                while (true) {
                    this->pop();
                }
            } catch (const std::range_error &) {}
        }

    private:
        /// @var std::queue<T> m_aQueue
        /// @brief The underlying queuet.
        std::queue<T> m_aQueue;

        /// @var CMutex m_oMutex
        /// @brief The mutex used to synchronize access to the queue.
        CMutex m_oMutex;
    };
};