#pragma once

#include <string_view>
#include <type_traits>

namespace Devel::Serializing {
    class CJsonFieldName
    {
    public:
        explicit CJsonFieldName(const char *i_pName) : m_pName(i_pName) {}
        explicit CJsonFieldName(const std::string_view i_stName) : m_pName(i_stName.data()) {}
        CJsonFieldName(const CJsonFieldName &i_oOther) = default;
        CJsonFieldName(CJsonFieldName &&i_oOther) noexcept : m_pName(i_oOther.m_pName) {}
        ~CJsonFieldName() = default;

        CJsonFieldName &operator=(const CJsonFieldName &i_oOther) { m_pName = i_oOther.m_pName; return *this; }
        CJsonFieldName &operator=(CJsonFieldName &&i_oOther) { m_pName = i_oOther.m_pName; return *this; }

        [[nodiscard]] const char *name() const { return m_pName; }
    private:
        const char *m_pName;
    };
}