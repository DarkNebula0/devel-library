#pragma once

#include "Core/Exceptions.h"
#include "IO/Buffer/Buffer.h"
#include "Core/CharArray/CharArray.h"

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    static auto ZeroTerminatedStringException = std::overflow_error("String is not zero terminated!");

    /// @class Devel::IO::CReadStream
    /// @brief A class for reading data from a buffer.
    /// This class provides functionality to read data from a buffer. It allows reading strings, raw data, and numeric values from the buffer.
    /// <b>Example</b>
    /// @code{.cpp}
    /// // Create a buffer
    /// const char* buffer = "Hello, World!";
    /// size_t bufferSize = strlen(buffer) + 1; // Including the null terminator
    /// // Create a read stream
    /// Devel::IO::CReadStream stream(buffer, bufferSize);
    /// // Read a string from the stream
    /// std::string str = stream.getString();
    /// std::cout << "String: " << str << std::endl;
    /// // Read raw data from the stream
    /// char rawData[6];
    /// stream.getRaw(rawData, 6);
    /// std::cout << "Raw Data: ";
    /// for (int i = 0; i < 6; ++i) {
    /// std::cout << rawData[i];
    /// }
    /// std::cout << std::endl;
    /// // Read a numeric value from the stream
    /// int num = stream.get<int>();
    /// std::cout << "Numeric Value: " << num << std::endl;
    /// @endcode
    class CReadStream {
    public:
        /// @brief Default constructor for CReadStream.
        /// @details Initializes an empty CReadStream.
        CReadStream()
                : m_pBuffer(nullptr), m_nSize(0), m_nPosition(0), m_fDeleteBuffer(false) {
            this->clear();
        }

        /// @brief Constructor for CReadStream with a buffer.
        /// @param i_pBuffer - The buffer to read data from.
        /// @param i_nSize - The size of the buffer.
        /// @param i_fCopyBuffer - Whether to make a copy of the buffer or use it directly.
        CReadStream(const char *i_pBuffer, const size_t i_nSize, const bool i_fCopyBuffer)
                : CReadStream() {
            this->setBuffer(i_pBuffer, i_nSize, i_fCopyBuffer);
        }

        /// @brief Copy constructor for CReadStream.
        /// @param i_oOther - The CReadStream to copy.
        CReadStream(const CReadStream &i_oOther) {
            this->operator=(i_oOther);
        }

        /// @brief Move constructor for CReadStream.
        /// @param i_oOther - The CReadStream to move.
        CReadStream(CReadStream &&i_oOther) noexcept {
            this->operator=(std::move(i_oOther));
        }

        /// @brief Destructor for CReadStream.
        virtual ~CReadStream() = default;

    private:
        /// @brief Deletes the buffer.
        /// @brief Checks if the buffer is valid.
        /// @return True if the buffer is valid, false otherwise.
        void deleteBuffer();

    private:
        /// @brief Checks if the position and read bytes are valid within the buffer.
        /// @param i_nPosition - The position in the buffer.
        /// @param i_nReadBytes - The number of bytes to read.
        /// @return True if the position and read bytes are valid, false otherwise.
        [[nodiscard]] bool checkBuffer() const {
            if (!this->m_pBuffer) {
                throw NoBufferException;
            }

            return true;
        }

        /// @brief Checks if the buffer and the position and read bytes are valid.
        /// @param i_nPosition - The position in the buffer.
        /// @param i_nReadBytes - The number of bytes to read.
        /// @return True if the buffer and the position and read bytes are valid, false otherwise.
        [[nodiscard]] bool checkSize(const size_t i_nPosition, const size_t i_nReadBytes) const {
            if (this->leftBytes(i_nPosition) < i_nReadBytes) {
                throw IndexOutOfRangeException;
            }

            return true;
        }

        /// @brief Checks if the buffer and the position and read bytes are valid.
        /// @param i_nPosition - The position in the buffer.
        /// @param i_nReadBytes - The number of bytes to read.
        /// @return True if the buffer and the position and read bytes are valid, false otherwise.
        [[nodiscard]] bool checkBufferAndSize(const size_t i_nPosition, const size_t i_nReadBytes) const {
            return this->checkBuffer() && this->checkSize(i_nPosition, i_nReadBytes);
        }

        /// @brief Returns the buffer position for the given position.
        /// @param i_nPosition - The position in the buffer.
        /// @return The buffer position.
        [[nodiscard]] char *bufferPosition(const size_t i_nPosition) const {
            return const_cast<char *>(this->m_pBuffer + i_nPosition);
        }

    public:
        /// @brief Sets the buffer for the CReadStream.
        /// @param i_pBuffer - The buffer to set.
        /// @param i_nSize - The size of the buffer.
        /// @param i_fCopyBuffer - Whether to make a copy of the buffer or use it directly.
        void setBuffer(const char *i_pBuffer, size_t i_nSize, bool i_fCopyBuffer = false);

        /// @brief Sets the current position of the CReadStream.
        /// @param i_nPosition - The position to set.
        void setPosition(const size_t i_nPosition) {
            if (this->m_pBuffer) {
                this->m_nPosition = i_nPosition > this->m_nSize ? this->m_nSize : i_nPosition;
            }
        }

        /// @brief Moves the current position of the CReadStream.
        /// @param i_nBytes - The number of bytes to move the position.
        void seek(const size_t i_nBytes) {
            if (i_nBytes > 0) {
                this->setPosition(this->position() + i_nBytes);
            }
        }

        /// @brief Clears the CReadStream.
        void clear();

    public:
        /// @brief Returns the buffer of the CReadStream.
        /// @return The buffer of the CReadStream.
        [[nodiscard]] const char *buffer() const {
            return this->m_pBuffer;
        }

        /// @brief Returns the size of the buffer.
        /// @return The size of the buffer.
        [[nodiscard]] size_t size() const {
            return this->m_nSize;
        }

        /// @brief Returns the current position of the CReadStream.
        /// @return The current position of the CReadStream.
        [[nodiscard]] size_t position() const {
            return this->m_nPosition;
        }

        /// @brief Returns the number of bytes left from the current position to the end of the buffer.
        /// @param i_nPosition - The position to calculate the number of bytes from.
        /// @return The number of bytes left from the current position to the end of the buffer.
        [[nodiscard]] size_t leftBytes(const size_t i_nPosition) const {
            if (this->m_pBuffer) {
                return this->m_nSize - i_nPosition;
            }

            return 0;
        }

        /// @brief Returns the number of bytes left from the current position to the end of the buffer.
        /// @return The number of bytes left from the current position to the end of the buffer.
        [[nodiscard]] size_t leftBytes() const {
            return this->leftBytes(this->m_nPosition);
        }

        /// @brief Checks if the current position is at the end of the buffer.
        /// @return True if the current position is at the end of the buffer, false otherwise.
        [[nodiscard]] bool isEndOfBuffer() const {
            return (this->m_nPosition == this->size());
        }

        /// @brief Checks if the current position is at the end of the buffer.
        /// @return True if the current position is at the end of the buffer, false otherwise.
        [[nodiscard]] bool isEoB() const {
            return this->isEndOfBuffer();
        }

    private:
        /// @brief Reads a string from the buffer.
        /// @tparam TReturnType - The type of string to return.
        /// @tparam TType - The type of characters in the string.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_nLength - The length of the string to read.
        /// @param i_fIsZeroTerminated - Whether the string is zero-terminated.
        /// @param i_fSetPosition - Whether to set the current position after reading the string.
        /// @return The string read from the buffer.
        template<typename TReturnType, typename TType>
        TReturnType
        readString(const size_t i_nPosition, size_t i_nLength, bool i_fIsZeroTerminated, const bool i_fSetPosition) {
            TReturnType sReturn;

            if (this->checkBuffer()) {
                if (i_fIsZeroTerminated) {
                    const size_t nLeftBytes = this->leftBytes(i_nPosition);
                    if (nLeftBytes > 0) {
                        // Set to false for check if found
                        i_fIsZeroTerminated = false;
                        i_nLength = 0;

                        sReturn.reserve((nLeftBytes > 20 ? 20 : nLeftBytes));

                        for (; i_nLength < nLeftBytes; i_nLength += sizeof(TType)) {
                            auto *pBufferPosition = reinterpret_cast<TType *>(this->bufferPosition(
                                    this->m_nPosition + i_nLength));
                            if (*pBufferPosition != TType(0x00)) {
                                sReturn += *pBufferPosition;
                            } else {
                                i_fIsZeroTerminated = true;
                                break;
                            }
                        }

                        if (!i_fIsZeroTerminated) {
                            throw ZeroTerminatedStringException;
                        }
                    }
                } else if (i_nLength > 0 && this->checkSize(i_nPosition, i_nLength)) {
                    sReturn = TReturnType(reinterpret_cast<TType *>(this->bufferPosition(i_nPosition)), i_nLength);
                    i_nLength *= sizeof(TType);    // For wchar_t (x characters = x * 2 bytes)
                }

                if (i_fSetPosition) {
                    this->setPosition(i_nPosition + i_nLength + (i_fIsZeroTerminated * sizeof(TType)));
                }
            }

            return sReturn;
        }

    public:
        /// @brief Reads a string from the buffer.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_nLength - The length of the string to read.
        /// @param i_fIsZeroTerminated - Whether the string is zero-terminated.
        /// @param i_fSetPosition - Whether to set the current position after reading the string.
        /// @return The string read from the buffer.
        std::string getString(const size_t i_nPosition, const size_t i_nLength, const bool i_fIsZeroTerminated,
                              const bool i_fSetPosition) {
            return this->readString<std::string, char>(i_nPosition, i_nLength, i_fIsZeroTerminated, i_fSetPosition);
        }

        /// @brief Reads a string from the buffer.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_nLength - The length of the string to read.
        /// @param i_fSetPosition - Whether to set the current position after reading the string.
        /// @return The string read from the buffer.
        std::string getString(const size_t i_nPosition, const size_t i_nLength, const bool i_fSetPosition = true) {
            return this->getString(i_nPosition, i_nLength, false, i_fSetPosition);
        }

        /// @brief Reads a string from the buffer.
        /// @param i_nLength - The length of the string to read.
        /// @param i_fSetPosition - Whether to set the current position after reading the string.
        /// @return The string read from the buffer.
        std::string getString(const size_t i_nLength, const bool i_fSetPosition = true) {
            return this->getString(this->m_nPosition, i_nLength, false, i_fSetPosition);
        }

        /// @brief Reads a null-terminated string from the buffer.
        /// @param i_fSetPosition - Whether to set the current position after reading the string.
        /// @return The string read from the buffer.
        std::string getString(const bool i_fSetPosition = true) {
            return this->getString(this->m_nPosition, 0, true, i_fSetPosition);
        }

    public:
        /// @brief Reads a wide string from the buffer.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_nLength - The length of the wide string to read.
        /// @param i_fIsZeroTerminated - Whether the wide string is zero-terminated.
        /// @param i_fSetPosition - Whether to set the current position after reading the wide string.
        /// @return The wide string read from the buffer.
        std::wstring getWString(const size_t i_nPosition, const size_t i_nLength, const bool i_fIsZeroTerminated,
                                const bool i_fSetPosition) {
            return this->readString<std::wstring, wchar_t>(i_nPosition, i_nLength, i_fIsZeroTerminated, i_fSetPosition);
        }

        /// @brief Reads a wide string from the buffer.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_nLength - The length of the wide string to read.
        /// @param i_fSetPosition - Whether to set the current position after reading the wide string.
        /// @return The wide string read from the buffer.
        std::wstring getWString(const size_t i_nPosition, const size_t i_nLength, const bool i_fSetPosition = true) {
            return this->getWString(i_nPosition, i_nLength, false, i_fSetPosition);
        }

        /// @brief Reads a wide string from the buffer.
        /// @param i_nLength - The length of the wide string to read.
        /// @param i_fSetPosition - Whether to set the current position after reading the wide string.
        /// @return The wide string read from the buffer.
        std::wstring getWString(const size_t i_nLength, const bool i_fSetPosition = true) {
            return this->getWString(this->m_nPosition, i_nLength, false, i_fSetPosition);
        }

        /// @brief Reads a null-terminated wide string from the buffer.
        /// @param i_fSetPosition - Whether to set the current position after reading the wide string.
        /// @return The wide string read from the buffer.
        std::wstring getWString(const bool i_fSetPosition = true) {
            return this->getWString(this->m_nPosition, 0, true, i_fSetPosition);
        }

    public:
        /// @brief Reads raw data from the buffer.
        /// @param i_pDestination - The destination buffer to copy the raw data to.
        /// @param i_nReadBytes - The number of bytes to read.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_fSetPosition - Whether to set the current position after reading the raw data.
        void getRaw(void *i_pDestination, size_t i_nReadBytes, size_t i_nPosition, bool i_fSetPosition);

        /// @brief Reads raw data from the buffer.
        /// @param i_pDestination - The destination buffer to copy the raw data to.
        /// @param i_nReadBytes - The number of bytes to read.
        /// @param i_fSetPosition - Whether to set the current position after reading the raw data.
        void getRaw(void *i_pDestination, const size_t i_nReadBytes, const bool i_fSetPosition) {
            return this->getRaw(i_pDestination, i_nReadBytes, this->m_nPosition, i_fSetPosition);
        }

        /// @brief Reads raw data from the buffer.
        /// @param i_pDestination - The destination buffer to copy the raw data to.
        /// @param i_nReadBytes - The number of bytes to read.
        void getRaw(void *i_pDestination, const size_t i_nReadBytes) {
            return this->getRaw(i_pDestination, i_nReadBytes, true);
        }

    public:
        /// @brief Reads a value of type T from the buffer.
        /// @tparam T - The type of the value to read.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_fSetPosition - Whether to set the current position after reading the value.
        /// @return The value read from the buffer.
        template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
        T get(const size_t i_nPosition, const bool i_fSetPosition) {
            if (this->checkBufferAndSize(i_nPosition, sizeof(T))) {
                T tReturn = *reinterpret_cast<T *>(this->bufferPosition(i_nPosition));

                if (i_fSetPosition) {
                    this->setPosition(i_nPosition + sizeof(T));
                }

                return tReturn;
            }

            throw ShouldNotExecuteException;
        }

        /// @brief Reads a value of type T from the buffer.
        /// @tparam T - The type of the value to read.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @return The value read from the buffer.
        template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
        T get(const size_t i_nPosition) {
            return this->get<T>(this->m_nPosition, true);
        }

        /// @brief Reads a value of type T from the buffer.
        /// @tparam T - The type of the value to read.
        /// @return The value read from the buffer.
        template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
        T get() {
            return this->get<T>(this->m_nPosition);
        }

        /// @brief Reads an enum value from the buffer.
        /// @tparam T - The enum type.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @return The enum value read from the buffer.
        template<typename T, typename std::enable_if_t<std::is_enum_v<T>> * = nullptr>
        T get(const size_t i_nPosition) {
            return static_cast<T>(this->get<std::underlying_type_t<T>>(this->m_nPosition, true));
        }

        /// @brief Reads an enum value from the buffer.
        /// @tparam T - The enum type.
        /// @return The enum value read from the buffer.
        template<typename T, typename std::enable_if_t<std::is_enum_v<T>> * = nullptr>
        T get() {
            return static_cast<T>(this->get<std::underlying_type_t<T>>(this->m_nPosition));
        }

    public:
        /// @brief Reads an array from the buffer.
        /// @tparam TSize - The size of the array.
        /// @param i_nPosition - The position in the buffer to start reading from.
        /// @param i_fSetPosition - Whether to set the current position after reading the array.
        /// @return The array read from the buffer.
        template<size_t TSize>
        CCharArray<TSize> getArray(const size_t i_nPosition, const bool i_fSetPosition) {
            CCharArray<TSize> oBuffer;

            this->getRaw(oBuffer.begin(), TSize, i_nPosition, i_fSetPosition);

            return oBuffer;
        }

        /// @brief Reads an array from the buffer.
        /// @tparam TSize - The size of the array.
        /// @return The array read from the buffer.
        template<size_t TSize>
        CCharArray<TSize> getArray() {
            return this->getArray<TSize>(this->m_nPosition, true);
        }

    public:
        /// @brief Overload of the subscript operator.
        /// @param i_nIndex - The index in the buffer.
        /// @return The character at the specified index in the buffer.
        const char &operator[](const size_t i_nIndex) const {
            if (this->checkBufferAndSize(i_nIndex, 1)) {
                return this->m_pBuffer[i_nIndex];
            }

            throw ShouldNotExecuteException;
        }

        /// @brief Assignment operator.
        /// @param i_oOther - The CReadStream to assign.
        /// @return A reference to the assigned CReadStream.
        CReadStream &operator=(const CReadStream &i_oOther) {
            this->setBuffer(i_oOther.m_pBuffer, i_oOther.m_nSize, true);

            this->m_nPosition = i_oOther.m_nPosition;
            this->m_fDeleteBuffer = i_oOther.m_fDeleteBuffer;

            return *this;
        }

        /// @brief Move assignment operator.
        /// @param i_oOther - The CReadStream to move.
        /// @return A reference to the moved CReadStream.
        CReadStream &operator=(CReadStream &&i_oOther) noexcept {
            this->m_pBuffer = i_oOther.m_pBuffer;
            this->m_nSize = i_oOther.m_nSize;
            this->m_nPosition = i_oOther.m_nPosition;
            this->m_fDeleteBuffer = i_oOther.m_fDeleteBuffer;

            i_oOther.m_fDeleteBuffer = false;
            i_oOther.clear();

            return *this;
        }

    private:
        /// @var const char* m_pBuffer
        /// @brief Pointer to the buffer.
        const char *m_pBuffer{};

        /// @var size_t m_nSize
        /// @brief Size of the buffer.
        size_t m_nSize{};

        /// @var size_t m_nPosition
        /// @brief Current position in the buffer.
        size_t m_nPosition{};

        /// @var bool m_fDeleteBuffer
        /// @brief Whether to delete the buffer.
        bool m_fDeleteBuffer{};
    };
}