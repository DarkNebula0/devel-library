#include "DynamicBuffer.h"

Devel::IO::CDynamicBuffer::CDynamicBuffer()
        : m_pBuffer(nullptr), m_nSize(0), m_nAllocatedSize(0)
{
}

Devel::IO::CDynamicBuffer::CDynamicBuffer(const size_t i_nSize)
        : CDynamicBuffer()
{
    this->reallocate(i_nSize);
}

Devel::IO::CDynamicBuffer::~CDynamicBuffer()
{
    this->deleteBuffer();
}

void Devel::IO::CDynamicBuffer::deleteBuffer()
{
    delete[] this->m_pBuffer;

    this->m_pBuffer = nullptr;
    this->m_nSize = 0;
    this->m_nAllocatedSize = 0;
}

void Devel::IO::CDynamicBuffer::reallocate(const size_t i_nSize)
{
    if (i_nSize >= this->m_nAllocatedSize)
    {
        const size_t nReserveSize = i_nSize / 3;

        const char *pOldBuffer = this->m_pBuffer;
        this->m_nAllocatedSize = i_nSize + (nReserveSize > 500 ? 500 : nReserveSize);
        this->m_pBuffer = new char[this->m_nAllocatedSize];

        if (pOldBuffer)
        {
            memcpy(this->m_pBuffer, pOldBuffer, this->m_nSize);
            delete[] pOldBuffer;
        }
    }
}