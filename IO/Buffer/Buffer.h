#pragma once

#include <Core/Exceptions.h>
#include <Core/Typedef.h>
#include <cstring>

namespace Devel::IO
{
    CreateFastException(CNoBufferException, "Buffer is nullptr!");

    class IBuffer
    {
    public:
        virtual const char *buffer() const = 0;
        virtual char *rawBuffer() const = 0;
        virtual size_t size() const = 0;
    };
} // namespace Devel::IO