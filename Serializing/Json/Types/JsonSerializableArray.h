#pragma once
#include "Serializing/Json/JsonSerializableType.h"
#include "Serializing/Json/JsonSerializer.h"

namespace Devel::Serializing {

#pragma pack(push, 1)
    template<typename TStruct>
    class IJsonArray : public IJsonType<TStruct, IData<std::vector<TStruct>>> {
    public:
        IJsonArray(const CJsonFieldName i_oFieldName) : IJsonType<TStruct, IData<std::vector<TStruct>>>(
                i_oFieldName) {};
    private:
        bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) final {
            IO::CJsonObject *pObject = this->getObject(i_oObject, i_bIsStrict);
            if (!pObject) {
                return true;
            } else if (pObject->type() != IO::EJsonType::JTArray) {
                throw DifferentTypesException;
            }

            this->setNull(false);
            IO::CJsonArray oArray = pObject->toArray();
            for (const IO::CJsonObject &oItem: oArray) {
                TStruct grStruct;

                if (oItem.type() == IO::EJsonType::JTObject || oItem.type() == IO::EJsonType::JTArray) {
                    if (!DeserializeObject(grStruct, const_cast<IO::CJsonObject &>(oItem))) {
                        return false;
                    }
                }
                else {
                   if constexpr (is_data_class<TStruct>::value) {
                       if (!grStruct.doDeserialize(oItem.c_str())) {
                           return false;
                       }
                    }
                    else if constexpr (std::is_same_v<IO::CJsonObject, TStruct>) {
                        grStruct= oItem;
                   }
                   else {
                       throw InvalidTypeException;
                    }
                }

                this->m_tValue.push_back(std::move(grStruct));
            }

            return true;
        }

        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) const final {
            if (this->checkSerializeObject(i_oObject, i_bIsStrict)) {
                return true;
            }

            IO::CJsonArray oArray;
            for (const TStruct &grItem: this->m_tValue) {
                IO::CJsonObject oObject;

                if constexpr (std::is_base_of_v<IStruct, TStruct>) {
                    if (!SerializeObject(grItem, oObject)) {
                        return false;
                    }
                }
                else if constexpr (is_json_type_class<TStruct>::value) {
                    return grItem.onSerialize(oObject);
                }
                else if constexpr (is_data_class<TStruct>::value) {
                
                    oObject = grItem.value();
                }
                else {
                    throw InvalidTypeException;
                }

                oArray.push_back(oObject);
            }

            if (this->name().empty()) {
                i_oObject = oArray;
            } else {
                i_oObject.get(this->name()) = oArray;
            }
            return true;
        }

        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<TStruct, IData<std::vector<TStruct>>>::IJsonType;

        auto &operator=(const IJsonArray<TStruct> &i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }

        auto &operator=(IJsonArray<TStruct> &&i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }
    };

#pragma pack(pop)
}