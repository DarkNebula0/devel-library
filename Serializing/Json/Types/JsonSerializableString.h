#pragma once

#include "Serializing/Json/JsonSerializableType.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IJsonString
    /// @brief Represents a JSON string data type and provides serialization and deserialization functionality.
    class IJsonString : public IJsonType<std::string, IData<std::string>> {
    public:
        /// @brief Constructs an `IJsonString` object with the specified field name.
        /// @param i_oFieldName The field name for the JSON string.
        IJsonString(const CJsonFieldName i_oFieldName) : IJsonType<std::string, IData<std::string>>(i_oFieldName) {}

    private:
        /// @brief Performs deserialization of the `IJsonString` object from a JSON object, with strictness control.
        /// @param i_oObject The JSON object to deserialize from.
        /// @param i_bIsStrict Specifies whether to perform strict deserialization.
        /// @return `true` if deserialization is successful, `false` otherwise.
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

        /// @brief Performs serialization of the `IJsonString` object to a JSON object, with strictness control.
        /// @param i_oObject The JSON object to serialize to.
        /// @param i_bIsStrict Specifies whether to perform strict serialization.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const override {
            return this->serialize(i_oObject, i_bIsStrict);
        }

        /// @brief Performs deserialization of the `IJsonString` object from a JSON object.
        /// @param i_oObject The JSON object to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        /// @brief Performs serialization of the `IJsonString` object to a JSON object.
        /// @param i_oObject The JSON object to serialize to.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject) const final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<std::string, IData<std::string>>::IJsonType;

        /// @brief Assigns a value to the `IJsonString` object.
        /// @tparam String The type of the value to assign.
        /// @param i_tValue The value to assign.
        /// @return A reference to the `IJsonString` object.
        template<typename String,
                std::enable_if_t<std::is_constructible_v<std::string, String>, bool> = true
        >
        IJsonString &operator=(const String &i_tValue) {
            this->setNull(false);
            this->m_tValue = i_tValue;
            return *this;
        }

        /// @brief Assigns an rvalue to the `IJsonString` object.
        /// @tparam String The type of the rvalue to assign.
        /// @param i_tValue The rvalue to assign.
        /// @return A reference to the `IJsonString` object.
        template<typename String,
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