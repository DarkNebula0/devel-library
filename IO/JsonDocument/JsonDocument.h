#pragma once

#include "Core/Global.h"
#include "Core/Exceptions.h"
#include "IO/JsonObject/JsonObject.h"
#include "IO/Buffer/Buffer.h"

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    static auto InvalidFormatException = std::runtime_error("Object format is invalid!");
    static auto InvalidEncodingException = std::runtime_error("Object encoding is invalid!");

    /// @class Devel::IO::CJsonDocument
    /// @brief A class for representing and handling a JSON document.
    ///
    /// This class encapsulates a JSON object and provides functions for parsing and serializing JSON.
    /// <b>Example</b>
    ///
    /// @code{.cpp}
    ///     // Create a JSON document
    ///     Devel::IO::CJsonDocument doc;
    ///
    ///     // Parse a JSON string
    ///     doc.parse("{\"key\": \"value\"}");
    ///
    ///     // Get the object with the key "key"
    ///     Devel::IO::CJsonObject obj = doc.getObject("key");
    ///
    ///     // Serialize the document into a JSON string
    ///     std::string jsonString = doc.serialize(true);
    /// @endcode
    ///
    /// @throws std::runtime_error If the format or encoding of the JSON is invalid.
    class CJsonDocument {
    public:
        /// @brief Default constructor for CJsonDocument.
        /// @details Initializes an empty CJsonDocument.
        CJsonDocument();

        /// @brief Constructor for CJsonDocument from a JSON string.
        /// @param i_stJson - The JSON string to initialize the CJsonDocument.
        CJsonDocument(const std::string &i_stJson);

        /// @brief Copy constructor for CJsonDocument.
        /// @param i_oOther - The CJsonDocument to copy.
        /// @details Initializes a CJsonDocument by copying another CJsonDocument.
        CJsonDocument(const CJsonDocument &i_oOther) : CJsonDocument() { this->operator=(i_oOther); }

        /// @brief Move constructor for CJsonDocument.
        /// @param i_oOther - The CJsonDocument to move.
        /// @details Initializes a CJsonDocument by moving another CJsonDocument.
        CJsonDocument(CJsonDocument &&i_oOther) noexcept: CJsonDocument() { this->operator=(std::move(i_oOther)); }

        /// @brief Destructor for CJsonDocument.
        virtual ~CJsonDocument();

    private:
        /// @var CJsonObject m_oObject
        /// @brief The encapsulated JSON object.
        CJsonObject m_oObject;
    private:
        /// @var char* m_pBuffer
        /// @brief The buffer containing the JSON string.
        char *m_pBuffer;
        /// @var char* m_pPointer
        /// @brief The pointer to the current character during parsing.
        char *m_pPointer;
        /// @var char* m_pEnd
        /// @brief The pointer to the end of the buffer.
        char *m_pEnd;
    private:
        /// @brief Removes whitespace from the current position of the buffer pointer to the next non-whitespace character.
        /// @details This method will move the buffer pointer past all consecutive whitespace characters.
        void removeWhitespace();

        /// @brief Selects the appropriate parser based on the first character of the JSON value.
        /// @param i_stOutBuffer - The output buffer to which the parsed value is added.
        /// @param i_pObject - The CJsonObject that the parsed value should be added to. If nullptr, the parsed value is not added to any object.
        /// @details This method will look at the first character of the JSON value and call the appropriate parse method based on the character.
        void selectParser(std::string &i_stOutBuffer, CJsonObject *i_pObject = nullptr);

    private:
        /// @brief Parses a Unicode hexadecimal value from the buffer.
        /// @return The parsed Unicode hexadecimal value.
        /// @details This method will parse four characters from the buffer as a Unicode hexadecimal value and return the value.
        uint parseUnicodeHex();

    private:
        /// @brief Parses a null value from the buffer.
        /// @param i_stOutBuffer - The output buffer to which the parsed null value is added.
        /// @param i_pObject - The CJsonObject that the parsed null value should be added to.
        /// @details This method will parse a null value from the buffer and add it to the output buffer and CJsonObject.
        void parseNull(std::string &i_stOutBuffer, CJsonObject *i_pObject);

        /// @brief Parses a boolean value from the buffer.
        /// @param i_stOutBuffer - The output buffer to which the parsed boolean value is added.
        /// @param i_pObject - The CJsonObject that the parsed boolean value should be added to.
        /// @details This method will parse a boolean value from the buffer and add it to the output buffer and CJsonObject.
        void parseBool(std::string &i_stOutBuffer, CJsonObject *i_pObject);

        /// @brief Parses an object from the buffer.
        /// @param i_stOutBuffer - The output buffer to which the parsed object is added.
        /// @param i_pObject - The CJsonObject that the parsed object should be added to.
        /// @details This method will parse an object from the buffer and add it to the output buffer and CJsonObject.
        void parseObject(std::string &i_stOutBuffer, CJsonObject *i_pObject);

        /// @brief Parses a string from the buffer.
        /// @param i_stOutBuffer - The output buffer to which the parsed string is added.
        /// @param i_pObject - The CJsonObject that the parsed string should be added to. If nullptr, the parsed string is not added to any object.
        /// @details This method will parse a string from the buffer and add it to the output buffer and CJsonObject if i_pObject is not nullptr.
        void parseString(std::string &i_stOutBuffer, CJsonObject *i_pObject = nullptr);

        /// @brief Parses a number from the buffer.
        /// @param i_stOutBuffer - The output buffer to which the parsed number is added.
        /// @param i_pObject - The CJsonObject that the parsed number should be added to.
        /// @details This method will parse a number from the buffer and add it to the output buffer and CJsonObject.
        void parseNumber(std::string &i_stOutBuffer, CJsonObject *i_pObject);

        /// @brief Parses an array from the buffer.
        /// @param i_pObject - The CJsonObject that the parsed array should be added to.
        /// @details This method will parse an array from the buffer and add it to the CJsonObject.
        void parseArray(CJsonObject *i_pObject);

    private:
        /// @brief Selects the appropriate serializer based on the type of the JSON value in the CJsonObject.
        /// @param i_stBuffer - The output buffer to which the serialized JSON value is added.
        /// @param i_oObject - The CJsonObject containing the JSON value to be serialized.
        /// @param i_bFormatted - Whether the serialized JSON string should be pretty-printed.
        /// @details This method will look at the type of the JSON value in the CJsonObject and call the appropriate serialize method.
        static void selectSerializer(std::string &i_stBuffer, CJsonObject &i_oObject, bool i_bFormatted = false);

        /// @brief Serializes an array into a JSON string.
        /// @param i_stBuffer - The output buffer to which the serialized array is added.
        /// @param i_oObject - The CJsonObject containing the array to be serialized.
        /// @param i_bFormatted - Whether the serialized JSON string should be pretty-printed.
        /// @details This method will serialize the array in the CJsonObject into a JSON string and add it to the output buffer.
        static void serializeArray(std::string &i_stBuffer, CJsonObject &i_oObject, bool i_bFormatted = false);

        /// @brief Serializes an object into a JSON string.
        /// @param i_stBuffer - The output buffer to which the serialized object is added.
        /// @param i_oObject - The CJsonObject containing the object to be serialized.
        /// @param i_bFormatted - Whether the serialized JSON string should be pretty-printed.
        /// @details This method will serialize the object in the CJsonObject into a JSON string and add it to the output buffer.
        static void serializeObject(std::string &i_stBuffer, CJsonObject &i_oObject, bool i_bFormatted = false);

        /// @brief Serializes a number into a JSON string.
        /// @param i_stBuffer - The output buffer to which the serialized number is added.
        /// @param i_oObject - The CJsonObject containing the number to be serialized.
        /// @details This method will serialize the number in the CJsonObject into a JSON string and add it to the output buffer.
        static void serializeNumber(std::string &i_stBuffer, CJsonObject &i_oObject);

        /// @brief Serializes a string into a JSON string.
        /// @param i_stBuffer - The output buffer to which the serialized string is added.
        /// @param i_oObject - The CJsonObject containing the string to be serialized.
        /// @details This method will serialize the string in the CJsonObject into a JSON string and add it to the output buffer.
        static void serializeString(std::string &i_stBuffer, CJsonObject &i_oObject);

        /// @brief Serializes a null value into a JSON string.
        /// @param i_stBuffer - The output buffer to which the serialized null value is added.
        /// @details This method will serialize a null value into a JSON string and add it to the output buffer.
        static void serializeNull(std::string &i_stBuffer);

        /// @brief Serializes a boolean value into a JSON string.
        /// @param i_stBuffer - The output buffer to which the serialized boolean value is added.
        /// @param i_oObject - The CJsonObject containing the boolean value to be serialized.
        /// @details This method will serialize the boolean value in the CJsonObject into a JSON string and add it to the output buffer.
        static void serializeBool(std::string &i_stBuffer, CJsonObject &i_oObject);

    private:
        /// @brief Sets the buffer for the JSON document and clears the previous buffer if any.
        /// @param i_pBuffer - The new buffer to be set.
        /// @param i_nSize - The size of the new buffer.
        /// @details This method will clear the previous buffer if any, and set the new buffer and update the pointer and end accordingly.
        inline void setBuffer(char *i_pBuffer, const size_t i_nSize) {
            this->clearBuffer();
            this->m_pBuffer = i_pBuffer;
            this->m_pPointer = i_pBuffer;
            this->m_pEnd = i_pBuffer + i_nSize;
        }

        /// @brief Clears the buffer for the JSON document.
        /// @details This method will delete the buffer and set the buffer pointer and end to nullptr.
        inline void clearBuffer() {
            delete[] m_pBuffer;
            this->m_pBuffer = nullptr;
            this->m_pPointer = nullptr;
            this->m_pEnd = nullptr;
        }

        /// @brief Skips the current character in the buffer.
        /// @details This method will increment the buffer pointer to skip the current character.
        inline void skipChar() {
            this->m_pPointer++;
        }

    private:
        /// @brief Returns the size of the buffer.
        /// @return The size of the buffer.
        /// @details This method will return the difference between the end of the buffer and the start of the buffer.
        inline size_t getBufferSize() const { return this->m_pEnd - this->m_pBuffer; }

        /// @brief Checks if the current character in the buffer matches the expected character.
        /// @param i_chExpect - The expected character.
        /// @return Whether the current character in the buffer matches the expected character.
        /// @details This method will compare the current character in the buffer with the expected character, and increment the buffer pointer if they match.
        inline bool checkChar(const char i_chExpect) {
            if (*this->m_pPointer == i_chExpect) {
                this->m_pPointer++;
                return true;
            }
            return false;
        }

    public:
        /// @brief Parses a JSON string.
        /// @param i_stJson - The JSON string to parse.
        /// @details Parses a JSON string and populates the encapsulated JSON object.
        void parse(const std::string &i_stJson);

        /// @brief Serializes the encapsulated JSON object into a JSON string.
        /// @param i_bFormatted - Whether the output string should be pretty-printed.
        /// @return The serialized JSON string.
        /// @details Serializes the encapsulated JSON object into a JSON string.
        std::string serialize(bool i_bFormatted);

    public:
        /// @brief Clears the encapsulated JSON object.
        /// @details Clears the encapsulated JSON object.
        void clear() {
            this->m_oObject.clear();
        }

    public:
        /// @brief Gets a JSON object by key from the encapsulated JSON object.
        /// @param i_stKey - The key of the JSON object to get.
        /// @return The JSON object with the given key.
        /// @details Gets a JSON object by key from the encapsulated JSON object.
        inline CJsonObject &getObject(const std::string &i_stKey) { return this->operator[](i_stKey); }

        /// @brief Gets the encapsulated JSON object.
        /// @return The encapsulated JSON object.
        /// @details Gets the encapsulated JSON object.
        inline CJsonObject &toObject() { return this->m_oObject; }

    public:
        /// @brief Overload of assignment operator for CJsonDocument.
        /// @param i_oOther - The CJsonDocument to copy.
        /// @return A reference to this CJsonDocument.
        /// @details Assigns the values of another CJsonDocument to this CJsonDocument.
        inline CJsonObject &operator[](const std::string &i_stKey) {
            return this->m_oObject.operator[](i_stKey);
        }

        /// @brief Overload of move assignment operator for CJsonDocument.
        /// @param i_oOther - The CJsonDocument to move.
        /// @return A reference to this CJsonDocument.
        /// @details Moves the values of another CJsonDocument to this CJsonDocument.
        inline CJsonDocument &operator=(const CJsonDocument &i_oOther) {
            this->m_oObject = i_oOther.m_oObject;
            return *this;
        }

        /// @brief Moves the ownership of the CJsonObject from the given CJsonDocument to this CJsonDocument.
        /// @param i_oOther - The CJsonDocument from which the ownership of the CJsonObject is to be moved.
        /// @return Reference to this CJsonDocument.
        /// @details This method will move the ownership of the CJsonObject from the given CJsonDocument to this CJsonDocument and return a reference to this CJsonDocument.
        inline CJsonDocument &operator=(CJsonDocument &&i_oOther) noexcept {
            this->m_oObject = std::move(i_oOther.m_oObject);
            return *this;
        }
    };
}