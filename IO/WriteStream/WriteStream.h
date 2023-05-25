#pragma once

#include "Core/Exceptions.h"
#include "IO/Buffer/Buffer.h"
#include "Core/CharArray/CharArray.h"

#include <type_traits>
#include <string>

namespace Devel::IO {
    /// @class Devel::IO::CWriteStream
    /// @brief A class for writing data to a buffer.
    /// This class provides functionality to write data to a buffer. It allows pushing strings, raw data, and numeric values to the buffer.
    ///
    /// <b>Example</b>
    /// @code{.cpp}
    /// // Create a write stream
    /// Devel::IO::CWriteStream stream;
    ///
    /// // Push a string to the stream
    /// stream.push("Hello, World!");
    ///
    /// // Push raw data to the stream
    /// char rawData[] = { 'R', 'a', 'w', 'D', 'a', 't', 'a' };
    /// stream.push(rawData, sizeof(rawData));
    ///
    /// // Push a numeric value to the stream
    /// int num = 42;
    /// stream.push(num);
    ///
    /// // Get the buffer and its size
    /// const char* buffer = stream.buffer();
    /// size_t bufferSize = stream.size();
    ///
    /// // Print the buffer
    /// std::cout << "Buffer: ";
    /// for (size_t i = 0; i < bufferSize; ++i) {
    /// std::cout << buffer[i];
    /// }
    /// std::cout << std::endl;
    /// @endcode
    class CWriteStream {
    public:

        /// @brief Default constructor.
        CWriteStream()
                : m_pBuffer(nullptr), m_nSize(0), m_nAllocatedSize(0) {
        }

        /// @brief Constructor with initial size.
        /// @param i_nSize The initial size of the buffer.
        explicit CWriteStream(const size_t i_nSize)
                : CWriteStream() {
            this->reallocate(i_nSize);
        }

        /// @brief Copy constructor.
        /// @param i_oOther The CWriteStream object to be copied.
        CWriteStream(const CWriteStream &i_oOther) : CWriteStream() { this->operator=(i_oOther); }

        /// @brief Move constructor.
        /// @param i_oWriteStream The CWriteStream object to be moved.
        CWriteStream(CWriteStream &&i_oWriteStream) noexcept {
            this->operator=(std::move(i_oWriteStream));
        }

        /// @brief Destructor.
        virtual ~CWriteStream() {
            this->deleteBuffer();
        }

    private:
        /// @brief Delete the buffer.
        /// @details This function will delete the underlying buffer, freeing up any memory that has been allocated.
        /// @warning This function should be used with care, as any subsequent operations on the buffer may lead to undefined behavior.
        void deleteBuffer();

    public:
        /// @brief Clears the stream by setting the size to 0.
        void clear() {
            this->m_nSize = 0;
        }

        /// @brief Reallocates the buffer to the given size.
        /// @param i_nSize The new size of the buffer.
        void reallocate(size_t i_nSize);

    public:
        /// @brief Pushes the specified data to the buffer.
        /// @param i_pBuffer Pointer to the data to be pushed.
        /// @param i_nSize The size of the data to be pushed.
        void push(const void *i_pBuffer, size_t i_nSize);

        /// @brief Pushes the data from another CWriteStream to the buffer.
        /// @param i_oStream The CWriteStream object to be pushed.
        void push(const CWriteStream &i_oStream) {
            if (i_oStream.size() > 0) {
                return this->push(i_oStream.buffer(), i_oStream.size());
            }
        }

        /// @brief Pushes a null-terminated string to the buffer.
        /// @param i_szString The null-terminated string to be pushed.
        void push(const char *i_szString) {
            return this->push(i_szString, strlen(i_szString));
        }

        /// @brief Pushes a std::string to the buffer.
        /// @param i_oString The std::string to be pushed.
        /// @param i_fZeroTerminated Whether to include a null-terminator at the end of the string.
        void push(const std::string &i_oString, const bool i_fZeroTerminated = true) {
            if (!i_oString.empty()) {
                return this->push(i_oString.c_str(), i_oString.size() + (i_fZeroTerminated));
            }
        }

        /// @brief Pushes a std::wstring to the buffer.
        /// @param i_oString The std::wstring to be pushed.
        /// @param i_fZeroTerminated Whether to include a null-terminator at the end of the string.
        void push(const std::wstring &i_oString, const bool i_fZeroTerminated = true) {
            if (!i_oString.empty()) {
                return this->push(i_oString.c_str(), i_oString.size() * 2 + (i_fZeroTerminated * 2));
            }
        }

        /// @brief Pushes a numeric value to the buffer.
        /// @tparam T The type of the numeric value.
        /// @param i_oValue The numeric value to be pushed.
        template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
        void push(const T &i_oValue) {
            this->reallocate(this->m_nSize + sizeof(T));

            *reinterpret_cast<T *>((this->m_pBuffer + this->m_nSize)) = i_oValue;
            this->m_nSize += sizeof(T);
        }

        /// @brief Pushes an enum value to the buffer.
        /// @tparam T The type of the enum.
        /// @param i_oValue The enum value to be pushed.
        template<typename T, typename std::enable_if_t<std::is_enum_v<T>> * = nullptr>
        void push(const T &i_oValue) {
            this->reallocate(this->m_nSize + sizeof(T));

            *reinterpret_cast<T *>((this->m_pBuffer + this->m_nSize)) = i_oValue;
            this->m_nSize += sizeof(T);
        }

        /// @brief Pushes a CCharArray to the buffer.
        /// @tparam TSize The size of the CCharArray.
        /// @param i_oValue The CCharArray to be pushed.
        /// @param i_bMaxLength Whether to push the maximum length of the CCharArray or its current length.
        template<size_t TSize>
        void push(const CCharArray<TSize> &i_oValue, const bool i_bMaxLength = true) {
            this->push(i_oValue.begin(), i_bMaxLength ? i_oValue.maxLength() : i_oValue.length());
        }

    public:
        /// @brief Replaces a portion of the buffer with the specified data.
        /// @param i_nPosition The position in the buffer to start replacing.
        /// @param i_pBuffer Pointer to the data to be replaced.
        /// @param i_nSize The size of the data to be replaced.
        void replace(const size_t i_nPosition, const void *i_pBuffer, const size_t i_nSize) const {
            if (this->m_nSize >= i_nPosition + i_nSize) {
                memcpy(this->m_pBuffer + i_nPosition, i_pBuffer, i_nSize);
            } else {
                throw IndexOutOfRangeException;
            }
        }

        /// @brief Replaces a portion of the buffer with the data from another CWriteStream.
        /// @param i_nPosition The position in the buffer to start replacing.
        /// @param i_oStream The CWriteStream object whose data will replace the buffer portion.
        void replace(const size_t i_nPosition, const CWriteStream &i_oStream) const {
            if (i_oStream.size() > 0) {
                this->replace(i_nPosition, i_oStream.buffer(), i_oStream.size());
            }
        }

        /// @brief Replaces a portion of the buffer with a null-terminated string.
        /// @param i_nPosition The position in the buffer to start replacing.
        /// @param i_szString The null-terminated string to be replaced.
        void replace(const size_t i_nPosition, const char *i_szString) const {
            return this->replace(i_nPosition, i_szString, strlen(i_szString));
        }

        /// @brief Replaces a portion of the buffer with a std::string.
        /// @param i_nPosition The position in the buffer to start replacing.
        /// @param i_oString The std::string to be replaced.
        void replace(const size_t i_nPosition, const std::string &i_oString) const {
            return this->replace(i_nPosition, i_oString.c_str(), i_oString.size());
        }

        /// @brief Replaces a portion of the buffer with a numeric value.
        /// @tparam T The type of the numeric value.
        /// @param i_nPosition The position in the buffer to start replacing.
        /// @param i_oValue The numeric value to be replaced.
        template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
        void replace(const size_t i_nPosition, const T &i_oValue) {
            if (this->m_nSize >= i_nPosition + sizeof(T)) {
                *reinterpret_cast<T *>((this->m_pBuffer + i_nPosition)) = i_oValue;
            } else {
                throw IndexOutOfRangeException;
            }
        }

        /// @brief Replaces a portion of the buffer with an enum value.
        /// @tparam T The type of the enum.
        /// @param i_nPosition The position in the buffer to start replacing.
        /// @param i_oValue The enum value to be replaced.
        template<typename T, typename std::enable_if_t<std::is_enum_v<T>> * = nullptr>
        void replace(const size_t i_nPosition, const T &i_oValue) {
            if (this->m_nSize >= i_nPosition + sizeof(T)) {
                *reinterpret_cast<T *>((this->m_pBuffer + i_nPosition)) = i_oValue;
            } else {
                throw IndexOutOfRangeException;
            }
        }

    public:
        /// @brief Gets the allocated size of the buffer.
        /// @return The allocated size of the buffer.
        [[nodiscard]] size_t allocatedSize() const {
            return this->m_nAllocatedSize;
        }

        /// @brief Gets the current size of the buffer.
        /// @return The current size of the buffer.
        [[nodiscard]] size_t size() const {
            return this->m_nSize;
        }

        /// @brief Gets a const pointer to the buffer.
        /// @return A const pointer to the buffer.
        [[nodiscard]] const char *buffer() const {
            return this->m_pBuffer;
        }

    public:
        /// @brief Copy assignment operator.
        /// @param i_oOther The CWriteStream object to be assigned.
        /// @return Reference to the assigned CWriteStream object.
        CWriteStream &operator=(const CWriteStream &i_oOther) {
            this->clear();
            this->push(i_oOther.m_pBuffer, i_oOther.m_nSize);
            return *this;
        }

        /// @brief Move assignment operator.
        /// @param i_oOther The CWriteStream object to be moved.
        /// @return Reference to the moved CWriteStream object.
        CWriteStream &operator=(CWriteStream &&i_oOther) noexcept {
            this->deleteBuffer();

            this->m_pBuffer = i_oOther.m_pBuffer;
            this->m_nAllocatedSize = i_oOther.m_nAllocatedSize;
            this->m_nSize = i_oOther.m_nSize;

            i_oOther.m_pBuffer = nullptr;
            i_oOther.m_nAllocatedSize = 0;
            i_oOther.m_nSize = 0;

            return *this;
        }

    private:
        /// @var Devel::IO::CWriteStream::m_pBuffer
        /// @brief The pointer to the buffer storing the written data.
        char *m_pBuffer{};
        /// @var Devel::IO::CWriteStream::m_nSize
        /// @brief The current size of the buffer.
        size_t m_nSize{};
        /// @var Devel::IO::CWriteStream::m_nAllocatedSize
        /// @brief The allocated size of the buffer.
        size_t m_nAllocatedSize{};
    };
}