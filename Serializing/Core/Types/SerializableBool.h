#pragma once

#include "Serializing/SerializingDefines.h"
#include "Serializing/Core/SerializableData.h"
#include "Core/Utils/StringUtils.h"

namespace Devel::Serializing {
#pragma pack(push, 1)

    template<bool IsHidden = false, typename T = bool>
    class IBool : public IData<T, IsHidden> {
    private:
        bool serialize(IO::CWriteStream &i_oStream) const override {
            i_oStream.push(this->m_tValue);
            return true;
        }

    private:
        bool deserialize(IO::CReadStream &i_oStream) override {
            this->m_tValue = i_oStream.get<T>();
            return true;
        }

        bool deserialize(const char *i_szString) override {
            this->m_tValue = (StringUtils::ToInt64(i_szString) > 0);
            return true;
        }

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