#pragma once

#include "Core/Global.h"
#include "Core/Utils/StringUtils.h"
#include "Core/Typedef.h"
#include "Threading/LockGuard/LockGuard.h"

#include <string_view>
#include <string>
#include <map>

namespace Devel::IO {
    enum class EJsonType {
        JTObject,
        JTNumber,
        JTBoolean,
        JTString,
        JTArray,
        JTNull,
    };

    class CJsonArray;
    class CJsonObject : public std::string {
        friend class CJsonDocument;

    public:
        CJsonObject();

        CJsonObject(const CJsonObject &i_oOther) : CJsonObject() {
            this->operator=(i_oOther);
        }

        CJsonObject(CJsonObject &&i_oOther) noexcept: CJsonObject() {
            this->operator=(std::move((i_oOther)));
        }

        virtual ~CJsonObject();

    private:
        EJsonType m_eType;
    private:
        Threading::CMutex m_oMutex;
        CJsonArray *m_pArray;
    private:
        std::map<std::string, CJsonObject> m_aoData;
    private:
        void addObject(const std::string &i_stName, CJsonObject &&i_oObject);

        void setType(const EJsonType i_eType) { this->m_eType = i_eType; }

        void clear();

    public:
        CJsonObject *find(std::string_view i_stName);

        std::vector<std::string> getKeys();

        CJsonArray toArray() const;

    public:
        inline Threading::CMutex
        &

        mutex() {
            return this->m_oMutex;
        }

        inline EJsonType

        type() const { return this->m_eType; }

        inline CJsonObject
        &

        get(const std::string_view i_stName) { return this->operator[](i_stName); }

    public:
        inline void setNull() { this->m_eType = EJsonType::JTNull; }

    public:
        inline uint64

        toUInt64() const { return StringUtils::ToUInt64(*this); }

        inline int64

        toInt64() const { return StringUtils::ToInt64(*this); }

        inline int toInt() const { return StringUtils::ToInt(*this); }

        inline uint

        toUInt() const { return StringUtils::ToInt(*this); }

        inline float toFloat() const { return StringUtils::ToFloat(*this); }

        inline double toDouble() const { return StringUtils::ToDouble(*this); }

        inline bool toBool() const { return ( *this == "t" || *this == "1"); }
        inline bool isNull() const { return this->m_eType == EJsonType::JTNull; }

    public:
        CJsonObject &operator=(const CJsonObject &i_oOther);

        CJsonObject &operator=(CJsonObject &&i_oOther) noexcept;

        CJsonObject &operator=(const CJsonArray &i_oOther);

    public:
        inline CJsonObject
        &

        operator=(const char *i_stValue) {
            return this->operator=(std::string(i_stValue));
        }

        inline CJsonObject
        &

        operator=(const std::string &i_stValue) {
            this->m_eType = EJsonType::JTString;
            std::string::operator=(i_stValue);
            return *this;
        }

        inline CJsonObject
        &

        operator=(const uint64 i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject
        &

        operator=(const uint i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject
        &

        operator=(const int64 i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject
        &

        operator=(const float i_fValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_fValue));
            return *this;
        }

        inline CJsonObject
        &

        operator=(const double i_dValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_dValue));
            return *this;
        }

        inline CJsonObject
        &

        operator=(const int i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject
        &

        operator=(const bool i_bState) {
            this->operator=((i_bState ? "t" : "f"));
            this->m_eType = EJsonType::JTBoolean;
            return *this;
        }

        inline CJsonObject
        &

        operator[](const std::string_view i_stKey) {
            Threading::RecursiveLockGuard(this->m_oMutex);
            return this->m_aoData.operator[](std::string(i_stKey));
        }
    };
}