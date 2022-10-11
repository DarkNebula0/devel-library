#pragma once
#include "IO/Buffer/Buffer.h"

namespace Devel::IO
{
    class CDynamicBuffer : public IBuffer
    {
    public:
        CDynamicBuffer();
        CDynamicBuffer(const size_t i_nSize);
        CDynamicBuffer(const CDynamicBuffer &i_oOther){
            this->operator=(i_oOther);
        }
        CDynamicBuffer(CDynamicBuffer &&i_oOther) noexcept {
            this->operator=(std::move(i_oOther));
        }
        virtual ~CDynamicBuffer();
    private:
        void deleteBuffer();
    private:
        void checkBuffer(){
            if(!this->m_pBuffer)
            {
                throw CNoBufferException();
            }
        }
    public:
        void reallocate(const size_t i_nSize);
    public:
        const char *buffer() const { return this->m_pBuffer; }
        char *rawBuffer() const {return this->m_pBuffer;}
        size_t size() const { return this->m_nSize; }
        size_t allocatedSize() const { return this->m_nAllocatedSize; }
    public:
        const char &operator[](const size_t i_nIndex){
            if (this->checkBuffer(); i_nIndex > this->m_nSize)
            {
                throw CIndexOutOfRangeException();
            }
            return this->m_pBuffer[i_nIndex];
        }

        void operator=(const CDynamicBuffer &i_oOther)
        {
            this->m_nAllocatedSize = i_oOther.m_nAllocatedSize;
            this->m_pBuffer = new char[this->m_nAllocatedSize];
            this->m_nSize = i_oOther.m_nSize;
            memcpy(this->m_pBuffer, i_oOther.m_pBuffer, this->m_nSize);
        }

        void operator=(CDynamicBuffer &&i_oOther) noexcept
        {
            this->m_pBuffer = i_oOther.m_pBuffer;
            this->m_nSize = i_oOther.m_nSize;
            this->m_nAllocatedSize = i_oOther.m_nAllocatedSize;
            i_oOther.m_pBuffer = nullptr;
            i_oOther.m_nSize = 0;
            i_oOther.m_nAllocatedSize = 0;
        }
    private:
        char *m_pBuffer;
        size_t m_nSize;
        size_t m_nAllocatedSize;
    };
}