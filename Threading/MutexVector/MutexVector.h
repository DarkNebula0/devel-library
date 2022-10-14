#pragma once

#include <functional>
#include <vector>

#include "Threading/Mutex/Mutex.h"
#include "Core/Exceptions.h"

#define MutexVectorLockGuard(x) RecursiveLockGuard(x.mutex())
#define MutexVectorLock(x)        RecursiveLockGuard(x.mutex().lock())
#define MutexVectorUnlock(x)    RecursiveLockGuard(x.mutex().unlock())

namespace Devel::Threading {
    template<typename T>
    class CMutexVector {
#define InClassLock() RecursiveLockGuard(this->m_oMutex)

        CreateFastException(CNoEntryFoundException, "No entry found!");

        CreateFastException(CIndexOutOfRangeException, "Passed index is out of range!");
    public:
        CMutexVector() = default;

        explicit CMutexVector(std::vector<T> &i_oVector) {
            this->operator=(i_oVector);
        }

        explicit CMutexVector(std::vector<T> &&i_oVector) {
            this->operator=(std::move(i_oVector));
        }

        CMutexVector(const CMutexVector<T> &i_oVector) {
            this->operator=(i_oVector);
        }

        CMutexVector(CMutexVector<T> &&i_oVector)
        noexcept {
            this->operator=(std::move(i_oVector));
        }

        virtual ~CMutexVector() = default;

    public:
        typedef std::function<bool(const T &)> FnMatch;

        bool removeAll(FnMatch i_fnMatch) {
            bool fWasSuccessful = false;

            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize;) {
                if (i_fnMatch(this->m_atVector[i])) {
                    nSize--;
                    this->removeAt(i);
                    fWasSuccessful = true;
                } else {
                    i++;
                }
            }

            return fWasSuccessful;
        }

        bool removeOne(FnMatch i_fnMatch) {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    this->removeAt(i);
                    return true;
                }
            }

            return false;
        }

        bool remove(FnMatch i_fnMatch) {
            return this->removeOne(i_fnMatch);
        }


        T find(FnMatch i_fnMatch) const {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    return this->m_atVector[i];
                }
            }

            throw CNoEntryFoundException();
        }

        T get(FnMatch i_fnMatch) const {
            return this->find(i_fnMatch);
        }

        std::vector<T> findAll(FnMatch i_fnMatch) const {
            std::vector<T> atData;

            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    atData.push_back(this->m_atVector[i]);
                }
            }

            return atData;
        }

        std::vector<T> getAll(FnMatch i_fnMatch) const {
            return this->findAll(i_fnMatch);
        }


        size_t findIndex(FnMatch i_fnMatch) const {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    return i;
                }
            }

            return (~0);
        }

        size_t indexOf(FnMatch i_fnMatch) const {
            return this->findIndex(i_fnMatch);
        }

        std::vector<size_t> findIndexAll(FnMatch i_fnMatch) const {
            std::vector<size_t> anIndexes;

            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    anIndexes.push_back(i);
                }
            }

            return anIndexes;
        }

        std::vector<size_t> indexOfAll(FnMatch i_fnMatch) const {
            return this->findIndexAll(i_fnMatch);
        }


        T take(FnMatch i_fnMatch) const {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    T tData = this->m_atVector[i];
                    this->removeAt(i);
                    return tData;
                }
            }

            throw CNoEntryFoundException();
        }

        std::vector<T> takeAll(FnMatch i_fnMatch) const {
            std::vector<T> atData;

            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize;) {
                if (i_fnMatch(this->m_atVector[i])) {
                    atData.push_back(this->m_atVector[i]);
                    this->removeAt(i);
                    nSize--;
                } else {
                    i++;
                }
            }

            return atData;
        }

    public:
        const CMutex &mutex() const {
            return this->m_oMutex;
        }

        const std::vector<T> &rawVector() const {
            return this->m_atVector;
        }

        auto begin() const {
            return this->m_atVector.begin();
        }

        auto end() const {
            return this->m_atVector.end();
        }

        auto cbegin() const {
            return this->m_atVector.cbegin();
        }

        auto cend() const {
            return this->m_atVector.cend();
        }

        size_t size() const {
            return this->m_atVector.size();
        }

        bool isEmpty() const {
            return this->m_atVector.empty();
        }

        T &first() {
            return *this->m_atVector.begin();
        }

        T &last() {
            return *(this->end() - 1);
        }

        T &at(const size_t i_nIndex) {
            return this->operator[](i_nIndex);
        }

        std::vector<T> toStdVector() const {
            return this->m_atVector;
        }

        bool contains(const T &i_oValue) const {
            InClassLock();
            for (const T &tValue: this->m_atVector) {
                if (tValue == i_oValue) {
                    return true;
                }
            }

            return false;
        }

    public:
        void resize(const size_t i_nSize) {
            InClassLock();
            return this->m_atVector.resize(i_nSize);
        }

        void reserve(const size_t i_nSize) {
            InClassLock();
            return this->m_atVector.reserve(i_nSize);
        }

        void push_back(const T &i_oValue) {
            InClassLock();
            return this->m_atVector.push_back(i_oValue);
        }

        void push_back(T &&i_oValue) {
            InClassLock();
            return this->m_atVector.push_back(std::move(i_oValue));
        }

        void push_back(const std::vector<T> &i_atValue) {
            for (const T &oItem: i_atValue) {
                this->push_back(oItem);
            }
        }

        void push_back(std::vector<T> &&i_atValue) {
            for (const T &oItem: i_atValue) {
                this->push_back(std::move(oItem));
            }
        }

        void push_back(const CMutexVector<T> &i_atValue) {
            MutexVectorLockGuard(i_atValue);
            return this->push_back(i_atValue.rawVector());
        }

        void push_back(CMutexVector<T> &&i_atValue) {
            return this->push_back(std::move(i_atValue.rawVector()));
        }

    public:
        bool removeAt(const size_t i_nIndex) {
            InClassLock();
            if (i_nIndex > this->size()) {
                return false;
            }

            this->m_atVector.erase(this->begin() + i_nIndex);

            return true;
        }

        bool remove(const T &i_oValue) {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (this->m_atVector[i] == i_oValue) {
                    this->removeAt(i);
                    return true;
                }
            }
            return false;
        }

        void clear() {
            InClassLock();
            this->m_atVector.clear();
        }

    public:
        CMutexVector &operator=(const std::vector<T> &i_tOther) {
            InClassLock();
            this->m_atVector = i_tOther;
            return *this;
        }

        CMutexVector &operator=(std::vector<T> &&i_tOther) {
            InClassLock();
            this->m_atVector = std::move(i_tOther);
            return *this;
        }

        CMutexVector &operator=(const CMutexVector<T> &i_tOther) {
            InClassLock();
            MutexVectorLockGuard(i_tOther);
            this->operator=(i_tOther.rawVector());
            return *this;
        }

        CMutexVector &operator=(CMutexVector<T> &&i_tOther)
        noexcept {
            InClassLock();
            MutexVectorLockGuard(i_tOther);
            this->operator=(std::move(i_tOther.rawVector()));
            return *this;
        }

        T &operator[](const size_t i_nIndex) {
            if (i_nIndex >= this->size()) {
                throw CIndexOutOfRangeException();
            }

            return this->m_atVector[i_nIndex];
        }

        const T &operator[](const size_t i_nIndex) const {
            if (i_nIndex >= this->size()) {
                throw CIndexOutOfRangeException();
            }

            return this->m_atVector[i_nIndex];
        }

    private:
        CMutex m_oMutex;
        std::vector<T> m_atVector;
    };
}