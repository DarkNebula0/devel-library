#pragma once

#include "Serializing/Core/Types/SerializableBool.h"
#include "Serializing/Json/JsonSerializableType.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    class IJsonBool : public IJsonType<bool, Serializing::IBool<>> {
    public:
        IJsonBool(const CJsonFieldName i_oFieldName) : IJsonType<bool, Serializing::IBool<>>(i_oFieldName) {}

    private:
        bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) final {
            IO::CJsonObject *pObject = this->getObject(i_oObject, i_bIsStrict);

            if (!pObject) {
                return true;
            } else if (pObject->type() != IO::EJsonType::JTBoolean) {
                throw DifferentTypesException;
            }

            this->operator=(!(pObject->empty() ||
                              pObject->at(0) < '1' ||
                              pObject->at(0) == 'f' ||
                              pObject->at(0) == 'F')
            );

            return true;
        }

        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const final {
            return this->serialize(i_oObject, i_bIsStrict);
        }

        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<bool, Serializing::IBool<>>::IJsonType;

        IJsonBool &operator=(const bool &i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }

        IJsonBool &operator=(bool &&i_tValue) {
            this->setNull(false);
            this->m_tValue = std::move(i_tValue);
            return *this;
        }
    };

#pragma pack(pop)
}