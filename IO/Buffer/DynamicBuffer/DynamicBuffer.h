#pragma once

#include "IO/Buffer/Buffer.h"

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    /// @class Devel::IO::CDynamicBuffer
    /// @brief A dynamic implementation of the IBuffer interface.
    ///
    /// This class represents a buffer of bytes that can be resized dynamically,
    /// providing a flexible way to interact with variable-sized data.
    ///
    /// <b>Example</b>
    ///
    /// Here's an example of how you might use a CDynamicBuffer:
    ///
    /// @code{.cpp}
    ///     Devel::IO::CDynamicBuffer buf(1024); // Creating a dynamic buffer of 1024 bytes
    ///     // Fill the buffer...
    ///     const char *buffer = buf.buffer();
    ///     size_t bufferSize = buf.size();
    ///     // Resize the buffer...
    ///     buf.reallocate(2048);
    ///     bufferSize = buf.size();
    /// @endcode
    class CDynamicBuffer : public IBuffer {
    public:
        /// @brief Default constructor.
        CDynamicBuffer();

        /// @brief Overloaded constructor.
        /// @param i_nSize The initial size of the buffer.
        CDynamicBuffer(const size_t i_nSize);

        /// @brief Copy constructor.
        /// @param i_oOther The object to copy from.
        CDynamicBuffer(const CDynamicBuffer &i_oOther) {
            this->operator=(i_oOther);
        }

        /// @brief Move constructor.
        /// @param i_oOther The object to move from.
        CDynamicBuffer(CDynamicBuffer &&i_oOther) noexcept {
            this->operator=(std::move(i_oOther));
        }

        /// @brief Virtual destructor.
        virtual ~CDynamicBuffer();

    private:
        /// @brief Delete the buffer.
        /// @details This function will delete the underlying buffer, freeing up any memory that has been allocated.
        /// @warning This function should be used with care, as any subsequent operations on the buffer may lead to undefined behavior.
        void deleteBuffer();

    private:
        /// @brief Check if the buffer is valid.
        /// @details This function will check if the buffer is not a null pointer.
        /// @exception NoBufferException If the buffer is a null pointer, this function will throw a NoBufferException.
        void checkBuffer() {
            if (!this->m_pBuffer) {
                throw NoBufferException;
            }
        }

    public:
        /// @brief Reallocate the buffer to a new size.
        /// @param i_nSize The new size for the buffer.
        void reallocate(const size_t i_nSize);

    public:
        /// @brief Get a constant pointer to the start of the buffer.
        /// @return A const char pointer to the buffer.
        const char *buffer() const override { return this->m_pBuffer; }

        /// @brief Get a mutable pointer to the start of the buffer.
        /// @return A char pointer to the buffer.
        char *rawBuffer() const override { return this->m_pBuffer; }

        /// @brief Get the size of the buffer.
        /// @return The size of the buffer.
        [[nodiscard]] size_t size() const override { return this->m_nSize; }

        /// @brief Get the total allocated size of the buffer.
        /// @return The total allocated size of the buffer.
        [[nodiscard]] size_t allocatedSize() const { return this->m_nAllocatedSize; }

    public:
        /// @brief Array access operator.
        /// @param i_nIndex The index of the byte to retrieve.
        /// @exception IndexOutOfRangeException If the provided index is greater than the size of the buffer, this function will throw an IndexOutOfRangeException.
        /// @return The byte at the specified index.
        const char &operator[](const size_t i_nIndex) {
            if (this->checkBuffer(); i_nIndex > this->m_nSize) {
                throw IndexOutOfRangeException;
            }
            return this->m_pBuffer[i_nIndex];
        }

        /// @brief Copy assignment operator.
        /// @param i_oOther The object to copy from.
        /// @details This function will copy the state of another CDynamicBuffer, allocating memory as necessary.
        void operator=(const CDynamicBuffer &i_oOther) {
            this->m_nAllocatedSize = i_oOther.m_nAllocatedSize;
            this->m_pBuffer = new char[this->m_nAllocatedSize];
            this->m_nSize = i_oOther.m_nSize;
            memcpy(this->m_pBuffer, i_oOther.m_pBuffer, this->m_nSize);
        }

        /// @brief Move assignment operator.
        /// @param i_oOther The object to move from.
        /// @details This function will take over the state of another CDynamicBuffer, leaving the other object in a safe, but undefined state.
        void operator=(CDynamicBuffer &&i_oOther) noexcept {
            this->m_pBuffer = i_oOther.m_pBuffer;
            this->m_nSize = i_oOther.m_nSize;
            this->m_nAllocatedSize = i_oOther.m_nAllocatedSize;
            i_oOther.m_pBuffer = nullptr;
            i_oOther.m_nSize = 0;
            i_oOther.m_nAllocatedSize = 0;
        }

    private:
        /// @var char* Devel::IO::CDynamicBuffer::m_pBuffer
        /// @brief The raw buffer.
        char *m_pBuffer;

        /// @var size_t Devel::IO::CDynamicBuffer::m_nSize
        /// @brief The size of the buffer.
        size_t m_nSize;

        /// @var size_t Devel::IO::CDynamicBuffer::m_nAllocatedSize
        /// @brief The total allocated size of the buffer.
        size_t m_nAllocatedSize;
    };
}