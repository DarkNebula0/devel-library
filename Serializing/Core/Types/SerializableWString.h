#pragma once

#include "Serializing/Core/SerializableData.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IWString
    /// @brief A class representing a wide string value for serialization.
    ///
    /// This class specializes the IData class for wide string values.
    ///
    /// @tparam IsHidden Flag indicating whether the field is hidden during serialization.
    /// @tparam T The underlying type of the wide string value.
    template<bool IsHidden = false, typename T = std::wstring>
    class IWString : public IData<T, IsHidden> {
    public:
        /// @brief Retrieves the compare data for the wide string value.
        /// @return The compare data containing the pointer to the underlying string data and its size in bytes.
        SCompareData compareData() const override {
            return {static_cast<const void *>(this->m_tValue.c_str()), this->m_tValue.size() * 2};
        }

    private:
        /// @brief Serializes the wide string value to a write stream.
        ///
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization was successful, `false` otherwise.
        bool serialize(IO::CWriteStream &i_oStream) override {
            i_oStream.push<uint>(static_cast<uint>(this->m_tValue.size()));
            i_oStream.push(this->m_tValue, false);
            return true;
        }

    private:
        /// @brief Deserializes the wide string value from a read stream.
        ///
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(IO::CReadStream &i_oStream) override {
            const size_t nSize = static_cast<size_t>(i_oStream.get<uint>());
            this->m_tValue = i_oStream.getWString(nSize);
            return true;
        }

        /// @brief Deserializes the wide string value from a C-style string.
        ///
        /// @param i_szString The C-style string value to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(const char *i_szString) override {
            this->m_tValue = std::wstring(i_szString, i_szString + strlen(i_szString));
            return true;
        }

        /// @brief Deserializes the wide string value from a vector of strings.
        ///
        /// @param i_oIt Iterator pointing to the current string value in the vector.
        /// @param i_oItEnd Iterator pointing to the end of the vector.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(std::vector<std::string>::const_iterator &i_oIt,
                         const std::vector<std::string>::const_iterator &i_oItEnd) override {
            this->m_tValue = std::wstring(i_oIt->begin(), i_oIt->end());
            return true;
        }

    public:
        CreateSerializeOperators(T, IsHidden);
    };

#pragma pack(pop)
}