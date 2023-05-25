#pragma once

#include "IO/JsonDocument/JsonDocument.h"
#include "IO/JsonObject/JsonObject.h"
#include "IO/JsonArray/JsonArray.h"
#include "Serializing/Json/JsonSerializableType.h"

namespace Devel::Serializing {
    /// @brief Deserializes a JSON object into a struct.
    /// @tparam T The type of the struct.
    /// @param i_oStruct The struct to deserialize into.
    /// @param i_oObject The JSON object to deserialize.
    /// @param i_bIsStrict Determines if strict deserialization should be used.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return True if deserialization is successful, false otherwise.
    template<typename T>
    bool DeserializeObject(T &i_oStruct, IO::CJsonObject &i_oObject, const bool i_bIsStrict = false,
                           size_t i_nStructSize = sizeof(T)) {
        if (i_oObject.type() == IO::EJsonType::JTObject || i_oObject.type() == IO::EJsonType::JTArray) {
            return IterateDeserializableStruct<IJsonType<>>(&i_oStruct, [&](IJsonType<> *i_pData) {
                return i_pData->doDeserialize(i_oObject, i_bIsStrict);
            }, i_nStructSize);
        }

        throw DifferentTypesException;
    }

    /// @brief Deserializes a JSON document into a struct.
    /// @tparam T The type of the struct.
    /// @param i_oStruct The struct to deserialize into.
    /// @param i_oDocument The JSON document to deserialize.
    /// @param i_bIsStrict Determines if strict deserialization should be used.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return True if deserialization is successful, false otherwise.
    template<typename T>
    bool DeserializeDocument(T &i_oStruct, IO::CJsonDocument &i_oDocument, const bool i_bIsStrict = false,
                             size_t i_nStructSize = sizeof(T)) {
        return IterateDeserializableStruct<IJsonType<>>(&i_oStruct, [&](IJsonType<> *i_pData) {
            return i_pData->doDeserialize(i_oDocument.toObject(), i_bIsStrict);
        }, i_nStructSize);
    }

    /// @brief Serializes a struct into a JSON object.
    /// @tparam T The type of the struct.
    /// @param i_oStruct The struct to serialize.
    /// @param i_oObject The JSON object to serialize into.
    /// @param i_bIsStrict Determines if strict serialization should be used.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return True if serialization is successful, false otherwise.
    template<typename T>
    bool SerializeObject(const T &i_oStruct, IO::CJsonObject &i_oObject, const bool i_bIsStrict = false,
                         size_t i_nStructSize = sizeof(T)) {
        return IterateSerializableStruct<IJsonType<>>(&i_oStruct, [&](const IJsonType<> *i_pData) {
            return i_pData->doSerialize(i_oObject, i_bIsStrict);
        }, i_nStructSize);
    }

    /// @brief Serializes a struct into a JSON document.
    /// @tparam T The type of the struct.
    /// @param i_oStruct The struct to serialize.
    /// @param i_oDocument The JSON document to serialize into.
    /// @param i_bIsStrict Determines if strict serialization should be used.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return True if serialization is successful, false otherwise.
    template<typename T>
    bool SerializeDocument(const T &i_oStruct, IO::CJsonDocument &i_oDocument, const bool i_bIsStrict = false,
                           size_t i_nStructSize = sizeof(T)) {
        i_oDocument.clear();
        return SerializeObject(i_oStruct, i_oDocument.toObject(), i_bIsStrict, i_nStructSize);
    }
}