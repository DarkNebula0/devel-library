#include "JsonObject.h"
#include "IO/JsonArray/JsonArray.h"

Devel::IO::CJsonObject::CJsonObject()
        : m_eType(EJsonType::JTObject), m_pArray(nullptr) {}

Devel::IO::CJsonObject::~CJsonObject() {
    this->clear();
}

void Devel::IO::CJsonObject::addObject(const std::string &i_stName, Devel::IO::CJsonObject &&i_oObject) {
    if (!i_stName.empty()) {
        this->m_aoData[i_stName] = std::move(i_oObject);
    }
}

Devel::IO::CJsonObject *Devel::IO::CJsonObject::find(const std::string_view i_stName) {
    Threading::RecursiveLockGuard(this->m_oMutex);
    std::string str(i_stName);
    return this->m_aoData.count(str) ? &this->m_aoData[str] : nullptr;
}


void Devel::IO::CJsonObject::clear() {
    delete this->m_pArray;
    this->m_pArray = nullptr;
    this->m_eType = EJsonType::JTObject;
    this->m_aoData.clear();
    std::string::clear();
}

std::vector<std::string> Devel::IO::CJsonObject::getKeys() {
    std::vector<std::string> astRet;

    Threading::RecursiveLockGuard(this->m_oMutex);
    astRet.reserve(this->m_aoData.size());
    for (auto &it: this->m_aoData) {
        astRet.emplace_back(it.first);
    }

    return astRet;
}

Devel::IO::CJsonArray Devel::IO::CJsonObject::toArray() const {
    if (this->m_pArray) {
        return *this->m_pArray;
    }

    return {};
}

Devel::IO::CJsonObject &Devel::IO::CJsonObject::operator=(const Devel::IO::CJsonObject &i_oOther) {
    this->clear();

    this->m_eType = i_oOther.m_eType;
    this->m_aoData = i_oOther.m_aoData;


    if (i_oOther.m_pArray)
        this->m_pArray = new Devel::IO::CJsonArray(*i_oOther.m_pArray);

    std::string::operator=(i_oOther);
    return *this;
}

Devel::IO::CJsonObject &Devel::IO::CJsonObject::operator=(Devel::IO::CJsonObject &&i_oOther) noexcept {
    this->clear();
    this->m_eType = i_oOther.m_eType;
    this->m_aoData = i_oOther.m_aoData;
    this->m_pArray = i_oOther.m_pArray;
    std::string::operator=(i_oOther);

    i_oOther.m_pArray = nullptr;
    i_oOther.clear();
    return *this;
}

Devel::IO::CJsonObject &Devel::IO::CJsonObject::operator=(const Devel::IO::CJsonArray &i_oOther) {
    this->m_eType = EJsonType::JTArray;

    if (this->m_pArray) {
        this->m_pArray->clear();
    } else {
        this->m_pArray = new Devel::IO::CJsonArray();
    }

    this->m_pArray->operator=(i_oOther);
    return *this;
}