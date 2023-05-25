#pragma once

#include "Serializing/Core/SerializerStream.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
#pragma pack(push, 1)

    /// @class Devel::Serializing::IVector
    /// @brief A class representing a vector for serialization.
    ///
    /// This class provides serialization and deserialization functionality for vectors.
    ///
    /// @tparam Type The element type of the vector.
    /// @tparam IsHidden Flag indicating whether the field is hidden during serialization.
    /// @tparam TSize The size type used for specifying the size of the vector.
    /// @tparam T The underlying vector type.
    template<typename Type = int, bool IsHidden = false, typename TSize = uint, typename T = std::vector<Type>>
    class IVector : public IData<T, IsHidden> {
    private:
        /// @brief Helper function for serializing vector elements.
        ///
        /// This function is specialized for different element types:
        /// - If the element type is derived from IField, it calls doSerialize() on each element.
        /// - If the element type is derived from IStruct, it calls SerializeStream() on each element.
        /// - For other element types, it pushes each element onto the write stream.
        ///
        /// @tparam TCopy The element type of the vector.
        /// @param i_oStream The write stream to serialize to.
        template<typename TCopy = Type, typename std::enable_if_t<std::is_base_of_v<Serializing::IField, TCopy>> * = nullptr>
        void _serialize(IO::CWriteStream &i_oStream) {
            for (TCopy &tType: this->m_tValue) {
                tType.doSerialize(i_oStream);
            }
        }

        /// @brief Helper function for serializing vector elements.
        ///
        /// This function is specialized for different element types:
        /// - If the element type is derived from IStruct, it calls SerializeStream() on each element.
        /// - For other element types, it pushes each element onto the write stream.
        ///
        /// @tparam TCopy The element type of the vector.
        /// @param i_oStream The write stream to serialize to.
        template<typename TCopy = Type, typename std::enable_if_t<std::is_base_of_v<Serializing::IStruct, TCopy>> * = nullptr>
        void _serialize(IO::CWriteStream &i_oStream) {
            for (TCopy &tType: this->m_tValue) {
                Serializing::SerializeStream(tType, i_oStream);
            }
        }

        /// @brief Helper function for serializing vector elements.
        ///
        /// This function is specialized for element types that are not derived from IField or IStruct.
        /// It simply pushes each element onto the write stream.
        ///
        /// @tparam TCopy The element type of the vector.
        /// @param i_oStream The write stream to serialize to.
        template<typename TCopy = Type,
                typename std::enable_if_t<!std::is_base_of_v<Serializing::IField, TCopy>> * = nullptr,
                typename std::enable_if_t<!std::is_base_of_v<Serializing::IStruct, TCopy>> * = nullptr>
        void _serialize(IO::CWriteStream &i_oStream) {
            for (const TCopy &tType: this->m_tValue) {
                i_oStream.push<TCopy>(tType);
            }
        }

        /// @brief Serializes the vector to a write stream.
        ///
        /// @param i_oStream The write stream to serialize to.
        /// @return `true` if serialization was successful, `false` otherwise.
        bool serialize(IO::CWriteStream &i_oStream) override {
            i_oStream.push<TSize>(static_cast<TSize>(this->m_tValue.size()));
            this->_serialize(i_oStream);
            return true;
        }

    private:
        /// @brief Helper function for deserializing vector elements.
        ///
        /// This function is specialized for different element types:
        /// - If the element type is derived from IField, it calls doDeserialize() on each element.
        /// - If the element type is derived from IStruct, it calls DeserializeStream() on each element.
        /// - For other element types, it retrieves each element from the read stream.
        ///
        /// @tparam TCopy The element type of the vector.
        /// @param i_oStream The read stream to deserialize from.
        /// @param i_nSize The size of the vector.
        template<typename TCopy = Type, typename std::enable_if_t<std::is_base_of_v<Serializing::IField, TCopy>> * = nullptr>
        void _deserialize(IO::CReadStream &i_oStream, size_t i_nSize) {
            for (; i_nSize > 0; i_nSize--) {
                this->m_tValue.emplace_back();
                (--this->m_tValue.end())->doDeserialize(i_oStream);
            }
        }

        /// @brief Helper function for deserializing vector elements.
        ///
        /// This function is specialized for different element types:
        /// - If the element type is derived from IStruct, it calls DeserializeStream() on each element.
        /// - For other element types, it retrieves each element from the read stream.
        ///
        /// @tparam TCopy The element type of the vector.
        /// @param i_oStream The read stream to deserialize from.
        /// @param i_nSize The size of the vector.
        template<typename TCopy = Type, typename std::enable_if_t<std::is_base_of_v<Serializing::IStruct, TCopy>> * = nullptr>
        void _deserialize(IO::CReadStream &i_oStream, size_t i_nSize) {
            for (; i_nSize > 0; i_nSize--) {
                this->m_tValue.emplace_back();
                Serializing::DeserializeStream(*(--this->m_tValue.end()), i_oStream);
            }
        }

        /// @brief Helper function for deserializing vector elements.
        ///
        /// This function is specialized for element types that are not derived from IField or IStruct.
        /// It retrieves each element from the read stream.
        ///
        /// @tparam TCopy The element type of the vector.
        /// @param i_oStream The read stream to deserialize from.
        /// @param i_nSize The size of the vector.
        template<typename TCopy = Type,
                typename std::enable_if_t<!std::is_base_of_v<Serializing::IField, TCopy>> * = nullptr,
                typename std::enable_if_t<!std::is_base_of_v<Serializing::IStruct, TCopy>> * = nullptr>
        void _deserialize(IO::CReadStream &i_oStream, size_t i_nSize) {
            for (; i_nSize > 0; i_nSize--) {
                this->m_tValue.push_back(i_oStream.get<Type>());
            }
        }

        /// @brief Deserializes the vector from a read stream.
        ///
        /// @param i_oStream The read stream to deserialize from.
        /// @return `true` if deserialization was successful, `false` otherwise.
        bool deserialize(IO::CReadStream &i_oStream) override {
            const TSize nSize = i_oStream.get<TSize>();
            this->m_tValue.reserve(nSize > 30 ? 30 : nSize);

            this->_deserialize(i_oStream, nSize);
            return true;
        }

    public:
        CreateSerializeOperators(T, IsHidden);
    };

#pragma pack(pop)
}