#pragma once

#include "Serializing/Core/SerializableData.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    template<bool IsHidden = false, typename T = std::string>
    class IString : public IData<T, IsHidden> {
    public:
        [[nodiscard]] SCompareData compareData() const override {
            return {static_cast<const void *>(this->m_tValue.c_str()), this->m_tValue.size()};
        }

    private:
        bool serialize(IO::CWriteStream &i_oStream) const override {
            i_oStream.push<uint>(static_cast<uint>(this->m_tValue.size()));
            i_oStream.push(this->m_tValue, false);
            return true;
        }

    private:
        bool deserialize(IO::CReadStream &i_oStream) override {
            const auto nSize = static_cast<size_t>(i_oStream.get<uint>());
            this->m_tValue = i_oStream.getString(nSize);
            return true;
        }

        bool deserialize(const char *i_szString) override {
            this->m_tValue = i_szString;
            return true;
        }

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