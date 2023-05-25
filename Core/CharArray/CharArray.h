#pragma once

#include "Core/Global.h"
#include "Core/Utils/StringUtils.h"
/// @namespace Devel
/// @brief A namespace for development related classes and functions.
namespace Devel {
    /// @class Devel::CCharArray
    /// @brief A class for representing and manipulating a character array.
    ///
    /// This class encapsulates character arrays by providing constructors,
    /// assignment operators, and string manipulation functionalities.
    ///
    /// <b>Example</b>
    ///
    /// This class must be used with the template type being the size of the array you are
    /// working with.
    /// @code{.cpp}
    ///     Devel::CCharArray<50> arr; // Creating an instance of CCharArray with a size of 50
    ///
    ///     // Setting data from a C-style string
    ///     arr.set("Hello, world!");
    ///
    ///     // Setting data from a std::string
    ///     std::string str = "Hello, world!";
    ///     arr.set(str);
    ///
    ///     // Setting data from another CCharArray
    ///     Devel::CCharArray<50> arr2 = arr;
    ///
    ///     // Getting the C-style string representation of the array
    ///     const char* cStr = arr.c_str();
    ///
    ///     // Getting the std::string representation of the array
    ///     std::string stdStr = arr.toStdString();
    ///
    ///     // Comparing CCharArray with another CCharArray, a C-style string, and a std::string
    ///     bool isEqual = (arr == arr2) && (arr == cStr) && (arr == stdStr);
    /// @endcode
    template<size_t Size>
    class CCharArray {
    public:
        ///  Default constructor
        CCharArray()
                : m_szString{0} {}

        /// @brief Explicit constructor
        /// @param i_szString The char pointer to copy
        explicit CCharArray(const char *i_szString) {
            Devel::StringUtils::ToArray(this->m_szString, i_szString);
        }

        /// @brief Explicit constructor
        /// @param i_sString The string to copy
        explicit CCharArray(const std::string &i_sString) {
            Devel::StringUtils::ToArray(this->m_szString, i_sString);
        }

        /// @brief Initializer list constructor
        /// @param i_oList initializer list
        CCharArray(std::initializer_list<char> i_oList) {
            size_t nSize = i_oList.size();

            if (nSize > Size) {
                nSize = Size;
            }

            Devel::StringUtils::ToArray(this->m_szString, i_oList.begin(), nSize);
        }

        /// @brief Copy constructor
        /// @param i_szString The char array to copy
        CCharArray(const CCharArray<Size> &i_szString) {
            this->operator=(i_szString);
        }

        /// @brief Copy constructor
        /// @param i_szString The char array to copy
        template<size_t TOtherSize>
        explicit CCharArray(const CCharArray<TOtherSize> &i_szString) {
            this->operator=(i_szString);
        }

        /// @brief Default destructor.
        ~CCharArray() = default;

    public:
        /// @brief Set char array data from string
        /// @param i_sString The string to set
        void set(const std::string &i_sString) {
            Devel::StringUtils::ToArray(this->m_szString, i_sString);
        }

        /// @brief Set char array data from char pointer
        /// @param i_szString The string to set
        /// @param i_nSize The size of the string
        void set(const char *i_szString, size_t i_nSize) {
            Devel::StringUtils::ToArray(this->m_szString, i_szString, i_nSize);
        }

        /// @brief Set char array data from char pointer
        /// @param i_szString The string to set
        void set(const char *i_szString) {
            Devel::StringUtils::ToArray(this->m_szString, i_szString);
        }

        /// @brief Set char array data from other CCharArray
        /// @param i_szString The CCharArray to set
        void set(const CCharArray<Size> &i_szString) {
            return this->set(i_szString.c_str(), i_szString.length());
        }

        /// @brief Set char array data from other CCharArray
        /// @param i_szString The CCharArray to set
        template<size_t SizeOther>
        void set(const CCharArray<SizeOther> &i_szString) {
            return this->set(i_szString.c_str(), i_szString.length());
        }

    public:
        /// @return A pointer to the beginning of the char array
        char *begin() {
            return &this->first();
        }

        /// @return A pointer to the beginning of the const char array
        [[nodiscard]] const char *begin() const {
            return &this->first();
        }

        /// @return A pointer to the end of the char array
        char *end() {
            return &this->first() + Size;
        }

        /// @return A pointer to the end of the const char array
        [[nodiscard]] const char *end() const {
            return &this->first() + Size;
        }

        /// @return A const char pointer representing the char array
        [[nodiscard]] const char *c_str() const {
            return this->m_szString;
        }

    public:
        /// @return The length of the char array
        [[nodiscard]] size_t length() const {
            return Devel::StringUtils::Size(this->m_szString, Size);
        }

        /// @return The maximum length of the char array
        static constexpr size_t maxLength() {
            return Size;
        }

    public:
        /// @return The first character of the char array
        char &first() {
            return this->m_szString[0];
        }

        /// @return The first character of the const char array
        [[nodiscard]] const char &first() const {
            return this->m_szString[0];
        }

        /// @return The last character of the char array
        char &last() {
            return this->m_szString[Size - 1];
        }

        /// @return The last character of the const char array
        [[nodiscard]] const char &last() const {
            return this->m_szString[Size - 1];
        }

        /// @return The character at the given index of the char array
        char &at(const size_t i_nIndex) {
            return this->m_szString[i_nIndex];
        }

        /// @return The character at the given index of the const char array
        [[nodiscard]] const char &at(const size_t i_nIndex) const {
            return this->m_szString[i_nIndex];
        }

    public:
        /// @return The CCharArray as a standard string
        [[nodiscard]] std::string toStdString() const {
            return std::string(this->m_szString, this->length());
        }

    public:
        /// @brief Assigns the contents of another CCharArray to this object
        /// @param i_szString The CCharArray to copy
        /// @return This CCharArray object
        CCharArray<Size> &operator=(const CCharArray<Size> &i_szString) {
            memcpy(this->m_szString, i_szString.c_str(), Size);
            return *this;
        }

        /// @brief Assigns the contents of another CCharArray to this object
        /// @param i_szString The CCharArray to copy
        /// @return This CCharArray object
        template<size_t TOtherSize>
        CCharArray<Size> &operator=(const CCharArray<TOtherSize> &i_szString) {
            this->set<TOtherSize>(i_szString);
            return *this;
        }

        /// @brief Assigns the contents of a standard string to this object
        /// @param i_sString The string to copy
        /// @return This CCharArray object
        CCharArray<Size> &operator=(const std::string &i_sString) {
            this->set(i_sString);
            return *this;
        }

        /// @brief Assigns the contents of a char array to this object
        /// @param i_szString The char array to copy
        /// @return This CCharArray object
        CCharArray<Size> &operator=(const char *i_szString) {
            this->set(i_szString);
            return *this;
        }

        /// @brief Compare CCharArray object with another for equality
        /// @param i_szString The CCharArray to compare
        /// @return True if equal, False otherwise
        bool operator==(const CCharArray<Size> &i_szString) const {
            return this->compare(i_szString.c_str(), i_szString.length());
        }

        /// @brief Compare CCharArray object with another for equality
        /// @param i_szString The CCharArray to compare
        /// @return True if equal, False otherwise
        template<size_t SizeOther>
        bool operator==(const CCharArray<SizeOther> &i_szString) const {
            return this->compare(i_szString.c_str(), i_szString.length());
        }

        /// @brief Compare CCharArray object with a char array for equality
        /// @param i_szString The char array to compare
        /// @return True if equal, False otherwise
        bool operator==(const char *i_szString) const {
            return this->compare(i_szString, strlen(i_szString));
        }

        /// @brief Compare CCharArray object with a standard string for equality
        /// @param i_sString The string to compare
        /// @return True if equal, False otherwise
        bool operator==(const std::string &i_sString) const {
            return this->compare(i_sString.c_str(), i_sString.length());
        }

        /// @brief Compare CCharArray object with another for inequality
        /// @param i_szString The CCharArray to compare
        /// @return True if not equal, False otherwise
        bool operator!=(const CCharArray<Size> &i_szString) const {
            return !this->compare(i_szString.c_str(), i_szString.length());
        }

        /// @brief Compare CCharArray object with another for inequality
        /// @param i_szString The CCharArray to compare
        /// @return True if not equal, False otherwise
        template<size_t SizeOther>
        bool operator!=(const CCharArray<SizeOther> &i_szString) const {
            return !this->compare(i_szString.c_str(), i_szString.length());
        }

        /// @brief Compare CCharArray object with a char array for inequality
        /// @param i_szString The char array to compare
        /// @return True if not equal, False otherwise
        bool operator!=(const char *i_szString) const {
            return !this->compare(i_szString, strlen(i_szString));
        }

        /// @brief Compare CCharArray object with a standard string for inequality
        /// @param i_sString The string to compare
        /// @return True if not equal, False otherwise
        bool operator!=(const std::string &i_sString) const {
            return !this->compare(i_sString.c_str(), i_sString.length());
        }

        /// @brief Implicit conversion to a char array
        operator char *() {
            return &this->m_szString[0];
        }

        /// @brief Implicit conversion to a const char array
        operator const char *() const {
            return this->m_szString;
        }

    private:
        /// Compare CCharArray object with a char array of specific length for equality
        /// @param i_szOther The char array to compare
        /// @param i_nLength The length of the char array
        /// @return True if equal, False otherwise
        bool compare(const char *i_szOther, const size_t i_nLength) const {
            const size_t nLength = this->length();
            if (i_nLength != nLength) return false;

            return (memcmp(this->m_szString, i_szOther, nLength) == 0);
        }

    private:
        /// @var char m_szString[Size]
        /// @brief The char array to store the data.
        char m_szString[Size]{};
    };
}