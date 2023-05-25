#pragma once

#include <type_traits>

/// @def SerializableGetField(Type, Struct, Index)
/// @brief Retrieves a field of a structure by casting its memory location to the specified type.
///
/// This macro allows retrieving a field of a structure by casting the memory location of the structure plus the specified index to the desired type.
/// The macro returns a pointer to the field.
///
/// @param Type The type of the field.
/// @param Struct The structure containing the field.
/// @param Index The index of the field within the structure.
/// @return A pointer to the field.
#define SerializableGetField(Type, Struct, Index)        reinterpret_cast<Type *>(reinterpret_cast<char *>(Struct) + Index)

/// @def MakeAssignmentOperatorsPrivate(Type)
/// @brief Makes the assignment operators of a class private.
///
/// This macro generates private assignment operators for the specified class.
/// It is commonly used to disable assignment to certain members of a class.
///
/// @param Type The class type.
#define MakeAssignmentOperatorsPrivate(Type)                \
        auto &operator=(const Type &i_tValue)        \
        {                                                   \
            this->m_tValue = i_tValue;                      \
            return *this;                                   \
        }                                                   \
                                                            \
        auto &operator=(Type &&i_tValue)             \
        {                                                   \
            this->m_tValue = i_tValue;                      \
            return *this;                                   \
        }

/// @def CreateSerializeOperators(T, IsHidden)
/// @brief Creates serialization operators for a class.
///
/// This macro generates serialization operators for the specified class, using the IData interface provided by the Devel::Serializing namespace.
/// It also makes the assignment operators private to prevent assignment to the class objects.
///
/// @param T The class type.
/// @param IsHidden A boolean value indicating whether the serialized data is hidden.
#define CreateSerializeOperators(T, IsHidden)                   \
        using Devel::Serializing::IData<T, IsHidden>::IData;   \
        MakeAssignmentOperatorsPrivate(T);

/// @def CreateSerializeOperatorsCustomDerive(T)
/// @brief Creates serialization operators for a class derived from a custom base class.
///
/// This macro generates serialization operators for the specified class, which is derived from a custom base class.
/// It makes the assignment operators private to prevent assignment to the class objects.
///
/// @param T The class type.
#define CreateSerializeOperatorsCustomDerive(T)    \
        MakeAssignmentOperatorsPrivate(T);

/// @def SerializerEnableIfNotArithmetic(TReturn)
/// @brief A template enable_if condition for serialization.
///
/// This macro defines a template enable_if condition that checks if the specified type is not arithmetic.
/// It is typically used in serialization code to conditionally enable serialization functions based on type traits.
///
/// @param TReturn The return type of the serialization function.
#define SerializerEnableIfNotArithmetic(TReturn)    template<typename T1 = T> std::enable_if_t<!std::is_arithmetic_v<T1>, TReturn>

#pragma region Template String
/// @def JsonFieldName(name)
/// @brief Creates a CJsonFieldName object with the specified field name.
///
/// This macro creates a CJsonFieldName object using the specified field name.
/// The CJsonFieldName object is commonly used in JSON serialization to represent a named field.
///
/// @param name The name of the field.
/// @return A CJsonFieldName object representing the field name.
#define JsonFieldName(name) (Devel::Serializing::CJsonFieldName(name))
#pragma endregion