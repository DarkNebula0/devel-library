#pragma once

#include "Serializing/Json/JsonSerializableType.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    class IJsonString : public IJsonType<std::string, IData<std::string>> {
    public:
        IJsonString(const CJsonFieldName i_oFieldName) : IJsonType<std::string, IData<std::string>>(i_oFieldName) {}

    private:
        bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) override {
            IO::CJsonObject *pObject = this->getObject(i_oObject, i_bIsStrict);

            if (!pObject) {
                return true;
            } else if (pObject->type() != IO::EJsonType::JTString) {
                throw DifferentTypesException;
            }

            this->operator=(*pObject);
            return true;
        }

        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const override {
            return this->serialize(i_oObject, i_bIsStrict);
        }

        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<std::string, IData<std::string>>::IJsonType;

        template <typename String,
                std::enable_if_t<std::is_constructible_v<std::string, String>, bool> = true
        >
        IJsonString &operator=(const String &i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }

        template <typename String,
                std::enable_if_t<std::is_constructible_v<std::string, String>, bool> = true
        >
        IJsonString &operator=(String &&i_tValue) {
            this->setNull(false);
            this->m_tValue = std::move(i_tValue);
            return *this;
        };
    };

#pragma pack(pop)
}