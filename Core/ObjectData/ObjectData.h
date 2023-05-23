#pragma once

#include <type_traits>
#include <functional>
#include <memory>
/// @namespace Devel
/// @brief A namespace for development related classes and functions.
namespace Devel {
    /// @class Devel::CObjectData
    /// @brief A class for representing and handling data of an arbitrary type.
    ///
    /// This class encapsulates generic objects by providing constructors,
    /// destructors, and meta data extraction functionalities for an arbitrary type.
    ///
    /// <b>Example</b>
    ///
    /// This class must be used with the template type being the type you are
    /// working with.
    /// @code{.cpp}
    ///     class CExampleClass {};
    ///
    ///     Devel::CObjectData data = Devel::CObjectData::get<CExampleClass>(); // Creating CObjectData for CExampleClass
    ///
    ///     // Create an instance of CExampleClass using construct function
    ///     CExampleClass* example = data.construct<CExampleClass>();
    ///
    ///     // Create a shared_ptr instance of CExampleClass using constructShared function
    ///     std::shared_ptr<CExampleClass> sharedExample = data.constructShared<CExampleClass>();
    ///
    ///     // Destroy the instance of CExampleClass using deconstruct function
    ///     data.deconstruct<CExampleClass>(example);
    ///
    ///     // You can also get meta data
    ///     size_t classSize = data.size();
    ///     bool hasVirtualDestructor = data.hasVirtual();
    /// @endcode
    class CObjectData {
        /// @typedef Constructor
        /// @brief Type definition for function that constructs an object and returns a raw pointer to it.
        typedef std::function<void *()> Constructor;
        /// @typedef ConstructorShared
        /// @brief Type definition for function that constructs an object and returns a shared pointer to it.
        typedef std::function<std::shared_ptr<void>()> ConstructorShared;
        /// @typedef Deconstructor
        /// @brief Type definition for function that takes a raw pointer and destructs the pointed object.
        typedef std::function<void(void *)> Deconstructor;

    public:
        /// @brief Default constructor.
        CObjectData() = default;

        /// @brief Copy constructor.
        ///
        /// @param i_oObjectData - Object to copy from.
        CObjectData(const CObjectData &i_oObjectData) {
            this->m_fnClassConstructor = i_oObjectData.m_fnClassConstructor;
            this->m_fnClassConstructorShared = i_oObjectData.m_fnClassConstructorShared;
            this->m_fnClassDeconstructor = i_oObjectData.m_fnClassDeconstructor;

            this->m_nClassSize = i_oObjectData.m_nClassSize;
            this->m_fHasVirtual = i_oObjectData.m_fHasVirtual;
        }

        /// @brief Default virtual destructor.
        virtual ~CObjectData() = default;

    public:
        /// @brief Static function for creating CObjectData for a specific type.
        ///
        /// @tparam T - The type for which the CObjectData is to be created.
        /// @return CObjectData instance corresponding to the given type.
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
        /// @brief Constructs an object of a specific type.
        ///
        /// @tparam T - The type of object to construct.
        /// @return A raw pointer to the constructed object.
        template<typename T = void>
        T *construct() {
            return (this->m_fnClassConstructor ? reinterpret_cast<T *>(this->m_fnClassConstructor()) : nullptr);
        }

        /// @brief Constructs an object of a specific type.
        ///
        /// @tparam T - The type of object to construct.
        /// @return A shared pointer to the constructed object.
        template<typename T = void>
        std::shared_ptr<T> constructShared() {
            return (this->m_fnClassConstructorShared ? std::static_pointer_cast<T>(this->m_fnClassConstructorShared())
                                                     : nullptr);
        }

        /// @brief Deconstructs an object of a specific type.
        ///
        /// @tparam T - The type of the object to deconstruct.
        /// @param i_tData - Pointer to the object to deconstruct.
        template<typename T = void>
        void deconstruct(T *i_tData) {
            if (this->m_fnClassDeconstructor) {
                return this->m_fnClassDeconstructor(i_tData);
            }
        }

    public:
        /// @brief Getter for m_fnClassConstructor.
        ///
        /// @return The constructor function of the class.
        [[nodiscard]] Constructor constructor() const {
            return this->m_fnClassConstructor;
        }

        /// @brief Getter for m_fnClassConstructorShared.
        ///
        /// @return The shared constructor function of the class.
        [[nodiscard]] ConstructorShared constructorShared() const {
            return this->m_fnClassConstructorShared;
        }

        /// @brief Getter for m_fnClassDeconstructor.
        ///
        /// @return The deconstructor function of the class.
        [[nodiscard]] Deconstructor deconstructor() const {
            return this->m_fnClassDeconstructor;
        }

        /// @brief Getter for m_nClassSize.
        ///
        /// @return The size of the class.
        [[nodiscard]] size_t size() const {
            return this->m_nClassSize;
        }

        /// @brief Getter for m_fHasVirtual.
        ///
        /// @return Whether the class has virtual functions.
        [[nodiscard]] bool hasVirtual() const {
            return this->m_fHasVirtual;
        }

    private:
        /// @var Constructor m_fnClassConstructor
        /// @brief The constructor function of the class.
        Constructor m_fnClassConstructor;
        /// @var ConstructorShared m_fnClassConstructorShared
        /// @brief The shared constructor function of the class.
        ConstructorShared m_fnClassConstructorShared;
        /// @var Deconstructor m_fnClassDeconstructor
        /// @brief The deconstructor function of the class.
        Deconstructor m_fnClassDeconstructor;
        /// @var size_t m_nClassSize
        /// @brief The size of the class.
        size_t m_nClassSize{};
        /// @var bool m_fHasVirtual
        /// @brief Whether the class has virtual functions.
        bool m_fHasVirtual{};
    };
}