#pragma once

#include "Serializing/Core/Types/SerializableBool.h"
#include "Serializing/Json/JsonSerializableType.h"
/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IJsonBool
    /// @brief Represents a JSON boolean data type for serialization and deserialization.
    ///
    /// The `IJsonBool` class is a specialization of `IJsonType` for handling boolean values in JSON objects.
    /// It provides functionality for deserializing a JSON boolean value into a boolean variable,
    /// as well as serializing a boolean variable into a JSON boolean value.
    class IJsonBool : public IJsonType<bool, Serializing::IBool<>> {
    public:
        /// @brief Constructs an `IJsonBool` object with the specified JSON field name.
        /// @param i_oFieldName The JSON field name.
        IJsonBool(const CJsonFieldName i_oFieldName) : IJsonType<bool, Serializing::IBool<>>(i_oFieldName) {}

    private:
        /// @brief Performs deserialization of the `IJsonBool` object from a JSON object, with strictness control.
        /// @param i_oObject The JSON object to deserialize from.
        /// @param i_bIsStrict Specifies whether to perform strict deserialization.
        /// @return `true` if deserialization is successful, `false` otherwise.
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

        /// @brief Performs serialization of the `IJsonBool` object to a JSON object, with strictness control.
        /// @param i_oObject The JSON object to serialize to.
        /// @param i_bIsStrict Specifies whether to perform strict serialization.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const final {
            return this->serialize(i_oObject, i_bIsStrict);
        }

        /// @brief Performs deserialization of the `IJsonBool` object from a JSON object.
        /// @param i_oObject The JSON object to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        /// @brief Performs serialization of the `IJsonBool` object to a JSON object.
        /// @param i_oObject The JSON object to serialize to.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<bool, Serializing::IBool<>>::IJsonType;

        /// @brief Assignment operator for assigning a boolean value to the `IJsonBool` object.
        /// @param i_tValue The boolean value to assign.
        /// @return A reference to the modified `IJsonBool` object.
        IJsonBool &operator=(const bool &i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }

        /// @brief Move assignment operator for assigning a boolean value to the `IJsonBool` object.
        /// @param i_tValue The boolean value to assign.
        /// @return A reference to the modified `IJsonBool` object.
        IJsonBool &operator=(bool &&i_tValue) {
            this->setNull(false);
            this->m_tValue = std::move(i_tValue);
            return *this;
        }
    };

#pragma pack(pop)
}