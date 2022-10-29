#pragma once

#include "Serializing/Core/SerializableData.h"

namespace Devel::Serializing {
    static auto FalseException = std::logic_error("Serialize-Function returned false!");
    static auto TooLessDataInPacketException = std::range_error(
            "Not enough data in Packet available for deserialize into Struct!");

    template<typename T>
    bool SerializeStream(const T &i_oStruct, IO::CWriteStream &i_oStream) {
        return IterateSerializableStruct<IData<>>(&i_oStruct, [&](const IData<> *i_pData) {
            if (!i_pData->doSerialize(i_oStream)) {
                return false;
            }

            return true;
        });
    }

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