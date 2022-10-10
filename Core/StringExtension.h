#pragma once

#include <type_traits>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

namespace Devel {
    namespace String {
        inline std::string Repeat(const std::string &i_sString, size_t i_nTimes) {
            std::string sString = i_sString;

            for (; i_nTimes > 1; i_nTimes--) {
                sString += i_sString;
            }

            return sString;
        }


        // When you don't pass a length(means -1), the string has to be zero terminated!
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

        inline std::vector<std::string>
        Split(const std::string &i_sString, const char i_bDelimeter, const size_t i_nReserve = -1) {
            return Split(i_sString.c_str(), i_sString.length(), i_bDelimeter, i_nReserve);
        }


        inline std::string Join(const std::vector<std::string> &i_asString, const std::string &i_sDelimeter) {
            std::string sData = "";

            for (const std::string &sString: i_asString) {
                if (!sData.empty()) {
                    sData += i_sDelimeter;
                }

                sData += sString;
            }

            return sData;
        }

        inline std::string Join(const std::vector<std::string> &i_asString, const char i_bDelimeter) {
            return Join(i_asString, std::string(&i_bDelimeter, 1));
        }


        inline std::string &Replace(std::string &i_sSource, const char i_bFind, const char i_bReplaceWith) {
            const size_t iSize = i_sSource.size();
            for (size_t i = 0; i < iSize; i++) {
                if (i_sSource[i] == i_bFind)
                    i_sSource[i] = i_bReplaceWith;
            }

            return i_sSource;
        }

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


        inline long long ToInt64(const std::string &i_sBuffer) {
            char *pEnd;
            return strtoll(i_sBuffer.c_str(), &pEnd, 10);
        }

        inline unsigned long long ToUInt64(const std::string &i_sBuffer) {
            return static_cast<unsigned long long>(ToInt64(i_sBuffer));
        }

        inline int ToInt(const std::string &i_sBuffer) {
            char *pEnd;
            return strtol(i_sBuffer.c_str(), &pEnd, 10);
        }

        inline unsigned int ToUInt(const std::string &i_sBuffer) {
            return static_cast<unsigned int>(ToInt(i_sBuffer));
        }

        inline float ToFloat(const std::string &i_stBuffer) {
            char *pEndPtr;
            return std::strtof(i_stBuffer.c_str(), &pEndPtr);
        }

        inline double ToDouble(const std::string &i_stBuffer) {
            char *pEndPtr;
            return std::strtod(i_stBuffer.c_str(), &pEndPtr);
        }


        inline std::string ToLowerCopy(const std::string &i_sBuffer) {
            std::string sToLower = i_sBuffer;
            for (char &c: sToLower) {
                c = tolower(c);
            }
            return sToLower;
        }

        inline void ToLower(std::string &i_sBuffer) {
            for (char &c: i_sBuffer) {
                c = tolower(c);
            }
        }


        inline std::string ToUpperCopy(const std::string &i_sBuffer) {
            std::string sToLower = i_sBuffer;
            for (char &c: sToLower) {
                c = toupper(c);
            }
            return sToLower;
        }

        inline void ToUpper(std::string &i_sBuffer) {
            for (char &c: i_sBuffer) {
                c = toupper(c);
            }
        }


        inline bool
        Contains(const std::string &i_sString, const std::string &i_sToFind, const bool i_fCaseSensetive = true) {
            const size_t nPosition = (i_fCaseSensetive ? i_sString.find(i_sToFind) : ToLowerCopy(i_sString).find(
                    ToLowerCopy(i_sToFind)));

            return (nPosition != std::string::npos);
        }


        inline size_t Size(const char *i_szString, const size_t i_nMaxSize) {
            size_t nSize = 0;

            if (i_szString) {
                for (; nSize < i_nMaxSize && *i_szString++ != 0x00; nSize++) {}
            }

            return nSize;
        }


        inline void Set(char *i_pDestination, const char *i_szString, const size_t i_nSize, size_t i_nMax) {
            memset(static_cast<void *>(i_pDestination), 0, i_nMax);

            if (i_nSize <= i_nMax) {
                i_nMax = i_nSize;
            }

            memcpy(static_cast<void *>(i_pDestination), i_szString, i_nMax);
        }

        inline void Set(char *i_pDestination, const char *i_szString, const size_t i_nMax) {
            Set(i_pDestination, i_szString, strlen(i_szString), i_nMax);
        }

        inline void Set(char *i_pDestination, const std::string &i_sData, const size_t i_nMax) {
            Set(i_pDestination, i_sData.c_str(), i_sData.length(), i_nMax);
        }

        inline std::string Get(char *i_pSource, const size_t i_nMaxSize) {
            const size_t nSize = Size(i_pSource, i_nMaxSize);
            return std::string(i_pSource, nSize);
        }


        inline size_t Count(const char *i_szString, const size_t i_nSize, const char i_bDelimeter) {
            return std::count(i_szString, i_szString + i_nSize, i_bDelimeter);
        }

        inline size_t Count(const std::string &i_sString, const char i_bDelimeter) {
            return Count(i_sString.c_str(), i_sString.size(), i_bDelimeter);
        }


        // E.g.: std::string sString = "Hallo"; char szData[10]; memset(szData, 0, sizeof(szData)); StringToArray(szData, sString);
        template<typename T>
        void ToArray(T &i_pDestination, const char *i_szString, const size_t i_nSize) {
            return Set(i_pDestination, i_szString, i_nSize, sizeof(i_pDestination));
        }

        template<typename T>
        void ToArray(T &i_pDestination, const char *i_szString) {
            return ToArray(i_pDestination, i_szString, strlen(i_szString));
        }

        template<typename T>
        void ToArray(T &i_pDestination, const std::string &i_sData) {
            return ToArray(i_pDestination, i_sData.c_str(), i_sData.length());
        }


        // E.g.: char szData[32]; std::string sString = ArrayToString(szData);
        template<typename T>
        std::string FromArray(const T &i_pSource) {
            return Get(const_cast<char *>(i_pSource), sizeof(i_pSource));
        }

        template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
        inline std::string ToHex(T i_oValue) {
            char achHexString[4 * sizeof(T) + 3];
            sprintf_s(achHexString, sizeof(achHexString), "0x%02x", i_oValue);
            return std::string(achHexString);
        }
    }
}