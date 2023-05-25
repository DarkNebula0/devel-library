#pragma once

#include "Serializing/Json/JsonSerializableType.h"
#include "Serializing/Json/JsonSerializer.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {

#pragma pack(push, 1)

    /// @class Devel::Serializing::IJsonArray
    /// @brief Represents a JSON array of a specific type.
    /// @tparam TStruct The type of the elements in the JSON array.
    template<typename TStruct>
    class IJsonArray : public IJsonType<TStruct, IData<std::vector<TStruct>>> {
    public:
        /// @brief Constructs an instance of the JSON array with the given field name.
        /// @param i_oFieldName The field name of the JSON array.
        IJsonArray(const CJsonFieldName i_oFieldName) : IJsonType<TStruct, IData<std::vector<TStruct>>>(
                i_oFieldName) {};
    private:
        /// @brief Handles the deserialization of the JSON array.
        /// @param i_oObject The JSON object to deserialize.
        /// @param i_bIsStrict Determines if strict deserialization should be used.
        /// @return True if deserialization is successful, false otherwise.
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
                } else {
                    if constexpr (is_data_class<TStruct>::value) {
                        if (!grStruct.doDeserialize(oItem.c_str())) {
                            return false;
                        }
                    } else if constexpr (std::is_same_v<IO::CJsonObject, TStruct>) {
                        grStruct = oItem;
                    } else {
                        throw InvalidTypeException;
                    }
                }

                this->m_tValue.push_back(std::move(grStruct));
            }

            return true;
        }

        /// @brief Handles the serialization of the JSON array.
        /// @param i_oObject The JSON object to serialize into.
        /// @param i_bIsStrict Determines if strict serialization should be used.
        /// @return True if serialization is successful, false otherwise.
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
                } else if constexpr (is_json_type_class<TStruct>::value) {
                    return grItem.onSerialize(oObject);
                } else if constexpr (is_data_class<TStruct>::value) {

                    oObject = grItem.value();
                } else {
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

        /// @brief Handles the deserialization of the JSON array.
        /// @param i_oObject The JSON object to deserialize.
        /// @return True if deserialization is successful, false otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        /// @brief Handles the serialization of the JSON array.
        /// @param i_oObject The JSON object to serialize into.
        /// @return True if serialization is successful, false otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<TStruct, IData<std::vector<TStruct>>>::IJsonType;

        /// @brief Assigns another instance of IJsonArray to this instance.
        /// @param i_tValue The other instance of IJsonArray to assign.
        /// @return Reference to this instance after assignment.
        auto &operator=(const IJsonArray<TStruct> &i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }

        /// @brief Moves another instance of IJsonArray to this instance.
        /// @param i_tValue The other instance of IJsonArray to move.
        /// @return Reference to this instance after move.
        auto &operator=(IJsonArray<TStruct> &&i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }
    };

#pragma pack(pop)
}