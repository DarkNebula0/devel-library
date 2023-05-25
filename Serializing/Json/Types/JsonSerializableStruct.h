#pragma once

#include "Core/Global.h"
#include "Serializing/Json/JsonSerializableType.h"
#include "Serializing/Json/JsonSerializer.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IJsonStruct
    /// @brief Represents a JSON structure data type and provides serialization and deserialization functionality.
    /// @tparam TStruct The type of the structure to represent as a JSON structure.
    template<typename TStruct>
    class IJsonStruct : public IJsonType<TStruct, IData<TStruct>> {
    public:
        /// @brief Constructs an `IJsonStruct` object with the specified field name.
        /// @param i_oFieldName The field name for the JSON structure.
        IJsonStruct(const CJsonFieldName i_oFieldName) : IJsonType<TStruct, IData<TStruct>>(i_oFieldName) {}

    private:
        /// @brief Performs deserialization of the `IJsonStruct` object from a JSON object, with strictness control.
        /// @param i_oObject The JSON object to deserialize from.
        /// @param i_bIsStrict Specifies whether to perform strict deserialization.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) final {
            IO::CJsonObject *pObject = this->getObject(i_oObject, i_bIsStrict);

            if (!pObject) {
                return true;
            }
            if (pObject->type() != IO::EJsonType::JTObject) {
                throw DifferentTypesException;
            }

            return DeserializeObject(this->m_tValue, *pObject);
        }

        /// @brief Performs serialization of the `IJsonStruct` object to a JSON object, with strictness control.
        /// @param i_oObject The JSON object to serialize to.
        /// @param i_bIsStrict Specifies whether to perform strict serialization.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const final {
            if (this->checkSerializeObject(i_oObject, i_bIsStrict)) {
                return true;
            }

            return SerializeObject(this->m_tValue, i_oObject.get(this->name()), i_bIsStrict);
        }

        /// @brief Performs deserialization of the `IJsonStruct` object from a JSON object.
        /// @param i_oObject The JSON object to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        /// @brief Performs serialization of the `IJsonStruct` object to a JSON object.
        /// @param i_oObject The JSON object to serialize to.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<TStruct, IData<TStruct>>::IJsonType;

        /// @brief Assigns a value to the `IJsonStruct` object.
        /// @param i_tValue The value to assign.
        /// @return A reference to the `IJsonStruct` object
        IJsonStruct &operator=(const TStruct &i_tValue) {
            this->m_tValue = i_tValue;
            this->setNull(false);
            return *this;
        }

        /// @brief Assigns an rvalue to the `IJsonStruct` object.
        /// @param i_tValue The rvalue to assign.
        /// @return A reference to the `IJsonStruct` object.
        IJsonStruct &operator=(TStruct &&i_tValue) {
            this->m_tValue = std::move(i_tValue);
            this->setNull(false);
            return *this;
        }
    };

#pragma pack(pop)
}