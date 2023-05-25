#pragma once

#include <functional>
#include <vector>

#include "Threading/Mutex/Mutex.h"
#include "Core/Exceptions.h"

/// @def MutexVectorLockGuard(x)
/// @brief Defines a lock guard for a MutexVector. When this macro is used, it creates a lock guard object for the MutexVector's mutex.
///
/// @param x The MutexVector instance to lock.
#define MutexVectorLockGuard(x) RecursiveLockGuard(x.mutex())

/// @def MutexVectorLock(x)
/// @brief Defines a lock for a MutexVector. When this macro is used, it locks the MutexVector's mutex.
///
/// @param x The MutexVector instance to lock.
#define MutexVectorLock(x)        RecursiveLockGuard(x.mutex().lock())
/// @def MutexVectorUnlock(x)
/// @brief Defines an unlock for a MutexVector. When this macro is used, it unlocks the MutexVector's mutex.
///
/// @param x The MutexVector instance to unlock.
#define MutexVectorUnlock(x)    RecursiveLockGuard(x.mutex().unlock())

/// @namespace Devel::Threading
/// @brief The namespace encapsulating threading related classes and functions in the Devel framework.
namespace Devel::Threading {
    /// @class Devel::Threading::CMutexVector<T>
    /// @brief A class for thread-safe handling of vectors.
    ///
    /// This class encapsulates a std::vector<T>, providing an interface
    /// for thread-safe operations on the vector.
    ///
    /// <b>Example</b>
    ///
    /// This class must be used when you want to manipulate a vector in a multi-threaded context.
    /// Here is a simple usage example:
    /// @code{.cpp}
    ///     #include "CMutexVector.h"
    ///     #include <thread>
    ///
    ///     Devel::Threading::CMutexVector<int> mutexVec;
    ///
    ///     void addToVec(int value) {
    ///         mutexVec.push_back(value);
    ///     }
    ///
    ///     int main() {
    ///         // Launch two threads that both add to the vector
    ///         std::thread t1(addToVec, 1);
    ///         std::thread t2(addToVec, 2);
    ///
    ///         // Wait for both threads to finish
    ///         t1.join();
    ///         t2.join();
    ///
    ///         // Print the final size of the vector
    ///         std::cout << "Final vector size: " << mutexVec.size() << std::endl;
    ///
    ///         return 0;
    ///     }
    /// @endcode
    template<typename T>
    class CMutexVector {
#define InClassLock() RecursiveLockGuard(this->m_oMutex)
    public:
        /// @brief Default constructor for CMutexVector.
        CMutexVector() = default;

        /// @brief Copy constructor that takes a non-const reference to a vector.
        explicit CMutexVector(std::vector<T> &i_oVector) {
            this->operator=(i_oVector);
        }

        /// @brief Move constructor that takes an rvalue reference to a vector.
        explicit CMutexVector(std::vector<T> &&i_oVector) {
            this->operator=(std::move(i_oVector));
        }

        /// @brief Copy constructor that takes a const reference to another CMutexVector.
        CMutexVector(const CMutexVector<T> &i_oVector) {
            this->operator=(i_oVector);
        }

        //// @brief Move constructor that takes an rvalue reference to another CMutexVector.
        CMutexVector(CMutexVector<T> &&i_oVector)
        noexcept {
            this->operator=(std::move(i_oVector));
        }

        /// @brief Destructor for CMutexVector.
        virtual ~CMutexVector() = default;

    public:
        typedef std::function<bool(const T &)> FnMatch;

        /// @brief Removes all elements from the vector that match the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return True if any elements were removed, false otherwise.
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

        /// @brief Removes the first element from the vector that matches the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return True if an element was removed, false otherwise.
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

        /// @brief Removes the first element from the vector that matches the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return True if an element was removed, false otherwise.
        bool remove(FnMatch i_fnMatch) {
            return this->removeOne(i_fnMatch);
        }

        /// @brief Finds the first element in the vector that matches the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return The first matching element.
        /// @throws NoEntryFoundException if no matching element is found.
        T find(FnMatch i_fnMatch) const {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    return this->m_atVector[i];
                }
            }

            throw NoEntryFoundException;
        }

        /// @brief Alias for find(FnMatch).
        /// @param i_fnMatch The matching condition.
        /// @return The first matching element.
        /// @throws NoEntryFoundException if no matching element is found.
        T get(FnMatch i_fnMatch) const {
            return this->find(i_fnMatch);
        }

        /// @brief Finds all elements in the vector that match the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return A vector containing all matching elements.
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

        /// @brief Alias for findAll(FnMatch).
        /// @param i_fnMatch The matching condition.
        /// @return A vector containing all matching elements.
        std::vector<T> getAll(FnMatch i_fnMatch) const {
            return this->findAll(i_fnMatch);
        }

        /// @brief Finds the index of the first element in the vector that matches the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return The index of the first matching element.
        /// @return (~0) if no matching element is found.
        size_t findIndex(FnMatch i_fnMatch) const {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    return i;
                }
            }

            return (~0);
        }

        /// @brief Alias for findIndex(FnMatch).
        /// @param i_fnMatch The matching condition.
        /// @return The index of the first matching element.
        /// @return (~0) if no matching element is found.
        size_t indexOf(FnMatch i_fnMatch) const {
            return this->findIndex(i_fnMatch);
        }

        /// @brief Finds all indexes of the elements in the vector that match the given condition.
        /// @param i_fnMatch The matching condition.
        /// @return A vector containing all indexes of the matching elements.
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

        /// @brief Alias for findIndexAll(FnMatch).
        /// @param i_fnMatch The matching condition.
        /// @return A vector containing all indexes of the matching elements.
        std::vector<size_t> indexOfAll(FnMatch i_fnMatch) const {
            return this->findIndexAll(i_fnMatch);
        }

        /// @brief Takes the first element from the vector that matches the given condition and removes it from the vector.
        /// @param i_fnMatch The matching condition.
        /// @return The first matching element.
        /// @throws NoEntryFoundException if no matching element is found.
        T take(FnMatch i_fnMatch) const {
            InClassLock();
            for (size_t i = 0, nSize = this->size(); i < nSize; i++) {
                if (i_fnMatch(this->m_atVector[i])) {
                    T tData = this->m_atVector[i];
                    this->removeAt(i);
                    return tData;
                }
            }

            throw NoEntryFoundException;
        }

        /// @brief Takes all elements from the vector that match the given condition and removes them from the vector.
        /// @param i_fnMatch The matching condition.
        /// @return A vector containing all matching elements.
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
        /// @brief Returns a reference to the underlying mutex of the CMutexVector.
        /// @return A reference to the mutex.
        const CMutex &mutex() const {
            return this->m_oMutex;
        }

        /// @brief Returns a reference to the underlying vector.
        /// @return A reference to the vector.
        const std::vector<T> &rawVector() const {
            return this->m_atVector;
        }

        /// @brief Returns an iterator to the beginning of the vector.
        /// @return An iterator to the beginning.
        auto begin() const {
            return this->m_atVector.begin();
        }

        /// @brief Returns an iterator to the end of the vector.
        /// @return An iterator to the end.
        auto end() const {
            return this->m_atVector.end();
        }

        /// @brief Returns a const iterator to the beginning of the vector.
        /// @return A const iterator to the beginning.
        auto cbegin() const {
            return this->m_atVector.cbegin();
        }

        /// @brief Returns a const iterator to the end of the vector.
        /// @return A const iterator to the end.
        auto cend() const {
            return this->m_atVector.cend();
        }

        /// @brief Returns the size of the vector.
        /// @return The size of the vector.
        size_t size() const {
            return this->m_atVector.size();
        }

        /// @brief Checks if the vector is empty.
        /// @return True if the vector is empty, false otherwise.
        bool isEmpty() const {
            return this->m_atVector.empty();
        }

        /// @brief Returns a reference to the first element in the vector.
        /// @return A reference to the first element.
        T &first() {
            return *this->m_atVector.begin();
        }

        /// @brief Returns a reference to the last element in the vector.
        /// @return A reference to the last element.
        T &last() {
            return *(this->end() - 1);
        }

        /// @brief Returns a reference to the element at the specified index.
        /// @param i_nIndex The index of the element.
        /// @return A reference to the element.
        T &at(const size_t i_nIndex) {
            return this->operator[](i_nIndex);
        }

        /// @brief Converts the CMutexVector to a standard vector.
        /// @return A std::vector<T> containing the elements of the CMutexVector.
        std::vector<T> toStdVector() const {
            return this->m_atVector;
        }

        /// @brief Checks if the vector contains the specified value.
        /// @param i_oValue The value to check for.
        /// @return True if the vector contains the value, false otherwise.
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
        /// @brief Resizes the vector to the specified size.
        /// @param i_nSize The new size of the vector.
        void resize(const size_t i_nSize) {
            InClassLock();
            return this->m_atVector.resize(i_nSize);
        }

        /// @brief Reserves memory for the specified number of elements.
        /// @param i_nSize The number of elements to reserve memory for.
        void reserve(const size_t i_nSize) {
            InClassLock();
            return this->m_atVector.reserve(i_nSize);
        }

        /// @brief Appends a new element to the end of the vector.
        /// @param i_oValue The value to append.
        void push_back(const T &i_oValue) {
            InClassLock();
            return this->m_atVector.push_back(i_oValue);
        }

        /// @brief Moves a new element to the end of the vector.
        /// @param i_oValue The value to move.
        void push_back(T &&i_oValue) {
            InClassLock();
            return this->m_atVector.push_back(std::move(i_oValue));
        }

        /// @brief Appends a vector of elements to the end of the vector.
        /// @param i_atValue The vector of elements to append.
        void push_back(const std::vector<T> &i_atValue) {
            for (const T &oItem: i_atValue) {
                this->push_back(oItem);
            }
        }

        /// @brief Moves a vector of elements to the end of the vector.
        /// @param i_atValue The vector of elements to move.
        void push_back(std::vector<T> &&i_atValue) {
            for (const T &oItem: i_atValue) {
                this->push_back(std::move(oItem));
            }
        }

        /// @brief Appends another CMutexVector to the end of the vector.
        /// @param i_atValue The CMutexVector to append.
        void push_back(const CMutexVector<T> &i_atValue) {
            MutexVectorLockGuard(i_atValue);
            return this->push_back(i_atValue.rawVector());
        }

        /// @brief Moves another CMutexVector to the end of the vector.
        /// @param i_atValue The CMutexVector to move.
        void push_back(CMutexVector<T> &&i_atValue) {
            return this->push_back(std::move(i_atValue.rawVector()));
        }

    public:
        /// @brief Removes the element at the specified index from the vector.
        /// @param i_nIndex The index of the element to remove.
        /// @return True if the element was removed, false otherwise.
        bool removeAt(const size_t i_nIndex) {
            InClassLock();
            if (i_nIndex > this->size()) {
                return false;
            }

            this->m_atVector.erase(this->begin() + i_nIndex);

            return true;
        }

        /// @brief Removes the first occurrence of the specified value from the vector.
        /// @param i_oValue The value to remove.
        /// @return True if the value was removed, false otherwise.
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

        /// @brief Removes all elements from the vector.
        void clear() {
            InClassLock();
            this->m_atVector.clear();
        }

    public:
        /// @brief Assignment operator that copies a std::vector<T> to the CMutexVector.
        /// @param i_tOther The std::vector<T> to copy.
        /// @return A reference to the CMutexVector after assignment.
        CMutexVector &operator=(const std::vector<T> &i_tOther) {
            InClassLock();
            this->m_atVector = i_tOther;
            return *this;
        }

        /// @brief Assignment operator that moves a std::vector<T> to the CMutexVector.
        /// @param i_tOther The std::vector<T> to move.
        /// @return A reference to the CMutexVector after assignment.
        CMutexVector &operator=(std::vector<T> &&i_tOther) {
            InClassLock();
            this->m_atVector = std::move(i_tOther);
            return *this;
        }

        /// @brief Assignment operator that copies another CMutexVector to the CMutexVector.
        /// @param i_tOther The CMutexVector to copy.
        /// @return A reference to the CMutexVector after assignment.
        virtual CMutexVector &operator=(const CMutexVector<T> &i_tOther) {
            InClassLock();
            MutexVectorLockGuard(i_tOther);
            this->operator=(i_tOther.rawVector());
            return *this;
        }

        /// @brief Assignment operator that moves another CMutexVector to the CMutexVector.
        /// @param i_tOther The CMutexVector to move.
        /// @return A reference to the CMutexVector after assignment.
        virtual CMutexVector &operator=(CMutexVector<T> &&i_tOther)
        noexcept {
            InClassLock();
            MutexVectorLockGuard(i_tOther);
            this->operator=(std::move(i_tOther.rawVector()));
            return *this;
        }

        /// @brief Access operator that returns a reference to the element at the specified index.
        /// @param i_nIndex The index of the element.
        /// @return A reference to the element.
        T &operator[](const size_t i_nIndex) {
            if (i_nIndex >= this->size()) {
                throw IndexOutOfRangeException;
            }

            return this->m_atVector[i_nIndex];
        }

        /// @brief Const access operator that returns a const reference to the element at the specified index.
        /// @param i_nIndex The index of the element.
        /// @return A const reference to the element.
        const T &operator[](const size_t i_nIndex) const {
            if (i_nIndex >= this->size()) {
                throw IndexOutOfRangeException;
            }

            return this->m_atVector[i_nIndex];
        }

    private:
        /// @var CMutex m_oMutex
        /// @brief The recursive mutex used for thread-safe operations.
        CMutex m_oMutex;

        /// @var std::vector<T> m_atVector
        /// @brief The underlying vector that the class encapsulates.
        std::vector<T> m_atVector;
    };
}