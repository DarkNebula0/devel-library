#pragma once

#include "Core/Global.h"
#include "Core/Utils/StringUtils.h"

namespace Devel {
    /**
     * @brief The CCharArray class
     * @tparam Size Size of the char array
     *
     * The CCharArray class is a type wrapper and a high-level programming interface for char arrays.
     */
    template<size_t Size>
    class CCharArray {
    public:
        /**
         * @brief Default constructor
         *
         * Constructs a new CCharArray object.
         */
        CCharArray()
                : m_szString{0} {}

        /**
         * @brief Explicit constructor
         * @param i_szString The char pointer to copy
         *
         * Constructs a new CCharArray object.
         */
        explicit CCharArray(const char *i_szString) {
            Devel::StringUtils::ToArray(this->m_szString, i_szString);
        }

        /**
        * @brief Explicit constructor
        * @param i_szString The string to copy
        *
        * Constructs a new CCharArray object.
        */
        explicit CCharArray(const std::string &i_sString) {
            Devel::StringUtils::ToArray(this->m_szString, i_sString);
        }

        /**
         * @brief Initializer list constructor
         * @param i_oList initializer list
         *
         * Constructs a new CCharArray object.
         */
        CCharArray(std::initializer_list<char> i_oList) {
            size_t nSize = i_oList.size();

            if (nSize > Size) {
                nSize = Size;
            }

            Devel::StringUtils::ToArray(this->m_szString, i_oList.begin(), nSize);
        }

        /**
         * @brief Copy constructor
         * @param i_szString The char array to copy
         *
         * Constructs a new CCharArray object.
         */
        CCharArray(const CCharArray<Size> &i_szString) {
            this->operator=(i_szString);
        }

        /**
        * @brief Copy constructor
        * @param i_szString The char array to copy
        *
        * Constructs a new CCharArray object.
        */
        template<size_t TOtherSize>
        explicit CCharArray(const CCharArray<TOtherSize> &i_szString) {
            this->operator=(i_szString);
        }

        ~CCharArray() = default;

    public:
        /**
         * @brief Set char array data from string
         * @param i_sString The string to set
         */
        void set(const std::string &i_sString) {
            Devel::StringUtils::ToArray(this->m_szString, i_sString);
        }

        /**
         * @brief Set char array data from char pointer
         * @param i_szString The string to set
         * @param i_nSize The size of the string
         */
        void set(const char *i_szString, size_t i_nSize) {
            Devel::StringUtils::ToArray(this->m_szString, i_szString, i_nSize);
        }

        /**
        * @brief Set char array data from char pointer
        * @param i_szString The string to set
        */
        void set(const char *i_szString) {
            Devel::StringUtils::ToArray(this->m_szString, i_szString);
        }

        /**
        * @brief Set char array data from other CCharArray
        * @param i_szString The CCharArray to set
        */
        void set(const CCharArray<Size> &i_szString) {
            return this->set(i_szString.c_str(), i_szString.length());
        }

        /**
         * @brief Set char array data from other CCharArray
         * @param i_szString The CCharArray to set
         */
        template<size_t SizeOther>
        void set(const CCharArray<SizeOther> &i_szString) {
            return this->set(i_szString.c_str(), i_szString.length());
        }

    public:
        char *begin() {
            return &this->first();
        }

        [[nodiscard]] const char *begin() const {
            return &this->first();
        }

        char *end() {
            return &this->first() + Size;
        }

        [[nodiscard]] const char *end() const {
            return &this->first() + Size;
        }

        [[nodiscard]] const char *c_str() const {
            return this->m_szString;
        }

    public:
        [[nodiscard]] size_t length() const {
            return Devel::StringUtils::Size(this->m_szString, Size);
        }

        static constexpr size_t maxLength() {
            return Size;
        }

    public:

        char &first() {
            return this->m_szString[0];
        }

        [[nodiscard]] const char &first() const {
            return this->m_szString[0];
        }

        char &last() {
            return this->m_szString[Size - 1];
        }

        [[nodiscard]] const char &last() const {
            return this->m_szString[Size - 1];
        }

        char &at(const size_t i_nIndex) {
            return this->m_szString[i_nIndex];
        }

        [[nodiscard]] const char &at(const size_t i_nIndex) const {
            return this->m_szString[i_nIndex];
        }

    public:
        [[nodiscard]] std::string toStdString() const {
            return std::string(this->m_szString, this->length());
        }

    public:
        CCharArray<Size> &operator=(const CCharArray<Size> &i_szString) {
            memcpy(this->m_szString, i_szString.c_str(), Size);
            return *this;
        }

        template<size_t TOherSize>
        CCharArray<Size> &operator=(const CCharArray<TOherSize> &i_szString) {
            this->set<TOherSize>(i_szString);
            return *this;
        }

        CCharArray<Size> &operator=(const std::string &i_sString) {
            this->set(i_sString);
            return *this;
        }

        CCharArray<Size> &operator=(const char *i_szString) {
            this->set(i_szString);
            return *this;
        }

        bool operator==(const CCharArray<Size> &i_szString) const {
            return this->compare(i_szString.c_str(), i_szString.length());
        }

        template<size_t SizeOther>
        bool operator==(const CCharArray<SizeOther> &i_szString) const {
            return this->compare(i_szString.c_str(), i_szString.length());
        }

        bool operator==(const char *i_szString) const {
            return this->compare(i_szString, strlen(i_szString));
        }

        bool operator==(const std::string &i_sString) const {
            return this->compare(i_sString.c_str(), i_sString.length());
        }

        bool operator!=(const CCharArray<Size> &i_szString) const {
            return !this->compare(i_szString.c_str(), i_szString.length());
        }

        template<size_t SizeOther>
        bool operator!=(const CCharArray<SizeOther> &i_szString) const {
            return !this->compare(i_szString.c_str(), i_szString.length());
        }

        bool operator!=(const char *i_szString) const {
            return !this->compare(i_szString, strlen(i_szString));
        }

        bool operator!=(const std::string &i_sString) const {
            return !this->compare(i_sString.c_str(), i_sString.length());
        }

        operator char *() {
            return &this->m_szString[0];
        }

        operator const char *() const {
            return this->m_szString;
        }

    private:
        bool compare(const char *i_szOther, const size_t i_nLength) const {
            const size_t nLength = this->length();
            if (i_nLength != nLength) return false;

            return (memcmp(this->m_szString, i_szOther, nLength) == 0);
        }

    private:
        /**
         * @brief The char array to store the data.
         */
        char m_szString[Size]{};
    };
}