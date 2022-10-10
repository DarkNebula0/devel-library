#pragma once

#include <type_traits>
#include <functional>
#include <memory>

namespace Devel {
    class CObjectData {
        typedef std::function<void *()> Constructor;
        typedef std::function<std::shared_ptr<void>()> ConstructorShared;
        typedef std::function<void(void *)> Deconstructor;

    public:
        CObjectData() = default;

        CObjectData(const CObjectData &i_oObjectData) {
            this->m_fnClassConstructor = i_oObjectData.m_fnClassConstructor;
            this->m_fnClassConstructorShared = i_oObjectData.m_fnClassConstructorShared;
            this->m_fnClassDeconstructor = i_oObjectData.m_fnClassDeconstructor;

            this->m_nClassSize = i_oObjectData.m_nClassSize;
            this->m_fHasVirtual = i_oObjectData.m_fHasVirtual;
        }

        virtual ~CObjectData() = default;

    public:
        template<typename T>
        static CObjectData get() {
            typedef typename std::remove_pointer<T>::type Type;

            CObjectData oData;

            // Get constructors
            oData.m_fnClassConstructor = []() { return new Type(); };

            // Get move constructor
            oData.m_fnClassConstructorShared = []() {
                return std::static_pointer_cast<void>(std::make_shared<Type>());
            };

            // Get deconstructor
            oData.m_fnClassDeconstructor = [](void *i_pData) { delete reinterpret_cast<Type *>(i_pData); };

            // Get meta data
            oData.m_nClassSize = sizeof(Type);
            oData.m_fHasVirtual = std::has_virtual_destructor<Type>::value;

            return oData;
        }

    public:
        template<typename T = void>
        T *construct() {
            return (this->m_fnClassConstructor ? reinterpret_cast<T *>(this->m_fnClassConstructor()) : nullptr);
        }

        template<typename T = void>
        std::shared_ptr<T> constructShared() {
            return (this->m_fnClassConstructorShared ? std::static_pointer_cast<T>(this->m_fnClassConstructorShared())
                                                     : nullptr);
        }

        template<typename T = void>
        void deconstruct(T *i_tData) {
            if (this->m_fnClassDeconstructor) {
                return this->m_fnClassDeconstructor(i_tData);
            }
        }

    public:
        Constructor constructor() const {
            return this->m_fnClassConstructor;
        }

        ConstructorShared constructorShared() const {
            return this->m_fnClassConstructorShared;
        }

        Deconstructor deconstructor() const {
            return this->m_fnClassDeconstructor;
        }

        size_t size() const {
            return this->m_nClassSize;
        }

        bool hasVirtual() const {
            return this->m_fHasVirtual;
        }

    private:
        Constructor m_fnClassConstructor;
        ConstructorShared m_fnClassConstructorShared;
        Deconstructor m_fnClassDeconstructor;

        size_t m_nClassSize;
        bool m_fHasVirtual;
    };
}