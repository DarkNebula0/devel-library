#pragma once

#include "Threading/MutexVector/MutexVector.h"
#include "IO/JsonObject/JsonObject.h"

namespace Devel::IO {
    class CJsonArray : public Threading::CMutexVector<CJsonObject> {
    public:
        CJsonArray() = default;

        explicit CJsonArray(std::vector<CJsonObject> &i_oOther) {
            Threading::CMutexVector<CJsonObject>::operator=(i_oOther);
        }

        explicit CJsonArray(Threading::CMutexVector<CJsonObject> &i_oOther) {
            Threading::CMutexVector<CJsonObject>::operator=(i_oOther);
        }

        CJsonArray(const CJsonArray &i_oOther) : CMutexVector(i_oOther) { this->operator=(i_oOther); }

        CJsonArray(CJsonArray &&i_oOther) noexcept { this->operator=(std::move(i_oOther)); }

        ~CJsonArray() override = default;

    public:
        void allocate(const size_t i_nSize) { Threading::CMutexVector<CJsonObject>::reserve(i_nSize); }

    public:
        inline const Threading::CMutexVector<CJsonObject>
        &

        data() const { return *this; }

    public:
        inline CJsonArray
        &

        operator=(const CJsonArray &i_oOther) {
            Threading::CMutexVector<CJsonObject>::operator=(i_oOther);
            return *this;
        }

        inline CJsonArray
        &

        operator=(CJsonArray &&i_oOther) noexcept {
            Threading::CMutexVector<CJsonObject>::operator=(std::move(i_oOther));
            return *this;
        }
    };
}