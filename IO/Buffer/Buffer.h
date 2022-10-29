#pragma once

#include <Core/Exceptions.h>
#include <Core/Typedef.h>
#include <cstring>

namespace Devel::IO {
    static auto NoBufferException = std::logic_error("Buffer is nullptr!");
    static auto IndexOutOfRangeException = std::range_error("Index out of range!");

    class IBuffer {
    public:
        virtual const char *buffer() const = 0;

        virtual char *rawBuffer() const = 0;

        virtual size_t size() const = 0;
    };
} // namespace Devel::IO