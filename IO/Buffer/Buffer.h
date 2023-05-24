#pragma once

#include <Core/Exceptions.h>
#include <Core/Typedef.h>
#include <cstring>

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    /// @var std::logic_error Devel::IO::NoBufferException
    /// @brief Exception thrown when the buffer is nullptr.
    static auto NoBufferException = std::logic_error("Buffer is nullptr!");

    /// @var std::range_error Devel::IO::IndexOutOfRangeException
    /// @brief Exception thrown when an index is out of range.
    static auto IndexOutOfRangeException = std::range_error("Index out of range!");

    /// @class Devel::IO::IBuffer
    /// @brief An interface for working with byte buffers.
    ///
    /// This class represents an interface for a buffer of bytes, providing
    /// a consistent way to interact with various types of byte buffers.
    ///
    /// <b>Example</b>
    ///
    /// Here's an example of how you might use an IBuffer:
    ///
    /// @code{.cpp}
    ///    class CExampleBuffer : public IBuffer {
    ///        char data[128];
    ///
    ///        const char *buffer() const override {
    ///            return data;
    ///        }
    ///
    ///        char *rawBuffer() const override {
    ///            return data;
    ///        }
    ///
    ///        size_t size() const override {
    ///            return sizeof(data);
    ///        }
    ///    };
    ///
    ///    CExampleBuffer myBuffer;
    ///    const char *buffer = myBuffer.buffer();
    ///    size_t bufferSize = myBuffer.size();
    /// @endcode
    class IBuffer {
    public:
        /// @brief Get a constant pointer to the start of the buffer.
        ///
        /// @return A const char pointer to the buffer.
        virtual const char *buffer() const = 0;

        /// @brief Get a mutable pointer to the start of the buffer.
        ///
        /// @return A char pointer to the buffer.
        virtual char *rawBuffer() const = 0;

        /// @brief Get the size of the buffer.
        ///
        /// @return The size of the buffer.
        virtual size_t size() const = 0;
    };
}