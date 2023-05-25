#pragma once

#include <thread>
#include <functional>
#include "Threading/SafeQueue/SafeQueue.h"

/// @namespace Devel::Threading
/// @brief The namespace encapsulating threading related classes and functions in the Devel framework.
namespace Devel::Threading {
    typedef std::function<void()> ThreadPoolTaskFn;

    /// @class CThreadPool
    /// @brief A class that implements a thread pool for executing tasks concurrently.
    ///
    /// The CThreadPool class manages a fixed number of worker threads that execute tasks from a task queue.
    class CThreadPool {
    public:
        /// @enum EError
        /// @brief An enumeration of possible errors that can occur when executing the thread pool.
        enum EError {
            ESuccess,           ///< The operation was successful.
            EAlreadyExecuted,   ///< The thread pool has already been executed.
        };

    public:
        /// @brief Default constructor for CThreadPool.
        CThreadPool()
                : m_nWorkerCount(3), m_fIsExecuted(false) {
        }

        /// @brief Constructor that sets the worker count for the thread pool.
        /// @param i_nWorkerCount The number of worker threads in the thread pool.
        explicit CThreadPool(const size_t i_nWorkerCount)
                : CThreadPool() {
            this->setWorkerCount(i_nWorkerCount);
        }

        // @brief Destructor for CThreadPool.
        ~CThreadPool() {
            this->stop();
        }


        /// @brief Deleted copy constructor for CThreadPool.
        /// This copy constructor is explicitly deleted to prevent copying of CThreadPool objects.
        /// @param i_oPool The CThreadPool object to be copied.
        CThreadPool(CThreadPool &i_oPool) = delete;

        /// @brief Deleted constructor for CThreadPool that takes a pointer.
        /// This constructor is explicitly deleted to prevent creation of CThreadPool objects using a pointer to another CThreadPool object.
        /// @param i_pPool A pointer to a CThreadPool object.
        CThreadPool(CThreadPool *i_pPool) = delete;

    public:
        /// @brief Executes the thread pool with the current worker count.
        /// @return The execution result.
        EError execute();

        /// @brief Executes the thread pool with a specified worker count.
        /// @param i_nWorkerCount The number of worker threads to use in the thread pool.
        /// @return The execution result.
        EError execute(const size_t i_nWorkerCount) {
            this->setWorkerCount(i_nWorkerCount);
            return this->execute();
        }

        /// @brief Stops the execution of the thread pool.
        /// @param i_fClearTasks Flag indicating whether to clear the task queue.
        void stop(bool i_fClearTasks = true);

    private:
        /// @brief Worker function that handles executing tasks from the task queue.
        void handleWorker();

    public:
        /// @brief Adds a task to the task queue.
        /// @param i_oTask The task to be added.
        inline void addTask(const ThreadPoolTaskFn &i_oTask) { this->m_aoTasks.enqueue(i_oTask); }

        /// @brief Adds a task to the task queue.
        /// @param i_oTask The task to be added.
        inline void addTask(ThreadPoolTaskFn &&i_oTask) { this->m_aoTasks.enqueue(std::move(i_oTask)); }

        /// @brief Sets the worker count for the thread pool.
        /// @param i_nWorkerCount The number of worker threads to use in the thread pool.
        inline void setWorkerCount(const size_t i_nWorkerCount) {
            this->m_nWorkerCount = (i_nWorkerCount == 0 ? 1 : i_nWorkerCount);
        }

    public:
        /// @brief Returns the current worker count of the thread pool.
        /// @return The worker count.
        size_t workerCount() const { return this->m_nWorkerCount; }

        /// @brief Checks if the thread pool has been executed.
        /// @return True if the thread pool has been executed, false otherwise.
        bool isExecuted() const { return this->m_fIsExecuted; }

    private:
        /// @var size_t m_nWorkerCount
        /// @brief The number of worker threads in the thread pool.
        size_t m_nWorkerCount;

        /// @var std::vector<std::thread> m_aoWorker
        /// @brief The vector of worker threads in the thread pool.
        std::vector<std::thread> m_aoWorker;

        /// @var CSafeQueue<ThreadPoolTaskFn> m_aoTasks
        /// @brief The task queue for the thread pool.
        CSafeQueue<ThreadPoolTaskFn> m_aoTasks;

        /// @var bool m_fIsExecuted
        /// @brief Flag indicating whether the thread pool has been executed.
        bool m_fIsExecuted;
    };
}
