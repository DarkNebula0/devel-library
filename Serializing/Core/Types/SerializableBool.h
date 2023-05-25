#pragma once

#include "Serializing/SerializingDefines.h"
#include "Serializing/Core/SerializableData.h"
#include "Core/Utils/StringUtils.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class IBool
    /// @brief A class representing a boolean value for serialization.
    /// @tparam IsHidden Flag indicating whether the field is hidden during serialization.
    /// @tparam T The underlying type of the boolean value.
    template<bool IsHidden = false, typename T = bool>
    class IBool : public IData<T, IsHidden> {
    private:
        /// @brief Serializes the boolean value to a write stream.
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization was successful, `false` otherwise.
        bool serialize(IO::CWriteStream &i_oStream) const override {
            i_oStream.push(this->m_tValue);
            return true;
        }

    private:
        /// @brief Deserializes the boolean value from a read stream.
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(IO::CReadStream &i_oStream) override {
            this->m_tValue = i_oStream.get<T>();
            return true;
        }

        /// @brief Deserializes the boolean value from a string.
        /// @param i_szString The string value to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(const char *i_szString) override {
            this->m_tValue = (StringUtils::ToInt64(i_szString) > 0);
            return true;
        }

        /// @brief Deserializes the boolean value from a vector of strings.
        /// @param i_oIt Iterator pointing to the current string value in the vector.
        /// @param i_oItEnd Iterator pointing to the end of the vector.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(std::vector<std::string>::const_iterator &i_oIt,
                         const std::vector<std::string>::const_iterator &i_oItEnd) override {
            this->m_tValue = static_cast<T>(StringUtils::ToInt(*i_oIt));

            ++i_oIt;
            return true;
        }

    public:
        CreateSerializeOperators(T, IsHidden);
    };

#pragma pack(pop)
}