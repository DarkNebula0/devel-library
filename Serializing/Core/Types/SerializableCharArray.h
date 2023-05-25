#pragma once

#include "Core/CharArray/CharArray.h"
#include "Serializing/Core/SerializableData.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class ICharArray
    /// @brief A class representing a fixed-size character array for serialization.
    ///
    /// @tparam Size The size of the character array.
    /// @tparam IsHidden Flag indicating whether the field is hidden during serialization.
    /// @tparam T The underlying type of the character array.
    template<size_t Size, bool IsHidden = false, typename T = CCharArray<Size>>
    class ICharArray : public IData<T, IsHidden> {
    private:
        /// @brief Serializes the character array to a write stream.
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization was successful, `false` otherwise.
        bool serialize(IO::CWriteStream &i_oStream) override {
            i_oStream.push<Size>(this->m_tValue);
            return true;
        }

    private:
        /// @brief Deserializes the character array from a read stream.
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(IO::CReadStream &i_oStream) override {
            this->m_tValue = i_oStream.getArray<Size>();
            return true;
        }

        /// @brief Deserializes the character array from a string.
        /// @param i_szValue The string value to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(const char *i_szValue) override {
            this->m_tValue = i_szValue;
            return true;
        }

        /// @brief Deserializes the character array from a vector of strings.
        /// @param i_oIt Iterator pointing to the current string value in the vector.
        /// @param i_oItEnd Iterator pointing to the end of the vector.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(std::vector<std::string>::const_iterator &i_oIt,
                         const std::vector<std::string>::const_iterator &i_oItEnd) override {
            this->m_tValue = *i_oIt++;
            return true;
        }

    public:
        CreateSerializeOperators(T, IsHidden);
    };

#pragma pack(pop)
}