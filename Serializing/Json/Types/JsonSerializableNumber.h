#pragma once

#include "Serializing/Core/Types/SerializableArithmetic.h"
#include "Serializing/Json/JsonSerializableType.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    template<typename T>
    class IJsonNumber : public IJsonType<T, IArithmetic<T>> {
    public:
        IJsonNumber(const CJsonFieldName i_oFieldName) : IJsonType<T, IArithmetic<T>>(i_oFieldName) {}

    private:
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

        bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) override {
            return this->serialize(i_oObject, i_bIsStrict);
        }

        bool onDeserialize(IO::CJsonObject &i_oObject) final {
            return this->onDeserialize(i_oObject, false);
        }

        bool onSerialize(IO::CJsonObject &i_oObject) final {
            return this->onSerialize(i_oObject, false);
        }

    public:
        using IJsonType<T, IArithmetic<T>>::IJsonType;

        auto &operator=(const T &i_tValue) {
            this->m_tValue = i_tValue;
            this->setNull(false);
            return *this;
        }

        auto &operator=(T &&i_tValue) {
            this->m_tValue = i_tValue;
            this->setNull(false);
            return *this;
        }
    };

    typedef IJsonNumber<char> IJsonChar;
    typedef IJsonNumber<byte> IJsonByte;
    typedef IJsonNumber<short> IJsonShort;
    typedef IJsonNumber<ushort> IJsonUShort;
    typedef IJsonNumber<int> IJsonInt;
    typedef IJsonNumber<uint> IJsonUInt;
    typedef IJsonNumber<int64> IJsonInt64;
    typedef IJsonNumber<uint64> IJsonUInt64;
    typedef IJsonNumber<float> IJsonFloat;
    typedef IJsonNumber<double> IJsonDouble;

#pragma pack(pop)
}