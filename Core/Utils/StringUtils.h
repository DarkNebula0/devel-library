#pragma once

#include <type_traits>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

/// @namespace Devel::StringUtils
/// @brief A namespace encapsulating a set of utility functions for string manipulation.
///
/// These utility functions provide a set of operations for string manipulation such as
/// splitting, joining, replacing, converting case, etc.
///
/// <b>Example</b>
///
/// In this example, we demonstrate the use of the StringUtils namespace.
/// @code{.cpp}
///     std::string str = "Hello, World!";
///
///     // Repeat a string
///     std::string repeatedStr = Devel::StringUtils::Repeat(str, 3); // Returns "Hello, World!Hello, World!Hello, World!"
///
///     // Split a string
///     std::vector<std::string> splitStr = Devel::StringUtils::Split(str, ','); // Returns {"Hello", " World!"}
///
///     // Join a vector of strings
///     std::string joinedStr = Devel::StringUtils::Join(splitStr, ','); // Returns "Hello, World!"
///
///     // Replace character in a string
///     Devel::StringUtils::Replace(joinedStr, '!', '.'); // Modifies joinedStr to "Hello, World."
///
///     // Replace substring in a string
///     std::string replacedStr = Devel::StringUtils::Replace(joinedStr, "World", "There"); // Returns "Hello, There!"
///
///     // Convert string to int
///     int val = Devel::StringUtils::ToInt("123"); // Returns 123
///
///     // Convert string to float
///     float fval = Devel::StringUtils::ToFloat("123.456"); // Returns 123.456
///
///     // Convert string to lower case
///     std::string lowerStr = Devel::StringUtils::ToLowerCopy("HELLO"); // Returns "hello"
///
///     // Convert string to upper case
///     std::string upperStr = Devel::StringUtils::ToUpperCopy("hello"); // Returns "HELLO"
///
///     // Check if string contains a substring
///     bool contains = Devel::StringUtils::Contains(joinedStr, "Hello"); // Returns true
///
///     // Get string size
///     size_t size = Devel::StringUtils::Size(joinedStr.c_str(), 50); // Returns 13 (size of "Hello, World.")
///
///     // Set a string to a destination buffer
///     char buffer[50];
///     Devel::StringUtils::Set(buffer, joinedStr, 50); // Copies "Hello, World." to buffer
///
///     // Get a string from a source buffer
///     std::string bufferStr = Devel::StringUtils::Get(buffer, 50); // Returns "Hello, World."
///
///     // Count the number of a specific character in the string
///     size_t count = Devel::StringUtils::Count(joinedStr.c_str(), joinedStr.length(), 'l'); // Returns 3
///
///     uint8_t byteData = 12; // For example
///
///     std::string hexString = Devel::StringUtils::ToHex(byteData);
///
///     // Output will be "0C"
///     std::cout << hexString << std::endl;
///
///     char arr[] = "Example array";
///     size_t arrSize = sizeof(arr)/sizeof(char);
///
///     std::string str = Devel::StringUtils::FromArray(arr, arrSize);
///
///     // Output will be "Example array"
///     std::cout << str << std::endl;
///
///     std::string str = "Example string";
///     const size_t size = 20;  // define size as needed
///
///     char arr[size] = {};  // initialize the array
///
///     Devel::StringUtils::ToArray(str, arr, size);
///
///     // Output will be "Example string"
///     std::cout << arr << std::endl;
/// @endcode
namespace Devel::StringUtils {
    /// @brief Repeats the input string a specified number of times.
    ///
    /// @param i_sString The string to repeat.
    /// @param i_nTimes The number of times to repeat the string.
    /// @return A new string that is the input string repeated the specified number of times.
    inline std::string Repeat(const std::string &i_sString, size_t i_nTimes) {
        std::string sString = i_sString;

        for (; i_nTimes > 1; i_nTimes--) {
            sString += i_sString;
        }

        return sString;
    }

    /// @brief Splits the input string into substrings based on the specified delimiter.
    ///
    /// @param i_szString The string to split.
    /// @param i_nLength The length of the string to split.
    /// @param i_bDelimeter The delimiter to use for splitting the string.
    /// @param i_nReserve The size to reserve for the resulting vector.
    /// @return A vector of strings split based on the specified delimiter.
    inline std::vector<std::string>
    Split(const char *i_szString, size_t i_nLength, const char i_bDelimeter, const size_t i_nReserve = -1) {
        std::vector<std::string> aSplitted;

        if (*i_szString != 0x00) {
            if (i_nLength == size_t(-1))
                i_nLength = strlen(i_szString);

            aSplitted.reserve((i_nReserve != size_t(-1) ? i_nReserve :
                                std::count(i_szString, i_szString + i_nLength, i_bDelimeter) + 1));

            size_t nLastPos = 0;
            for (size_t i = 0; i < i_nLength; i++) {
                if (i_szString[i] == i_bDelimeter) {
                    aSplitted.emplace_back(i_szString + nLastPos, i - nLastPos);
                    nLastPos = i + 1;
                }
            }
            aSplitted.emplace_back(i_szString + nLastPos, i_nLength - nLastPos);
        }

        return aSplitted;
    }

    /// @brief Splits the input string into substrings based on the specified delimiter.
    ///
    /// @param i_sString The string to split.
    /// @param i_bDelimeter The delimiter to use for splitting the string.
    /// @param i_nReserve The size to reserve for the resulting vector.
    /// @return A vector of strings split based on the specified delimiter.
    inline std::vector<std::string>
    Split(const std::string &i_sString, const char i_bDelimeter, const size_t i_nReserve = -1) {
        return Split(i_sString.c_str(), i_sString.length(), i_bDelimeter, i_nReserve);
    }

    /// @brief Joins the input vector of strings into a single string with the specified delimiter.
    ///
    /// @param i_asString The vector of strings to join.
    /// @param i_sDelimeter The delimiter to use for joining the strings.
    /// @return A string joined from the input vector of strings with the specified delimiter.
    inline std::string Join(const std::vector<std::string> &i_asString, const std::string &i_sDelimeter) {
        std::string sData;

        for (const std::string &sString: i_asString) {
            if (!sData.empty()) {
                sData += i_sDelimeter;
            }

            sData += sString;
        }

        return sData;
    }

    ///
    /// @param i_asString The vector of strings to join.
    /// @param i_bDelimeter The character to use for joining the strings.
    /// @return A string joined from the input vector of strings with the specified delimiter.
    inline std::string Join(const std::vector<std::string> &i_asString, const char i_bDelimeter) {
        return Join(i_asString, std::string(&i_bDelimeter, 1));
    }


    /// @brief Replaces all instances of a specific character in the source string with another character.
    ///
    /// @param i_sSource The source string.
    /// @param i_bFind The character to find.
    /// @param i_bReplaceWith The character to replace with.
    /// @return A reference to the modified source string.
    inline std::string &Replace(std::string &i_sSource, const char i_bFind, const char i_bReplaceWith) {
        const size_t iSize = i_sSource.size();
        for (size_t i = 0; i < iSize; i++) {
            if (i_sSource[i] == i_bFind)
                i_sSource[i] = i_bReplaceWith;
        }

        return i_sSource;
    }

    /// @brief Replaces all instances of a specific substring in the source string with another substring.
    ///
    /// @param i_sSource The source string.
    /// @param i_sFind The substring to find.
    /// @param i_sReplaceWith The substring to replace with.
    /// @return A new string that is the result of the replacement operation.
    inline std::string
    Replace(const std::string &i_sSource, const std::string &i_sFind, const std::string &i_sReplaceWith) {
        std::string sReturn;

        size_t nPos = i_sSource.find(i_sFind);
        size_t nCurrentPos = 0;
        while (nPos != std::string::npos) {
            sReturn += i_sSource.substr(nCurrentPos, nPos);
            sReturn += i_sReplaceWith;

            nCurrentPos = nPos + i_sFind.size();
            nPos = i_sSource.find(i_sSource, nPos);
        }

        if (nCurrentPos != i_sSource.size())
            sReturn += i_sSource.substr(nCurrentPos, i_sSource.size());

        return sReturn;
    }


    /// @brief Converts a string to a 64-bit integer.
    ///
    /// @param i_sBuffer The string to convert.
    /// @return The converted 64-bit integer.
    inline long long ToInt64(const std::string &i_sBuffer) {
        char *pEnd;
        return strtoll(i_sBuffer.c_str(), &pEnd, 10);
    }

    /// @brief Converts a string to an unsigned 64-bit integer.
    ///
    /// @param i_sBuffer The string to convert.
    /// @return The converted unsigned 64-bit integer.
    inline unsigned long long ToUInt64(const std::string &i_sBuffer) {
        return static_cast<unsigned long long>(ToInt64(i_sBuffer));
    }

    /// @brief Converts a string to an integer.
    ///
    /// @param i_sBuffer The string to convert.
    /// @return The converted integer.
    inline int ToInt(const std::string &i_sBuffer) {
        char *pEnd;
        return  static_cast<int>(strtol(i_sBuffer.c_str(), &pEnd, 10));
    }

    /// @brief Converts a string to an unsigned integer.
    ///
    /// @param i_sBuffer The string to convert.
    /// @return The converted unsigned integer.
    inline unsigned int ToUInt(const std::string &i_sBuffer) {
        return static_cast<unsigned int>(ToInt(i_sBuffer));
    }

    /// @brief Converts a string to a float.
    ///
    /// @param i_stBuffer The string to convert.
    /// @return The converted float.
    inline float ToFloat(const std::string &i_stBuffer) {
        char *pEndPtr;
        return std::strtof(i_stBuffer.c_str(), &pEndPtr);
    }

    /// @brief Converts a string to a double.
    ///
    /// @param i_stBuffer The string to convert.
    /// @return The converted double.
    inline double ToDouble(const std::string &i_stBuffer) {
        char *pEndPtr;
        return std::strtod(i_stBuffer.c_str(), &pEndPtr);
    }

    /// @brief Creates a copy of the string and converts it to lower case.
    ///
    /// @param i_sBuffer The string to copy and convert.
    /// @return A copy of the string converted to lower case.
    inline std::string ToLowerCopy(const std::string &i_sBuffer) {
        std::string sToLower = i_sBuffer;
        for (char &c: sToLower) {
            c = static_cast<char>(tolower(c));
        }
        return sToLower;
    }

    /// @brief Converts the string to lower case.
    ///
    /// @param i_sBuffer The string to convert.
    inline void ToLower(std::string &i_sBuffer) {
        for (char &c: i_sBuffer) {
            c = static_cast<char>(tolower(c));
        }
    }


    /// @brief Creates a copy of the string and converts it to upper case.
    ///
    /// @param i_sBuffer The string to copy and convert.
    /// @return A copy of the string converted to upper case.
    inline std::string ToUpperCopy(const std::string &i_sBuffer) {
        std::string sToLower = i_sBuffer;
        for (char &c: sToLower) {
            c = static_cast<char>(toupper(c));
        }
        return sToLower;
    }

    /// @brief Converts the string to upper case.
    ///
    /// @param i_sBuffer The string to convert.
    inline void ToUpper(std::string &i_sBuffer) {
        for (char &c: i_sBuffer) {
            c = static_cast<char>(toupper(c));
        }
    }

    /// @brief Checks if the string contains the substring.
    ///
    /// @param i_sString The string to check.
    /// @param i_sToFind The substring to find.
    /// @param i_fCaseSensetive Whether the search is case sensitive.
    /// @return True if the string contains the substring, false otherwise.
    inline bool
    Contains(const std::string &i_sString, const std::string &i_sToFind, const bool i_fCaseSensetive = true) {
        const size_t nPosition = (i_fCaseSensetive ? i_sString.find(i_sToFind) : ToLowerCopy(i_sString).find(
                ToLowerCopy(i_sToFind)));

        return (nPosition != std::string::npos);
    }

    /// @brief Returns the size of the string, up to a maximum size.
    ///
    /// @param i_szString The string to measure.
    /// @param i_nMaxSize The maximum size.
    /// @return The size of the string.
    inline size_t Size(const char *i_szString, const size_t i_nMaxSize) {
        size_t nSize = 0;

        if (i_szString) {
            for (; nSize < i_nMaxSize && *i_szString++ != 0x00; nSize++) {}
        }

        return nSize;
    }

    /// @brief Copies a string to a destination buffer, up to a maximum size.
    ///
    /// @param i_pDestination The destination buffer.
    /// @param i_szString The string to copy.
    /// @param i_nSize The size of the string.
    /// @param i_nMax The maximum size.
    inline void Set(char *i_pDestination, const char *i_szString, const size_t i_nSize, size_t i_nMax) {
        memset(static_cast<void *>(i_pDestination), 0, i_nMax);

        if (i_nSize <= i_nMax) {
            i_nMax = i_nSize;
        }

        memcpy(static_cast<void *>(i_pDestination), i_szString, i_nMax);
    }

    /// @brief Copies a string to a destination buffer, up to a maximum size.
    ///
    /// @param i_pDestination The destination buffer.
    /// @param i_szString The string to copy.
    /// @param i_nMax The maximum size.
    inline void Set(char *i_pDestination, const char *i_szString, const size_t i_nMax) {
        Set(i_pDestination, i_szString, strlen(i_szString), i_nMax);
    }

    /// @brief Copies a string to a destination buffer, up to a maximum size.
    ///
    /// @param i_pDestination The destination buffer.
    /// @param i_sData The string to copy.
    /// @param i_nMax The maximum size.
    inline void Set(char *i_pDestination, const std::string &i_sData, const size_t i_nMax) {
        Set(i_pDestination, i_sData.c_str(), i_sData.length(), i_nMax);
    }

    /// @brief Returns a string copied from a source buffer, up to a maximum size.
    ///
    /// @param i_pSource The source buffer.
    /// @param i_nMaxSize The maximum size.
    /// @return The copied string.
    inline std::string Get(char *i_pSource, const size_t i_nMaxSize) {
        const size_t nSize = Size(i_pSource, i_nMaxSize);
        return {i_pSource, nSize};
    }

    /// @brief Counts the number of a specific character in the string.
    ///
    /// @param i_szString The string to search.
    /// @param i_nSize The size of the string.
    /// @param i_bDelimeter The character to count.
    /// @return The count of the character in the string.
    inline size_t Count(const char *i_szString, const size_t i_nSize, const char i_bDelimeter) {
        return std::count(i_szString, i_szString + i_nSize, i_bDelimeter);
    }

    /// @brief Counts the number of a specific character in the string.
    ///
    /// @param i_sString The string to search.
    /// @param i_bDelimeter The character to count.
    /// @return The count of the character in the string.
    inline size_t Count(const std::string &i_sString, const char i_bDelimeter) {
        return Count(i_sString.c_str(), i_sString.size(), i_bDelimeter);
    }

    /// @brief Copies a string to a destination array, up to a maximum size.
    ///
    /// @param i_pDestination The destination array.
    /// @param i_szString The string to copy.
    /// @param i_nSize The size of the string.
    template<typename T>
    void ToArray(T &i_pDestination, const char *i_szString, const size_t i_nSize) {
        return Set(i_pDestination, i_szString, i_nSize, sizeof(i_pDestination));
    }

    /// @brief Copies a string to a destination array.
    ///
    /// @param i_pDestination The destination array.
    /// @param i_szString The string to copy.
    template<typename T>
    void ToArray(T &i_pDestination, const char *i_szString) {
        return ToArray(i_pDestination, i_szString, strlen(i_szString));
    }

    /// @brief Copies a string to a destination array.
    ///
    /// @param i_pDestination The destination array.
    /// @param i_szString The string to copy.
    template<typename T>
    void ToArray(T &i_pDestination, const std::string &i_sData) {
        return ToArray(i_pDestination, i_sData.c_str(), i_sData.length());
    }

    /// @brief Returns a string copied from a source array.
    ///
    /// @param i_pSource The source array.
    /// @return The copied string.
    template<typename T>
    std::string FromArray(const T &i_pSource) {
        return Get(const_cast<char *>(i_pSource), sizeof(i_pSource));
    }

    /// @brief Converts a numeric value to a hex string.
    ///
    /// @tparam T A numeric type.
    /// @param i_oValue The numeric value to convert.
    /// @return A string representing the hex value of the input.
    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    inline std::string ToHex(T i_oValue) {
        char achHexString[4 * sizeof(T) + 3];
        sprintf_s(achHexString, sizeof(achHexString), "0x%02x", i_oValue);
        return std::string(achHexString);
    }
}