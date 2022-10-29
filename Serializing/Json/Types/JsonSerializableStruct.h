#pragma once

#include "Core/Global.h"
#include "Serializing/Json/JsonSerializableType.h"
#include "Serializing/Json/JsonSerializer.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    template<typename TStruct>
    class IJsonStruct : public IJsonType<TStruct, IData<TStruct>> {
    public:
        IJsonStruct(const CJsonFieldName i_oFieldName) : IJsonType<TStruct, IData<TStruct>>(i_oFieldName) {}

    private:
        bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict ) final {
            IO::CJsonObject *pObject = this->getObject(i_oObject, i_bIsStrict);

            if (!pObject) {
                return true;
            }
            if (pObject->type() != IO::EJsonType::JTObject) {
                throw DifferentTypesException;
            }

            return DeserializeObject(this->m_tValue, *pObject);
        }

        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict ) const final {
            if (this->checkSerializeObject(i_oObject, i_bIsStrict)) {
                return true;
            }

            return SerializeObject(this->m_tValue, i_oObject.get(this->name()), i_bIsStrict);
        }

        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }
    public:
        using IJsonType<TStruct, IData<TStruct>>::IJsonType;

        IJsonStruct &operator=(const TStruct &i_tValue) {
            this->m_tValue = i_tValue;
            this->setNull(false);
            return *this;
        }

        IJsonStruct &operator=(TStruct &&i_tValue) {
            this->m_tValue = std::move(i_tValue);
            this->setNull(false);
            return *this;
        }
    };

#pragma pack(pop)
}