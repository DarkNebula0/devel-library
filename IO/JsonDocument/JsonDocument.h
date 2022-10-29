#pragma once
#include "Core/Global.h"
#include "Core/Exceptions.h"
#include "IO/JsonObject/JsonObject.h"
#include "IO/Buffer/Buffer.h"

namespace Devel::IO {
    static auto InvalidFormatException = std::runtime_error("Object format is invalid!");
    static auto InvalidEncodingException = std::runtime_error("Object encoding is invalid!");

    class CJsonDocument
    {
    public:
        CJsonDocument();
        CJsonDocument(const std::string &i_stJson);
        CJsonDocument(const CJsonDocument &i_oOther) : CJsonDocument() { this->operator=(i_oOther); }
        CJsonDocument(CJsonDocument &&i_oOther) noexcept : CJsonDocument() { this->operator=(std::move(i_oOther)); }
        virtual ~CJsonDocument();
    private:
        CJsonObject m_oObject;
    private:
        char *m_pBuffer;
        char *m_pPointer;
        char *m_pEnd;
    private:
        void removeWhitespace();
        void selectParser(std::string &i_stOutBuffer, CJsonObject *i_pObject = nullptr);
    private:
        uint parseUnicodeHex();
    private:
        void parseNull(std::string &i_stOutBuffer, CJsonObject *i_pObject);
        void parseBool(std::string &i_stOutBuffer, CJsonObject *i_pObject);
        void parseObject(std::string &i_stOutBuffer, CJsonObject *i_pObject);
        void parseString(std::string &i_stOutBuffer, CJsonObject *i_pObject = nullptr);
        void parseNumber(std::string &i_stOutBuffer, CJsonObject *i_pObject);
        void parseArray(CJsonObject *i_pObject);
    private:
        static void selectSerializer(std::string &i_stBuffer, CJsonObject &i_oObject, bool i_bFormatted = false);
        static void serializeArray(std::string &i_stBuffer, CJsonObject &i_oObject, bool i_bFormatted = false);
        static void serializeObject(std::string &i_stBuffer, CJsonObject &i_oObject, bool i_bFormatted = false);
        static void serializeNumber(std::string &i_stBuffer, CJsonObject &i_oObject);
        static void serializeString(std::string &i_stBuffer, CJsonObject &i_oObject);
        static void serializeNull(std::string &i_stBuffer);
        static void serializeBool(std::string &i_stBuffer, CJsonObject &i_oObject);
    private:
        inline void setBuffer(char *i_pBuffer, const size_t i_nSize)
        {
            this->clearBuffer();
            this->m_pBuffer = i_pBuffer;
            this->m_pPointer = i_pBuffer;
            this->m_pEnd = i_pBuffer + i_nSize;
        }
        inline void clearBuffer()
        {
            delete[] m_pBuffer;
            this->m_pBuffer = nullptr;
            this->m_pPointer = nullptr;
            this->m_pEnd = nullptr;
        }
        inline void skipChar()
        {
            this->m_pPointer++;
        }
    private:
        inline size_t getBufferSize() const { return this->m_pEnd - this->m_pBuffer; }
        inline bool checkChar(const char i_chExpect)
        {
            if (*this->m_pPointer == i_chExpect)
            {
                this->m_pPointer++;
                return true;
            }
            return false;
        }
    public:
        void parse(const std::string &i_stJson);
        std::string serialize(bool i_bFormatted);
    public:
        void clear()
        {
            this->m_oObject.clear();
        }
    public:
        inline CJsonObject &getObject(const std::string &i_stKey) { return this->operator[](i_stKey); }
        inline CJsonObject &toObject() { return this->m_oObject; }
    public:
        inline CJsonObject &operator[](const std::string &i_stKey)
        {
            return this->m_oObject.operator[](i_stKey);
        }
        inline CJsonDocument &operator=(const CJsonDocument &i_oOther)
        {
            this->m_oObject = i_oOther.m_oObject;
            return *this;
        }
        inline CJsonDocument &operator=(CJsonDocument &&i_oOther) noexcept
        {
            this->m_oObject = std::move(i_oOther.m_oObject);
            return *this;
        }
    };
}