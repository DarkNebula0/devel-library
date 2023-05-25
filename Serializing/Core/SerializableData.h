#pragma once

#include <vector>
#include <string>
#include <functional>

#include "Core/Global.h"
#include "Core/Global.h"
#include "IO/WriteStream/WriteStream.h"
#include "IO/ReadStream/ReadStream.h"

#include "Serializing/SerializingDefines.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
    /// @struct Devel::Serializing::SCompareData
    /// @brief Structure for comparing serialized data.
    struct SCompareData {
        /// @brief Constructs an `SCompareData` object with the specified data and size.
        /// @param i_pData The pointer to the data.
        /// @param i_nSize The size of the data.
        SCompareData(const void *i_pData, const size_t i_nSize)
                : pData(i_pData), nSize(i_nSize) {}

        /// @var const void *pData
        /// @brief The pointer to the data.
        const void *pData;

        /// @var const size_t nSize
        /// @brief The size of the data.
        const size_t nSize;
    };

#pragma pack(push, 1)

    /// @class Devel::Serializing::ISerializable
    /// @brief Base class for structures.
    class IStruct {
    };

    /// @class Devel::Serializing::IField
    /// @brief Base class for fields.
    /// @details This class is used to provide a common interface for all fields.
    // Needed for output and input stream operator
    class IField {
    };

    /// @class Devel::Serializing::IValue
    /// @brief Template class representing a value.
    /// @tparam T The type of the value.
    template<typename T>
    class IValue : public IField {
    public:
        /// @brief Constructs an `IValue` object with the specified arguments.
        /// @tparam TArgs The types of the arguments.
        /// @param i_tArgs The arguments to construct the value.
        template<typename ...TArgs, std::enable_if_t<std::is_constructible_v<T, TArgs...>> * = nullptr>
        IValue(TArgs... i_tArgs)
                : m_tValue(std::forward<TArgs>(i_tArgs)...) {}

    public:
        /// @brief Returns the value.
        /// @return The value.
        const T &value() const {
            return this->m_tValue;
        }

        /// @brief Returns a reference to the value.
        /// @return A reference to the value.
        T &value() {
            return this->m_tValue;
        }

    protected:
        /// @var T m_tValue
        /// @brief The value.
        T m_tValue;
    };

    /// @class Devel::Serializing::IData
    /// @brief Template class representing a data field.
    /// @tparam T The type of the data.
    /// @tparam IsHidden Specifies whether the field is hidden.
    template<typename T = int, bool IsHidden = false>
    class IData : public IValue<T> {
    public:
        using IValue<T>::IValue;

        /// @brief Default destructor.
        virtual ~IData() = default;

    public:
        /// @brief Serializes the data to a write stream.
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization is successful, `false` otherwise.
        bool doSerialize(IO::CWriteStream &i_oStream) const {
            if (!IsHidden) {
                return this->serialize(i_oStream);
            }

            return true;
        }

    private:
        /// @brief Serializes the data to a write stream.
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization is successful, `false` otherwise.
        virtual bool serialize(IO::CWriteStream &i_oStream) const {
            return true;
        }

    public:
        /// @brief Deserializes the data from a read stream.
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool doDeserialize(IO::CReadStream &i_oStream) {
            if (!IsHidden) {
                return this->deserialize(i_oStream);
            }

            return true;
        }

        /// @brief Deserializes the data from a string.
        /// @param i_szString The string to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool doDeserialize(const char *i_szString) {
            if (!IsHidden) {
                return this->deserialize(i_szString);
            }

            return true;
        }

        /// @brief Deserializes the data from a range of strings.
        /// @param i_oIt An iterator pointing to the current string.
        /// @param i_oItEnd An iterator pointing to the end of the range of strings.
        /// @return `true` if deserialization is successful, `false` otherwise.
        bool doDeserialize(std::vector<std::string>::const_iterator &i_oIt,
                           const std::vector<std::string>::const_iterator &i_oItEnd) {
            if (!IsHidden) {
                return this->deserialize(i_oIt, i_oItEnd);
            }

            return true;
        }

    private:
        /// @brief Deserializes the data from a read stream.
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        virtual bool deserialize(IO::CReadStream &i_oStream) {
            return true;
        }

        /// @brief Deserializes the data from a string.
        /// @param i_szString The string to deserialize from.
        /// @return `true` if deserialization is successful, `false` otherwise.
        virtual bool deserialize(const char *i_szString) {
            return true;
        }

        /// @brief Deserializes the data from a range of strings.
        /// @param i_oIt An iterator pointing to the current string.
        /// @param i_oItEnd An iterator pointing to the end of the range of strings.
        /// @return `true` if deserialization is successful, `false` otherwise.
        virtual bool deserialize(std::vector<std::string>::const_iterator &i_oIt,
                                 const std::vector<std::string>::const_iterator &i_oItEnd) {
            ++i_oIt;
            return true;
        }

    public:
        /// @brief Returns the size of the data.
        /// @return The size of the data.
        [[nodiscard]] virtual size_t size() const {
            return sizeof(*this);
        }

        /// @brief Returns whether the field is hidden.
        /// @return `true` if the field is hidden, `false` otherwise.
        [[nodiscard]] virtual bool isHidden() const {
            return IsHidden;
        }

        /// @brief Returns the compare data for the data field.
        /// @return The compare data.
        [[nodiscard]] virtual SCompareData compareData() const {
            return {static_cast<const void *>(&this->m_tValue), sizeof(T)};
        }

    public:
        /// @brief Returns an iterator pointing to the beginning of the value.
        /// @return An iterator pointing to the beginning of the value.
        auto begin() const {
            return this->m_tValue.begin();
        }

        /// @brief Returns an iterator pointing to the end of the value.
        /// @return An iterator pointing to the end of the value.
        auto end() const {
            return this->m_tValue.end();
        }

    public:
        /// @brief Returns a reference to the value at the specified index.
        /// @param i_nIndex The index of the value.
        /// @return A reference to the value at the specified index.
        auto &operator[](const size_t i_nIndex) {
            return this->m_tValue[i_nIndex];
        }

        /// @brief Returns a const reference to the value at the specified index.
        /// @param i_nIndex The index of the value.
        /// @return A const reference to the value at the specified index.
        const auto &operator[](const size_t i_nIndex) const {
            return this->m_tValue[i_nIndex];
        }

        /// @brief Pre-decrement operator.
        /// @return A reference to the data after decrement.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator--() {
            --this->m_tValue;
            return *this;
        }

        /// @brief Post-decrement operator.
        /// @return A reference to the data before decrement.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator--(int) {
            --this->m_tValue;
            return *this;
        }


        /// @brief Pre-increment operator.
        /// @return A reference to the data after increment.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator++() {
            ++this->m_tValue;
            return *this;
        }

        /// @brief Post-increment operator.
        /// @return A reference to the data before increment.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator++(int) {
            ++this->m_tValue;
            return *this;
        }

        /// @brief Addition assignment operator.
        /// @param i_tValue The value to add.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator+=(const T &i_tValue) {
            this->m_tValue += i_tValue;
            return *this;
        }

        /// @brief Subtraction assignment operator.
        /// @param i_tValue The value to subtract.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator-=(const T &i_tValue) {
            this->m_tValue -= i_tValue;
            return *this;
        }

        /// @brief Multiplication assignment operator.
        /// @param i_tValue The value to multiply.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator*=(const T &i_tValue) {
            this->m_tValue *= i_tValue;
            return *this;
        }

        /// @brief Division assignment operator.
        /// @param i_tValue The value to divide.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator/=(const T &i_tValue) {
            this->m_tValue /= i_tValue;
            return *this;
        }

        /// @brief Modulus assignment operator.
        /// @param i_tValue The value to calculate modulus with.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator%=(const T &i_tValue) {
            this->m_tValue %= i_tValue;
            return *this;
        }

        /// @brief Bitwise AND assignment operator.
        /// @param i_tValue The value to perform bitwise AND with.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator&=(const T &i_tValue) {
            this->m_tValue &= i_tValue;
            return *this;
        }

        /// @brief Bitwise OR assignment operator.
        /// @param i_tValue The value to perform bitwise OR with.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator|=(const T &i_tValue) {
            this->m_tValue |= i_tValue;
            return *this;
        }

        /// @brief Bitwise XOR assignment operator.
        /// @param i_tValue The value to perform bitwise XOR with.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator^=(const T &i_tValue) {
            this->m_tValue ^= i_tValue;
            return *this;
        }

        /// @brief Left shift assignment operator.
        /// @param i_tValue The value to shift left.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator<<=(const T &i_tValue) {
            this->m_tValue <<= i_tValue;
            return *this;
        }

        /// @brief Right shift assignment operator.
        /// @param i_tValue The value to shift right.
        /// @return A reference to the modified data.
        SerializerEnableIfNotArithmetic(IData<T> &)
        operator>>=(const T &i_tValue) {
            this->m_tValue >>= i_tValue;
            return *this;
        }

        /// @brief Addition operator.
        /// @param i_tValue The value to add.
        /// @return The result of the addition.
        SerializerEnableIfNotArithmetic(T)
        operator+(const T &i_tValue) const {
            return this->m_tValue + i_tValue;
        }

        /// @brief Subtraction operator.
        /// @param i_tValue The value to subtract.
        /// @return The result of the subtraction.
        SerializerEnableIfNotArithmetic(T)
        operator-(const T &i_tValue) const {
            return this->m_tValue - i_tValue;
        }

        /// @brief Multiplication operator.
        /// @param i_tValue The value to multiply.
        /// @return The result of the multiplication.
        SerializerEnableIfNotArithmetic(T)
        operator*(const T &i_tValue) const {
            return this->m_tValue * i_tValue;
        }

        /// @brief Division operator.
        /// @param i_tValue The value to divide.
        /// @return The result of the division.
        SerializerEnableIfNotArithmetic(T)
        operator/(const T &i_tValue) const {
            return this->m_tValue / i_tValue;
        }

        /// @brief Modulus operator.
        /// @param i_tValue The value to calculate modulus with.
        /// @return The result of the modulus operation.
        SerializerEnableIfNotArithmetic(T)
        operator%(const T &i_tValue) const {
            return this->m_tValue % i_tValue;
        }

        /// @brief Bitwise AND operator.
        /// @param i_tValue The value to perform bitwise AND with.
        /// @return The result of the bitwise AND operation.
        SerializerEnableIfNotArithmetic(T)
        operator&(const T &i_tValue) const {
            return this->m_tValue & i_tValue;
        }

        /// @brief Bitwise OR operator.
        /// @param i_tValue The value to perform bitwise OR with.
        /// @return The result of the bitwise OR operation.
        SerializerEnableIfNotArithmetic(T)
        operator|(const T &i_tValue) const {
            return this->m_tValue | i_tValue;
        }

        /// @brief Bitwise XOR operator.
        /// @param i_tValue The value to perform bitwise XOR with.
        /// @return The result of the bitwise XOR operation.
        SerializerEnableIfNotArithmetic(T)
        operator^(const T &i_tValue) const {
            return this->m_tValue ^ i_tValue;
        }

        /// @brief Left shift operator.
        /// @param i_tValue The value to shift left.
        /// @return The result of the left shift operation.
        SerializerEnableIfNotArithmetic(T)
        operator<<(const T &i_tValue) const {
            return this->m_tValue << i_tValue;
        }

        /// @brief Right shift operator.
        /// @param i_tValue The value to shift right.
        /// @return The result of the right shift operation.
        SerializerEnableIfNotArithmetic(T)
        operator>>(const T &i_tValue) const {
            return this->m_tValue >> i_tValue;
        }

        /// @brief Logical NOT operator.
        /// @return The result of the logical NOT operation.
        SerializerEnableIfNotArithmetic(bool)
        operator!() const {
            return !this->m_tValue;
        }

        /// @brief Equality operator.
        /// @param i_tValue The value to compare for equality.
        /// @return `true` if the values are equal, `false` otherwise.
        SerializerEnableIfNotArithmetic(bool)
        operator==(const T &i_tValue) const {
            return this->m_tValue == i_tValue;
        }

        /// @brief Inequality operator.
        /// @param i_tValue The value to compare for inequality.
        /// @return `true` if the values are not equal, `false` otherwise.
        SerializerEnableIfNotArithmetic(bool)
        operator!=(const T &i_tValue) const {
            return this->m_tValue != i_tValue;
        }

        /// @brief Greater than operator.
        /// @param i_tValue The value to compare as the right-hand side.
        /// @return `true` if the left-hand side value is greater than the right-hand side value, `false` otherwise.
        SerializerEnableIfNotArithmetic(bool)
        operator>(const T &i_tValue) const {
            return this->m_tValue > i_tValue;
        }

        /// @brief Greater than or equal to operator.
        /// @param i_tValue The value to compare as the right-hand side.
        /// @return `true` if the left-hand side value is greater than or equal to the right-hand side value, `false` otherwise.
        SerializerEnableIfNotArithmetic(bool)
        operator>=(const T &i_tValue) const {
            return this->m_tValue >= i_tValue;
        }

        /// @brief Less than operator.
        /// @param i_tValue The value to compare as the right-hand side.
        /// @return `true` if the left-hand side value is less than the right-hand side value, `false` otherwise.
        SerializerEnableIfNotArithmetic(bool)
        operator<(const T &i_tValue) const {
            return this->m_tValue < i_tValue;
        }

        /// @brief Less than or equal to operator.
        /// @param i_tValue The value to compare as the right-hand side.
        /// @return `true` if the left-hand side value is less than or equal to the right-hand side value, `false` otherwise.
        SerializerEnableIfNotArithmetic(bool)
        operator<=(const T &i_tValue) const {
            return this->m_tValue <= i_tValue;
        }

        /// @brief Arrow operator.
        /// @return A pointer to the value.
        template<typename T1 = T>
        typename std::enable_if<std::is_pointer<T1>::value, T>::type
        operator->() const {
            return this->m_tValue;
        }

        /// @brief Arrow operator.
        /// @return A pointer to the value.
        template<typename T1 = T>
        typename std::enable_if<!std::is_pointer<T1>::value, T *>::type
        operator->() {
            return &this->m_tValue;
        }

        /// @brief Dereference operator.
        /// @return A reference to the value.
        T &operator*() {
            return *this->m_tValue;
        }

        /// @brief Dereference operator.
        /// @return A const reference to the value.
        const T &operator*() const {
            return *this->m_tValue;
        }

        /// @brief Conversion operator to T&.
        /// @return A reference to the value.
        operator T &() {
            return this->m_tValue;
        }

        /// @brief Conversion operator to const T&.
        /// @return A const reference to the value.
        operator const T &() const {
            return this->m_tValue;
        }
    };

#pragma pack(pop)

    /// @brief Output stream operator for IValue.
    /// @tparam T The type of the value.
    /// @param i_oStream The output stream.
    /// @param i_tData The IValue object.
    /// @return The modified output stream
    template<typename T>
    std::ostream &operator<<(std::ostream &i_oStream, const IValue<T> &i_tData) {
        i_oStream << i_tData.value();
        return i_oStream;
    }

    /// @brief Input stream operator for IValue.
    /// @tparam T The type of the value.
    /// @param i_oStream The input stream.
    /// @param i_tData The IValue object.
    /// @return The modified input stream.
    template<typename T>
    std::istream &operator>>(std::istream &i_oStream, const IValue<T> &i_tData) {
        i_oStream >> i_tData.value();
        return i_oStream;
    }

    /// @brief Wide output stream operator for IValue.
    /// @tparam T The type of the value.
    /// @param i_oStream The wide output stream.
    /// @param i_tData The IValue object.
    /// @return The modified wide output stream.
    template<typename T>
    std::wostream &operator<<(std::wostream &i_oStream, const IValue<T> &i_tData) {
        i_oStream << i_tData.value();
        return i_oStream;
    }

    /// @brief Wide input stream operator for IValue.
    /// @tparam T The type of the value.
    /// @param i_oStream The wide input stream.
    /// @param i_tData The IValue object.
    /// @return The modified wide input stream.
    template<typename T>
    std::wistream &operator>>(std::wistream &i_oStream, const IValue<T> &i_tData) {
        i_oStream >> i_tData.value();
        return i_oStream;
    }


    /// @brief Iterates over a serializable struct and applies a callback function to each field.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_pStruct Pointer to the struct object.
    /// @param i_pCallback The callback function to apply to each field.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return `true` if the iteration was completed without early termination, `false` otherwise.
    // When callback return false then break iteration
    template<typename TStructFieldType = IData<>, typename TStruct>
    bool IterateSerializableStruct(const TStruct *i_pStruct, std::function<bool(const TStructFieldType *)> i_pCallback,
                                   const size_t i_nStructSize = sizeof(TStruct)) {

        for (size_t i = ((std::is_base_of_v<IStruct, TStruct> && std::is_polymorphic_v<TStruct>) ? sizeof(void *) : 0);
             i < i_nStructSize;) {
            auto pData = reinterpret_cast<const TStructFieldType *>((reinterpret_cast<const char *>(i_pStruct) + i));

            if (!i_pCallback(pData)) {
                return false;
            }

            i += pData->size();
        }

        return true;
    }

    /// @brief Iterates over a serializable struct and applies a callback function to each field.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_oStruct The struct object.
    /// @param i_pCallback The callback function to apply to each field.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return `true` if the iteration was completed without early termination, `false` otherwise.
    template<typename TStructFieldType = IData<>, typename TStruct>
    bool IterateSerializableStruct(const TStruct &i_oStruct, std::function<bool(const TStructFieldType *)> i_pCallback,
                                   const size_t i_nStructSize = sizeof(TStruct)) {
        return IterateSerializableStruct<TStructFieldType, TStruct>(&i_oStruct, i_pCallback, i_nStructSize);
    }

    /// @brief Iterates over a deserializable struct and applies a callback function to each field.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_pStruct Pointer to the struct object.
    /// @param i_pCallback The callback function to apply to each field.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return `true` if the iteration was completed without early termination, `false` otherwise.
    // When callback return false then break iteration
    template<typename TStructFieldType = IData<>, typename TStruct>
    bool IterateDeserializableStruct(TStruct *i_pStruct, std::function<bool(TStructFieldType *)> i_pCallback,
                                     const size_t i_nStructSize = sizeof(TStruct)) {
        for (size_t i = (std::has_virtual_destructor_v<TStruct> ? sizeof(void *) : 0); i < i_nStructSize;) {
            auto *pData = SerializableGetField(TStructFieldType, i_pStruct, i);

            if (!i_pCallback(pData)) {
                return false;
            }

            i += pData->size();
        }

        return true;
    }

    /// @brief Iterates over a deserializable struct and applies a callback function to each field.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_oStruct The struct object.
    /// @param i_pCallback The callback function to apply to each field.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return `true` if the iteration was completed without early termination, `false` otherwise.
    template<typename TStructFieldType = IData<>, typename TStruct>
    bool IterateDeserializableStruct(TStruct &i_oStruct, std::function<bool(TStructFieldType *)> i_pCallback,
                                     const size_t i_nStructSize = sizeof(TStruct)) {
        return IterateSerializableStruct<TStructFieldType, TStruct>(&i_oStruct, i_pCallback, i_nStructSize);
    }


    /// @brief Gets the offsets of the serializable fields in a struct.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_pStruct Pointer to the struct object.
    /// @param i_fIncludeHidden Flag indicating whether to include hidden fields.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return A vector containing the offsets of the serializable fields.
    template<typename TStructFieldType = IData<>, typename TStruct>
    std::vector<size_t> GetSerializableFieldOffsets(const TStruct *i_pStruct, const bool i_fIncludeHidden = true,
                                                    const size_t i_nStructSize = sizeof(TStruct)) {
        std::vector<size_t> anOffsets;
        anOffsets.reserve(10);

        for (size_t i = (std::has_virtual_destructor_v<TStruct> ? sizeof(void *) : 0); i < i_nStructSize;) {
            auto *pData = SerializableGetField(TStructFieldType, i_pStruct, i);

            if (i_fIncludeHidden || !pData->isHidden()) {
                anOffsets.push_back(i);
            }

            i += pData->size();
        }

        return anOffsets;
    }

    /// @brief Gets the offsets of the serializable fields in a struct.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_pStruct Pointer to the struct object.
    /// @param i_fIncludeHidden Flag indicating whether to include hidden fields.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return A vector containing the offsets of the serializable fields.
    template<typename TStructFieldType = IData<>, typename TStruct>
    std::vector<size_t> GetSerializableFieldOffsets(const TStruct &i_oStruct, const bool i_fIncludeHidden = true,
                                                    const size_t i_nStructSize = sizeof(TStruct)) {
        return GetSerializableFieldOffsets<TStructFieldType, TStruct>(&i_oStruct, i_fIncludeHidden, i_nStructSize);
    }


    /// @brief Gets the offsets of the serializable fields in a struct.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_oStruct The struct object.
    /// @param i_fIncludeHidden Flag indicating whether to include hidden fields.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return A vector containing the offsets of the serializable fields.
    template<typename TStructFieldType = IData<>, typename TStruct>
    TStructFieldType *GetSerializableFieldByIndex(const TStruct *i_pStruct, const size_t i_nIndex) {
        TStructFieldType *pReturn = nullptr;
        size_t nCurrentIndex = 0;
        IterateSerializableStruct<TStructFieldType>(i_pStruct, [&](TStructFieldType *i_pData) {
            if (nCurrentIndex == i_nIndex) {
                pReturn = i_pData;
                return false;
            }

            nCurrentIndex++;

            return true;
        });

        return pReturn;
    }

    /// @brief Gets a serializable field in a struct by index.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_pStruct Pointer to the struct object.
    /// @param i_nIndex The index of the field.
    /// @return A pointer to the serializable field, or nullptr if not found.
    template<typename TStructFieldType = IData<>, typename TStruct>
    TStructFieldType *GetSerializableFieldByIndex(const TStruct &i_oStruct, const size_t i_nIndex) {
        return GetSerializableFieldByIndex<TStructFieldType, TStruct>(&i_oStruct, i_nIndex);
    }


    /// @brief Compares two serializable structs for equality.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_pStruct Pointer to the first struct object.
    /// @param i_pCompareStruct Pointer to the second struct object.
    /// @param i_fIncludeHidden Flag indicating whether to include hidden fields in the comparison.
    /// @return `true` if the structs are equal, `false` otherwise.
    template<typename TStructFieldType = IData<>, typename TStruct>
    bool CompareSerializableStruct(TStruct *i_pStruct, TStruct *i_pCompareStruct, const bool i_fIncludeHidden = false) {
        std::vector<size_t> anOffsets = GetSerializableFieldOffsets(i_pStruct, i_fIncludeHidden);

        for (size_t nOffset: anOffsets) {
            auto *pFirst = SerializableGetField(TStructFieldType, i_pStruct, nOffset);
            auto *pSecond = SerializableGetField(TStructFieldType, i_pCompareStruct, nOffset);

            const SCompareData oFirstCompareData = pFirst->compareData();
            const SCompareData oSecondCompareData = pSecond->compareData();

            if (oFirstCompareData.nSize != oSecondCompareData.nSize) {
                return false;
            }

            if (memcmp(oFirstCompareData.pData, oSecondCompareData.pData, oFirstCompareData.nSize) != 0) {
                return false;
            }
        }

        return true;
    }

    /// @brief Compares two serializable structs for equality.
    /// @tparam TStructFieldType The type of the struct field.
    /// @tparam TStruct The type of the struct.
    /// @param i_oStruct The first struct object.
    /// @param i_oCompareStruct The second struct object.
    /// @param i_fIncludeHidden Flag indicating whether to include hidden fields in the comparison.
    /// @return `true` if the structs are equal, `false` otherwise.
    template<typename TStructFieldType = IData<>, typename TStruct>
    bool CompareSerializableStruct(TStruct &i_oStruct, TStruct &i_oCompareStruct, const bool i_fIncludeHidden = false) {
        return CompareSerializableStruct<TStructFieldType, TStruct>(&i_oStruct, &i_oCompareStruct, i_fIncludeHidden);
    }

    /// @brief Check if a type is a data class.
    /// @tparam T The type to check.
    /// @return `true` if the type is a data class, `false` otherwise.
    std::false_type is_data_class_impl(...);

    template<typename T = int, bool IsHidden = false>
    std::true_type is_data_class_impl(IData<T, IsHidden> *);

    template<typename T>
    using is_data_class = decltype(is_data_class_impl(std::declval<T *>()));
}