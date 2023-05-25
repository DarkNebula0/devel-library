#pragma once

#include "Serializing/Core/SerializableData.h"

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
    /// @brief The exception thrown when the serialize function returns false.
    static auto FalseException = std::logic_error("Serialize-Function returned false!");
    /// Exception thrown when there is not enough data in the packet to deserialize into the struct.
    static auto TooLessDataInPacketException = std::range_error(
            "Not enough data in Packet available for deserialize into Struct!");

    /// @brief Serializes a struct to a write stream.
    /// @tparam T The type of the struct.
    /// @param i_oStruct The struct object to serialize.
    /// @param i_oStream The write stream to serialize to.
    /// @return `true` if serialization was successful, `false` otherwise.
    template<typename T>
    bool SerializeStream(const T &i_oStruct, IO::CWriteStream &i_oStream) {
        return IterateSerializableStruct<IData<>>(&i_oStruct, [&](const IData<> *i_pData) {
            if (!i_pData->doSerialize(i_oStream)) {
                return false;
            }

            return true;
        });
    }

    /// @brief Deserializes a struct from a read stream.
    /// @tparam T The type of the struct.
    /// @param i_oStruct The struct object to deserialize into.
    /// @param i_oStream The read stream to deserialize from.
    /// @param i_nStructSize The size of the struct in bytes.
    /// @return `true` if deserialization was successful, `false` otherwise.
    /// @throws TooLessDataInPacketException If there is not enough data in the packet to deserialize into the struct.
    /// @throws IO::NoBufferException If the read stream has no buffer.
    template<typename T>
    bool DeserializeStream(T &i_oStruct, IO::CReadStream &i_oStream, size_t i_nStructSize = sizeof(T)) {
        if (i_oStream.buffer()) {
            return IterateDeserializableStruct<IData<>>(&i_oStruct, [&](IData<> *i_pData) {
                if (!i_pData->isHidden()) {
                    if (i_oStream.isEoB()) {
                        throw TooLessDataInPacketException;
                    }

                    if (!i_pData->doDeserialize(i_oStream)) {
                        return false;
                    }
                }

                return true;
            }, i_nStructSize);
        }

        throw IO::NoBufferException;
    }
}