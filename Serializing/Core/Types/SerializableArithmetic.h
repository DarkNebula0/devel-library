#pragma once

#include "Core/Typedef.h"
#include "Core/Global.h"
#include "Core/Utils/StringUtils.h"
#include "Serializing/Core/SerializableData.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IArithmetic
    /// @brief Class representing an arithmetic value for serialization.
    /// @tparam T The type of the arithmetic value.
    /// @tparam IsHidden Flag indicating if the field should be hidden during serialization.
    /// @tparam Enable SFINAE enable parameter to restrict the template to arithmetic types.
    template<typename T, bool IsHidden = false, typename std::enable_if<std::is_arithmetic<T>::value> * = nullptr>
    class IArithmetic : public IData<T, IsHidden> {
    private:
        /// @brief Serializes the arithmetic value to a write stream.
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization was successful, `false` otherwise.
        bool serialize(IO::CWriteStream &i_oStream) const override {
            i_oStream.push(this->m_tValue);
            return true;
        }

    private:
        /// @brief Deserializes the arithmetic value from a read stream.
        /// @param i_oStream The read stream to deserialize from.
        /// @return true if deserialization was successful, false otherwise.
        bool deserialize(IO::CReadStream &i_oStream) override {
            this->m_tValue = i_oStream.get<T>();
            return true;
        }

        /// @brief Deserializes the arithmetic value from a string.
        /// @param i_szValue The string value to deserialize from.
        /// @return true if deserialization was successful, false otherwise.
        bool deserialize(const char *i_szValue) override {
            if (sizeof(T) <= 4) {
                this->m_tValue = static_cast<T>(StringUtils::ToUInt(i_szValue));
            } else {
                this->m_tValue = static_cast<T>(StringUtils::ToUInt64(i_szValue));
            }

            return true;
        }

        /// @brief Deserializes the arithmetic value from a vector of strings.
        /// @param i_oIt Iterator pointing to the current string value in the vector.
        /// @param i_oItEnd Iterator pointing to the end of the vector.
        /// @return true if deserialization was successful, false otherwise.
        bool deserialize(std::vector<std::string>::const_iterator &i_oIt,
                         const std::vector<std::string>::const_iterator &i_oItEnd) override {
            if (sizeof(T) <= 4) {
                this->m_tValue = static_cast<T>(StringUtils::ToUInt(*i_oIt));
            } else {
                this->m_tValue = static_cast<T>(StringUtils::ToUInt64(*i_oIt));
            }

            ++i_oIt;
            return true;
        }

    public:
        CreateSerializeOperators(T, IsHidden);
    };

    /// @brief Alias for IArithmetic<char> representing a character value.
    template<bool IsHidden = false>
    using IChar = IArithmetic<char, IsHidden>;

    /// @brief Alias for IArithmetic<byte> representing a byte value.
    template<bool IsHidden = false>
    using IByte = IArithmetic<byte, IsHidden>;

    /// @brief Alias for IArithmetic<short> representing a short integer value.
    template<bool IsHidden = false>
    using IShort = IArithmetic<short, IsHidden>;

    /// @brief Alias for IArithmetic<ushort> representing an unsigned short integer value.
    template<bool IsHidden = false>
    using IUShort = IArithmetic<ushort, IsHidden>;

    /// @brief Alias for IArithmetic<int> representing an integer value.
    template<bool IsHidden = false>
    using IInt = IArithmetic<int, IsHidden>;

    /// @brief Alias for IArithmetic<uint> representing an unsigned integer value.
    template<bool IsHidden = false>
    using IUInt = IArithmetic<uint, IsHidden>;

    /// @brief Alias for IArithmetic<int64> representing a 64-bit integer value.
    template<bool IsHidden = false>
    using IInt64 = IArithmetic<int64, IsHidden>;

    /// @brief Alias for IArithmetic<int64> representing a 64-bit integer value.
    template<bool IsHidden = false>
    using IUInt64 = IArithmetic<uint64, IsHidden>;

    /// @brief Alias for IArithmetic representing an enumeration value.
    template<typename T, bool IsHidden = false>
    using IEnum = Devel::Serializing::IArithmetic<T, IsHidden>;
#pragma pack(pop)
}