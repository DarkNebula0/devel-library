#pragma once

#include "Core/Global.h"
#include "Core/Exceptions.h"
#include "Serializing/Json/JsonFieldName.h"
#include "Serializing/SerializingDefines.h"
#include "Serializing/Core/SerializableData.h"
#include "IO/JsonObject/JsonObject.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
    /// @brief Error thrown when the object has an invalid or empty name.
    static auto InvalidObjectName = std::runtime_error("Object invalid or empty name!");
    /// @brief Error thrown when the object does not match the struct.
    static auto InvalidData = std::runtime_error("Object does not matches the struct!");
    /// @brief Error thrown when different types are encountered.
    static auto DifferentTypesException = std::runtime_error("Different types!");
    /// @brief Error thrown when an invalid type is encountered.
    static auto InvalidTypeException = std::runtime_error("Invalid type!");

#pragma pack(push, 1)

    /// @class Devel::Serializing::IJsonType
    /// @brief Represents a JSON data type with serialization and deserialization functionality.
    /// @tparam T The underlying data type of the JSON field.
    /// @tparam TData The base class for serialization and deserialization operations.
    /// <b>Example</b>
    ///
    /// This class represents a JSON data type and provides serialization and deserialization functionality.
    ///
    /// Here is an example of how to use the IJsonType class:
    ///
    /// @code{.cpp}
    ///     #include "IJsonType.h"
    ///     #include "IO/JsonObject/JsonObject.h"
    ///
    ///     using namespace Devel::Serializing;
    ///     using namespace Devel::IO;
    ///
    ///     // Define a custom JSON data type
    ///     class MyJsonType : public IJsonType<int> {
    ///     public:
    ///         MyJsonType(const CJsonFieldName fieldName) : IJsonType<int>(fieldName) {}
    ///
    ///     protected:
    ///         bool onDeserialize(CJsonObject& object) override {
    ///             if (object.contains(this->name()) && object.get(this->name()).isInteger()) {
    ///                 this->m_tValue = object.get(this->name()).toInt();
    ///                 return true;
    ///             }
    ///             return false;
    ///         }
    ///
    ///         bool onSerialize(CJsonObject& object) const override {
    ///             object.get(this->name()) = this->m_tValue;
    ///             return true;
    ///         }
    ///     };
    ///
    ///     int main() {
    ///         // Create a JSON object
    ///         CJsonObject jsonObject;
    ///
    ///         // Create an instance of MyJsonType
    ///         MyJsonType myJsonType("myField");
    ///
    ///         // Serialize the MyJsonType object to the JSON object
    ///         myJsonType.doSerialize(jsonObject);
    ///
    ///         // Deserialize the JSON object into the MyJsonType object
    ///         myJsonType.doDeserialize(jsonObject);
    ///
    ///         return 0;
    ///     }
    /// @endcode
    ///
    /// This example demonstrates the creation of a custom JSON data type called `MyJsonType`, which derives from `IJsonType`.
    /// It overrides the `onDeserialize` and `onSerialize` functions to provide custom deserialization and serialization logic.
    /// The `MyJsonType` object is then serialized to a JSON object and deserialized back from the JSON object.
    /// Note that the example uses the `CJsonObject` class from the `IO` namespace for JSON object manipulation.
    ///
    template<typename T = int, typename TData = IData<T>>
    class IJsonType : public TData {
    protected:
        /// @brief Constructs an `IJsonType` object with the specified JSON field name.
        /// @param i_oFieldName The name of the JSON field.
        explicit IJsonType(const CJsonFieldName i_oFieldName) : m_oFieldName(i_oFieldName), m_bIsNull(false) {}

        /// @brief Destructor.
        virtual ~IJsonType() = default;

    private:
        /// @var CJsonFieldName m_oFieldName
        /// @brief The name of the JSON field.
        CJsonFieldName m_oFieldName;
        /// @var IBool<true> m_bIsNullvar
        /// @brief Determines if the JSON field is null.
        IBool<true> m_bIsNull;
    protected:
        /// @brief Called during deserialization to populate the object from a JSON object.
        /// @param i_oObject The JSON object containing the serialized data.
        /// @param i_bIsStrict Determines if strict deserialization rules should be applied.
        /// @return True if deserialization is successful, false otherwise.
        virtual bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) {
            return true;
        };

        /// @brief Called during serialization to convert the object to a JSON object.
        /// @param i_oObject The JSON object to populate with serialized data.
        /// @param i_bIsStrict Determines if strict serialization rules should be applied.
        /// @return True if serialization is successful, false otherwise.
        virtual bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const {
            return true;
        }

        /// @brief Called during deserialization to populate the object from a JSON object (non-strict mode).
        /// @param i_oObject The JSON object containing the serialized data.
        /// @return True if deserialization is successful, false otherwise.
        virtual bool onDeserialize(IO::CJsonObject &i_oObject) {
            return this->onDeserialize(i_oObject, false);
        }

        /// @brief Called during deserialization to populate the object from a JSON object (non-strict mode).
        /// @param i_oObject The JSON object containing the serialized data.
        /// @return True if deserialization is successful, false otherwise.
        virtual bool onSerialize(IO::CJsonObject &i_oObject) const {
            return this->onSerialize(i_oObject, false);
        }

    protected:
        /// @brief Serializes the data to a JSON object.
        ///
        /// This function serializes the data to a JSON object represented by the CJsonObject class.
        /// If the object already contains a field with the same name as this data object, the existing value is overwritten.
        ///
        /// @param i_oObject The JSON object to serialize to.
        /// @param i_bIsStrict Flag indicating whether strict serialization should be performed.
        /// If set to true, only fields marked for serialization will be included in the output.
        /// If set to false, all fields will be included in the output.
        /// @return true if serialization was successful, false otherwise.
        bool serialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) const {
            if (checkSerializeObject(i_oObject, i_bIsStrict)) {
                return true;
            }

            if (std::is_arithmetic_v<T>) {
                i_oObject.get(this->name()) = static_cast<T>(this->m_tValue);
            } else {
                i_oObject.get(this->name()) = this->m_tValue;
            }
            return true;
        }

        /// @brief Retrieves the name of the JSON field.
        /// @return The name of the JSON field as a string view.
        [[nodiscard]] std::string_view name() const {
            return this->m_oFieldName.name();
        }

        /// @brief Checks if the JSON field is null.
        /// @return True if the JSON field is null, false otherwise.
        [[nodiscard]] bool isNull() const {
            return this->m_bIsNull;
        }

        /// @brief Sets the null state of the JSON field.
        /// @param i_bState The null state to set.
        void setNull(bool i_bState) {
            this->m_bIsNull = i_bState;
        }

        /// @brief Retrieves the JSON object for the specified JSON field.
        /// @param i_oObject The JSON object to search within.
        /// @param i_bIsStrict Determines if strict deserialization rules should be applied.
        /// @return A pointer to the JSON object for the specified field, or nullptr if not found.
        IO::CJsonObject *getObject(IO::CJsonObject &i_oObject, const bool i_bIsStrict) {
            IO::CJsonObject *pObject = (i_oObject.type() != IO::EJsonType::JTArray)
                                       ? i_oObject.find(this->name())
                                       : ((this->name().empty()) ? &i_oObject
                                                                 : i_oObject.find(this->name())
                                       );

            if (!pObject) {
                if (i_bIsStrict) {
                    throw InvalidData;
                }
                IJsonType::setNull(true);
            } else if (pObject->type() == IO::EJsonType::JTNull) {
                IJsonType::setNull(true);
                pObject = nullptr;
            }
            return pObject;
        }

        /// @brief Checks if serialization of the object is allowed and handles null fields.
        /// @param i_oObject The JSON object being serialized to.
        /// @param i_bIsStrict Determines if strict serialization rules should be applied.
        /// @return True if serialization should be skipped due to null field or empty name, false otherwise.
        bool checkSerializeObject(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const {
            if (!i_bIsStrict && this->isNull()) {
                return true;
            }

            if (this->name().empty()) {
                throw InvalidObjectName;
            }

            if (this->isNull()) {
                i_oObject.get(this->name()).setNull();
            }

            return false;
        }

    public:
        /// @brief Deserializes the object from a JSON object.
        /// @param i_oObject The JSON object containing the serialized data.
        /// @param i_bIsStrict Determines if strict deserialization rules should be applied.
        /// @return True if deserialization is successful, false otherwise.
        bool doDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) {
            return this->onDeserialize(i_oObject, i_bIsStrict);
        }

        /// @brief Serializes the object to a JSON object.
        /// @param i_oObject The JSON object to populate with serialized data.
        /// @param i_bIsStrict Determines if strict serialization rules should be applied.
        /// @return True if serialization is successful, false otherwise.
        bool doSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) const {
            return this->onSerialize(i_oObject, i_bIsStrict);
        }

    public:
        /// @brief Retrieves the size of the object.
        /// @return The size of the object in bytes.
        [[nodiscard]] size_t size() const override {
            return sizeof(*this);
        }

    public:
        using TData::TData;

        /// @brief Assigns a JSON field name to the object.
        /// @tparam TJsonFieldName The type of the JSON field name (CJsonFieldName).
        /// @param i_tValue The JSON field name to assign.
        /// @return A reference to the assigned `IJsonType` object.
        template<typename TJsonFieldName,
                std::enable_if_t<std::is_same_v<CJsonFieldName, TJsonFieldName>, bool> = true
        >
        IJsonType &operator=(const TJsonFieldName &i_tValue) {
            this->m_oFieldName = i_tValue;
            return *this;
        }

        /// @brief Assigns a JSON field name to the object (move assignment).
        /// @tparam TJsonFieldName The type of the JSON field name (CJsonFieldName).
        /// @param i_tValue The JSON field name to assign.
        /// @return A reference to the assigned `IJsonType` object.
        template<typename TJsonFieldName,
                std::enable_if_t<std::is_same_v<CJsonFieldName, TJsonFieldName>, bool> = true
        >
        IJsonType &operator=(TJsonFieldName &&i_tValue) {
            this->m_oFieldName = std::move(i_tValue);
            return *this;
        };
    };

#pragma pack(pop)

    /// @brief Retrieves a JSON field by name from a struct.
    /// @tparam TField The type of the JSON field.
    /// @tparam TStruct The type of the struct.
    /// @param i_oStruct The struct to search within.
    /// @param i_sName The name of the JSON field to retrieve.
    /// @return A pointer to the JSON field if found, nullptr otherwise.
    template<typename TField, typename TStruct>
    TField *GetJsonFieldByName(TStruct &i_oStruct, const std::string_view i_sName) {
        TField *pField = nullptr;
        IterateSerializableStruct<TField>(&i_oStruct, [&](TField *i_pData) {
            if (i_pData->name() == i_sName) {
                pField = i_pData;
                return false;
            }

            return true;
        });

        return pField;
    }

    std::false_type is_json_type_class_impl(...);

    template<typename T = int, typename TData = IData<T>>
    std::true_type is_json_type_class_impl(IJsonType<T, TData> *);

    /// @brief Checks if a type is a JSON type class.
    /// @tparam T The type to check.
    template<typename T>
    using is_json_type_class = decltype(is_json_type_class_impl(std::declval<T *>()));
}