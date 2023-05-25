#pragma once

#include "Serializing/Core/Types/SerializableArithmetic.h"
#include "Serializing/Json/JsonSerializableType.h"
/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IJsonNumber
    /// @brief Represents a JSON number data type and provides serialization and deserialization functionality for arithmetic types.
    /// @tparam T The underlying arithmetic type.
    template<typename T>
    class IJsonNumber : public IJsonType<T, IArithmetic<T>> {
    public:
        /// @brief Constructs an `IJsonNumber` object with the specified field name.
        /// @param i_oFieldName The field name for the JSON number.
        IJsonNumber(const CJsonFieldName i_oFieldName) : IJsonType<T, IArithmetic<T>>(i_oFieldName) {}

    private:
        /// @brief Performs deserialization of the `IJsonNumber` object from a JSON object, with strictness control.
        /// @param i_oObject The JSON object to deserialize from.
        /// @param i_bIsStrict Specifies whether to perform strict deserialization.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) override {
            auto *pObject = this->getObject(i_oObject, i_bIsStrict);

            if (!pObject) {
                return true;
            } else if (pObject->type() == IO::EJsonType::JTNumber) {
                if (std::is_same_v<T, float>) {
                    this->operator=(static_cast<T>(pObject->toFloat()));
                } else if (std::is_same_v<T, double>) {
                    this->operator=(static_cast<T>(pObject->toDouble()));
                } else if (sizeof(T) == 8) {
                    this->operator=(static_cast<T>(pObject->toUInt64()));
                } else {
                    this->operator=(static_cast<T>(pObject->toInt()));
                }
            } else {
                throw DifferentTypesException;
            }

            return true;
        }

        /// @brief Performs serialization of the `IJsonNumber` object to a JSON object, with strictness control.
        /// @param i_oObject The JSON object to serialize to.
        /// @param i_bIsStrict Specifies whether to perform strict serialization.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) override {
            return this->serialize(i_oObject, i_bIsStrict);
        }

        /// @brief Performs deserialization of the `IJsonNumber` object from a JSON object.
        /// @param i_oObject The JSON object to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        /// @brief Performs serialization of the `IJsonNumber` object to a JSON object.
        /// @param i_oObject The JSON object to serialize to.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool onSerialize(IO::CJsonObject &i_oObject) final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<T, IArithmetic<T>>::IJsonType;

        /// @brief Assigns a value to the `IJsonNumber` object.
        /// @param i_tValue The value to assign.
        /// @return A reference to the `IJsonNumber` object.
        auto &operator=(const T &i_tValue) {
            this->m_tValue = i_tValue;
            this->setNull(false);
            return *this;
        }

        /// @brief Assigns a rvalue to the `IJsonNumber` object.
        /// @param i_tValue The rvalue to assign.
        /// @return A reference to the `IJsonNumber` object.
        auto &operator=(T &&i_tValue) {
            this->m_tValue = i_tValue;
            this->setNull(false);
            return *this;
        }
    };

    /// @brief Typedef for `IJsonNumber<char>`
    typedef IJsonNumber<char> IJsonChar;
    /// @brief Typedef for `IJsonNumber<byte>`.
    typedef IJsonNumber<byte> IJsonByte;
    /// @brief Typedef for `IJsonNumber<short>`.
    typedef IJsonNumber<short> IJsonShort;
    /// @brief Typedef for `IJsonNumber<ushort>`.
    typedef IJsonNumber<ushort> IJsonUShort;
    /// @brief Typedef for `IJsonNumber<int>`.
    typedef IJsonNumber<int> IJsonInt;
    /// @brief Typedef for `IJsonNumber<uint>`.
    typedef IJsonNumber<uint> IJsonUInt;
    /// @brief Typedef for `IJsonNumber<int64>`.
    typedef IJsonNumber<int64> IJsonInt64;
    /// @brief Typedef for `IJsonNumber<uint64>`.
    typedef IJsonNumber<uint64> IJsonUInt64;
    /// @brief Typedef for `IJsonNumber<float>`.
    typedef IJsonNumber<float> IJsonFloat;
    /// @brief Typedef for `IJsonNumber<double>`.
    typedef IJsonNumber<double> IJsonDouble;

#pragma pack(pop)
}