#pragma once

#include "Core/Global.h"
#include "Core/Utils/StringUtils.h"
#include "Core/Typedef.h"
#include "Threading/LockGuard/LockGuard.h"

#include <string_view>
#include <string>
#include <map>

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    /// @enum EJsonType
    /// @brief Enumerates the possible types of JSON value.
    enum class EJsonType {
        JTObject,   ///< An object type (an unordered set of name/value pairs).
        JTNumber,   ///< A number type.
        JTBoolean,  ///< A boolean type.
        JTString,   ///< A string type.
        JTArray,    ///< An array type (an ordered collection of values).
        JTNull,     ///< A null type.
    };

    // Forward declaration of CJsonArray.
    class CJsonArray;

    /// @class Devel::IO::CJsonObject
    /// @brief A class that encapsulates a JSON object.
    ///
    /// This class represents a JSON object and provides methods for accessing
    /// and manipulating its data.
    ///
    /// <b>Example</b>
    /// @code{.cpp}
    ///     // Creating a new JSON object
    ///     Devel::IO::CJsonObject jsonObject;
    ///
    ///     // Setting a string value
    ///     jsonObject["name"] = "John Doe";
    ///
    ///     // Setting a number value
    ///     jsonObject["age"] = 30;
    ///
    ///     // Accessing values
    ///     std::string name = jsonObject["name"].toString();
    ///     int age = jsonObject["age"].toInt();
    /// @endcode
    class CJsonObject : public std::string {
        friend class CJsonDocument; ///< Allows CJsonDocument to access private members of CJsonObject.

    public:
        /// @brief Default constructor.
        CJsonObject();

        /// @brief Copy constructor.
        /// @param i_oOther - The CJsonObject instance to copy.
        CJsonObject(const CJsonObject &i_oOther) : CJsonObject() {
            this->operator=(i_oOther);
        }

        /// @brief Move constructor.
        /// @param i_oOther - The CJsonObject instance to move.
        CJsonObject(CJsonObject &&i_oOther) noexcept: CJsonObject() {
            this->operator=(std::move((i_oOther)));
        }

        /// @brief Virtual destructor.
        virtual ~CJsonObject();

    private:
        /// @var EJsonType m_eType
        /// @brief The type of JSON value this object represents.
        EJsonType m_eType;
    private:
        /// @var Threading::CMutex m_oMutex
        /// @brief The mutex used for thread synchronization.
        Threading::CMutex m_oMutex;
        /// @var CJsonArray *m_pArray
        /// @brief A pointer to the JSON array, if this object represents an array type.
        CJsonArray *m_pArray;
    private:
        /// @var std::map<std::string, CJsonObject> m_aoData
        /// @brief The map containing the data of the JSON object, if this object represents an object type.
        std::map<std::string, CJsonObject> m_aoData;
    private:
        /// @brief Adds an object to the map.
        /// @param i_stName - The name of the value to add.
        /// @param i_oObject - The object to add.
        void addObject(const std::string &i_stName, CJsonObject &&i_oObject);

        /// @brief Sets the type of JSON value this object represents.
        /// @param i_eType - The type to set
        void setType(const EJsonType i_eType) { this->m_eType = i_eType; }

        /// @brief Clears all data from the object.
        void clear();

    public:
        /// @brief Finds a value in the JSON object.
        /// @param i_stName - The name of the value to find.
        /// @return A pointer to the value, if found. Otherwise, returns nullptr.
        CJsonObject *find(std::string_view i_stName);

        /// @brief Returns the keys of the JSON object.
        /// @return A vector of keys (strings) of the JSON object.
        std::vector<std::string> getKeys();

        /// @brief Converts the JSON object to a JSON array.
        /// @return A CJsonArray object.
        CJsonArray toArray() const;

    public:
        /// @brief Returns a reference to the mutex.
        /// @return A reference to the mutex.
        inline Threading::CMutex &mutex() {
            return this->m_oMutex;
        }

        /// @brief Returns the type of the JSON object.
        /// @return The type of the JSON object.
        inline EJsonType type() const { return this->m_eType; }

        /// @brief Gets the value associated with the specified name.
        /// @param i_stName The name of the value to get.
        /// @return The value associated with the specified name.
        inline CJsonObject &get(const std::string_view i_stName) { return this->operator[](i_stName); }

    public:
        /// @brief Sets the type of the JSON object to null.
        inline void setNull() { this->m_eType = EJsonType::JTNull; }

    public:
        /// @brief Converts the JSON object to a 64-bit unsigned integer.
        /// @return The JSON object as a 64-bit unsigned integer.
        inline uint64 toUInt64() const { return StringUtils::ToUInt64(*this); }

        /// @brief Converts the JSON object to a 64-bit signed integer.
        /// @return The JSON object as a 64-bit signed integer.
        inline int64 toInt64() const { return StringUtils::ToInt64(*this); }

        /// @brief Converts the JSON object to an integer.
        /// @return The JSON object as an integer.
        inline int toInt() const { return StringUtils::ToInt(*this); }

        /// @brief Converts the JSON object to an unsigned integer.
        /// @return The JSON object as an unsigned integer.
        inline uint toUInt() const { return StringUtils::ToInt(*this); }

        /// @brief Converts the JSON object to a float.
        /// @return The JSON object as a float.
        inline float toFloat() const { return StringUtils::ToFloat(*this); }

        /// @brief Converts the JSON object to a double.
        /// @return The JSON object as a double.
        inline double toDouble() const { return StringUtils::ToDouble(*this); }

        /// @brief Converts the JSON object to a boolean.
        /// @return The JSON object as a boolean.
        inline bool toBool() const { return (*this == "t" || *this == "1"); }

        /// @brief Checks if the JSON object is null.
        /// @return True if the JSON object is null; otherwise, false.
        inline bool isNull() const { return this->m_eType == EJsonType::JTNull; }

    public:
        /// @brief Assignment operator overloads for various data types including CJsonObject, CJsonArray, char, string, uint64, uint, int64, float, double, int, and bool.
        CJsonObject &operator=(const CJsonObject &i_oOther);

        CJsonObject &operator=(CJsonObject &&i_oOther) noexcept;

        CJsonObject &operator=(const CJsonArray &i_oOther);

        inline CJsonObject &operator=(const char *i_stValue) {
            return this->operator=(std::string(i_stValue));
        }

        inline CJsonObject &operator=(const std::string &i_stValue) {
            this->m_eType = EJsonType::JTString;
            std::string::operator=(i_stValue);
            return *this;
        }

        inline CJsonObject &operator=(const uint64 i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject &operator=(const uint i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject &operator=(const int64 i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject &operator=(const float i_fValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_fValue));
            return *this;
        }

        inline CJsonObject &operator=(const double i_dValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_dValue));
            return *this;
        }

        inline CJsonObject &operator=(const int i_nValue) {
            this->m_eType = EJsonType::JTNumber;
            std::string::operator=(std::to_string(i_nValue));
            return *this;
        }

        inline CJsonObject &operator=(const bool i_bState) {
            this->operator=((i_bState ? "t" : "f"));
            this->m_eType = EJsonType::JTBoolean;
            return *this;
        }

        /// @brief Subscript operator overload for string key.
        /// @param i_stKey The key to access.
        /// @return The value associated with the specified key.
        inline CJsonObject &operator[](const std::string_view i_stKey) {
            Threading::RecursiveLockGuard(this->m_oMutex);
            return this->m_aoData.operator[](std::string(i_stKey));
        }
    };
}