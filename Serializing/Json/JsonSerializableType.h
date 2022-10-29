#pragma once

#include "Core/Global.h"
#include "Core/Exceptions.h"
#include "Serializing/Json/JsonFieldName.h"
#include "Serializing/SerializingDefines.h"
#include "Serializing/Core/SerializableData.h"
#include "IO/JsonObject/JsonObject.h"


namespace Devel::Serializing {
    static auto InvalidObjectName = std::runtime_error("Object invalid or empty name!");
    static auto InvalidData = std::runtime_error("Object does not matches the struct!");
    static auto DifferentTypesException = std::runtime_error("Different types!");
    static auto InvalidTypeException = std::runtime_error("Invalid type!");

#pragma pack(push, 1)

    template<typename T = int, typename TData = IData<T>>
    class IJsonType : public TData {
    protected:
        explicit IJsonType(const CJsonFieldName i_oFieldName) : m_oFieldName(i_oFieldName), m_bIsNull(false) {}
        virtual ~IJsonType() = default;

    private:
        CJsonFieldName m_oFieldName;
        IBool<true> m_bIsNull;
    protected:
        virtual bool onDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) {
            return true;
        };

        virtual bool onSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const {
            return true;
        }

        virtual bool onDeserialize(IO::CJsonObject &i_oObject) {
            return this->onDeserialize(i_oObject, false);
        }

        virtual bool onSerialize(IO::CJsonObject &i_oObject) const {
            return this->onSerialize(i_oObject, false);
        }

    protected:
        bool serialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) const {
            if (checkSerializeObject(i_oObject, i_bIsStrict)) {
                return true;
            }

            if (std::is_arithmetic_v<T>) {
                i_oObject.get(this->name()) = static_cast<T>(this->m_tValue);
            } else {
                i_oObject.get(this->name()) = this->m_tValue;
            }
            return true;
        }

        [[nodiscard]] std::string_view name() const {
            return this->m_oFieldName.name();
        }

        [[nodiscard]] bool isNull() const {
            return this->m_bIsNull;
        }

        void setNull(bool i_bState) {
            this->m_bIsNull = i_bState;
        }

        IO::CJsonObject *getObject(IO::CJsonObject &i_oObject, const bool i_bIsStrict) {
            IO::CJsonObject *pObject = (i_oObject.type() != IO::EJsonType::JTArray)
                    ? i_oObject.find(this->name())
                    : ((this->name().empty()) ? &i_oObject
                    : i_oObject.find(this->name())
                    );

            if (!pObject) {
                if (i_bIsStrict) {
                    throw InvalidData;
                }
                IJsonType::setNull(true);
            } else if (pObject->type() == IO::EJsonType::JTNull) {
                IJsonType::setNull(true);
                pObject = nullptr;
            }
            return pObject;
        }

        bool checkSerializeObject(IO::CJsonObject &i_oObject, const bool i_bIsStrict) const {
            if (!i_bIsStrict && this->isNull()) {
                return true;
            }

            if (this->name().empty()) {
                throw InvalidObjectName;
            }

            if (this->isNull()) {
                i_oObject.get(this->name()).setNull();
            }

            return false;
        }

    public:
        bool doDeserialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) {
            return this->onDeserialize(i_oObject, i_bIsStrict);
        }

        bool doSerialize(IO::CJsonObject &i_oObject, const bool i_bIsStrict = false) const {
            return this->onSerialize(i_oObject, i_bIsStrict);
        }

    public:
        [[nodiscard]] size_t size() const override {
            return sizeof(*this);
        }

    public:
        using TData::TData;

        template <typename TJsonFieldName,
                std::enable_if_t<std::is_same_v<CJsonFieldName, TJsonFieldName>, bool> = true
        >
        IJsonType &operator=(const TJsonFieldName &i_tValue) {
            this->m_oFieldName = i_tValue;
            return *this;
        }

        template <typename TJsonFieldName,
                std::enable_if_t<std::is_same_v<CJsonFieldName, TJsonFieldName>, bool> = true
        >
        IJsonType &operator=(TJsonFieldName &&i_tValue) {
            this->m_oFieldName = std::move(i_tValue);
            return *this;
        };
    };

#pragma pack(pop)

    template<typename TField, typename TStruct>
    TField *GetJsonFieldByName(TStruct &i_oStruct, const std::string_view i_sName) {
        TField *pField = nullptr;
        IterateSerializableStruct<TField>(&i_oStruct, [&](TField *i_pData) {
            if (i_pData->name() == i_sName) {
                pField = i_pData;
                return false;
            }

            return true;
        });

        return pField;
    }

    std::false_type is_json_type_class_impl(...);
    template<typename T = int, typename TData = IData<T>>
    std::true_type is_json_type_class_impl(IJsonType<T, TData>*);

    template <typename T>
    using is_json_type_class = decltype(is_json_type_class_impl(std::declval<T*>()));
}