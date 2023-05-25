#pragma once

#include "Serializing/Core/SerializableData.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IString
    /// @brief A class representing a string value for serialization.
    ///
    /// This class provides serialization and deserialization functionality for string values.
    ///
    /// @tparam IsHidden Flag indicating whether the field is hidden during serialization.
    /// @tparam T The underlying type of the string value.
    template<bool IsHidden = false, typename T = std::string>
    class IString : public IData<T, IsHidden> {
    public:
        /// @brief Retrieves the comparison data for the string value.
        /// @return The comparison data containing the pointer to the underlying string data and its size
        [[nodiscard]] SCompareData compareData() const override {
            return {static_cast<const void *>(this->m_tValue.c_str()), this->m_tValue.size()};
        }

    private:
        /// @brief Serializes the string value to a write stream.
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization was successful, `false` otherwise.
        bool serialize(IO::CWriteStream &i_oStream) const override {
            i_oStream.push<uint>(static_cast<uint>(this->m_tValue.size()));
            i_oStream.push(this->m_tValue, false);
            return true;
        }

    private:
        /// @brief Deserializes the string value from a read stream.
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(IO::CReadStream &i_oStream) override {
            const auto nSize = static_cast<size_t>(i_oStream.get<uint>());
            this->m_tValue = i_oStream.getString(nSize);
            return true;
        }

        /// @brief Deserializes the string value from a C-style string.
        /// @param i_szString The C-style string value to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(const char *i_szString) override {
            this->m_tValue = i_szString;
            return true;
        }


        /// @brief Deserializes the string value from a vector of strings.
        /// @param i_oIt Iterator pointing to the current string value in the vector.
        /// @param i_oItEnd Iterator pointing to the end of the vector.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(std::vector<std::string>::const_iterator &i_oIt,
                         const std::vector<std::string>::const_iterator &i_oItEnd) override {
            this->m_tValue = *i_oIt++;
            return true;
        }

    public:
        using IData<T, IsHidden>::IData;
    };

#pragma pack(pop)
}