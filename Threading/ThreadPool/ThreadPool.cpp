#include "ThreadPool.h"
#include "Threading/ThreadUtils.h"


Devel::Threading::CThreadPool::EError Devel::Threading::CThreadPool::execute() {
    if (!this->m_fIsExecuted) {
        this->m_aoWorker.reserve(this->m_nWorkerCount);
        this->m_fIsExecuted = true;

        for (size_t i = 0; i < this->m_nWorkerCount; i++) {
            this->m_aoWorker.emplace_back(&CThreadPool::handleWorker, this);
        }

        return CThreadPool::EError::ESuccess;
    }

    return CThreadPool::EError::EAlreadyExecuted;
}

void Devel::Threading::CThreadPool::stop(bool i_fClearTasks) {
    if (this->m_fIsExecuted) {
        this->m_fIsExecuted = false;

        for (std::thread &oWorker: this->m_aoWorker) {
            if (oWorker.joinable()) {
                oWorker.join();
            }
        }

        if (i_fClearTasks) {
            this->m_aoTasks.clear();
        }

        this->m_aoWorker.clear();
    }
}

void Devel::Threading::CThreadPool::handleWorker() {
    while (this->m_fIsExecuted) {

        if (this->m_aoTasks.isEmpty()) {
            Devel::Threading::Utils::sleep(3);
            continue;
        }

        ThreadPoolTaskFn fnTask = nullptr;

        try {
            fnTask = this->m_aoTasks.dequeue();
        } catch (const CNoEntryFoundException &) {}

        if (fnTask) {
            fnTask();
        }
    }
}