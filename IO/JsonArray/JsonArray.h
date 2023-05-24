#pragma once

#include "Threading/MutexVector/MutexVector.h"
#include "IO/JsonObject/JsonObject.h"

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    /// @class Devel::IO::CJsonArray
    /// @brief A thread-safe array class for Json objects.
    ///
    /// This class encapsulates a thread-safe vector of Json objects by extending the CMutexVector class from the Threading namespace.
    ///
    /// @inherits Threading::CMutexVector<CJsonObject>
    ///
    /// @var std::vector<CJsonObject> Threading::CMutexVector<CJsonObject>::m_vVector
    /// @brief The protected vector object that holds the Json objects.
    ///
    /// <b>Example</b>
    ///
    /// The following example demonstrates how to use various functionalities of the `CJsonArray` class.
    ///
    /// @code{.cpp}
    ///     // Create an instance of CJsonArray
    ///     Devel::IO::CJsonArray jsonArray;
    ///
    ///     // Create a Json object
    ///     Devel::IO::CJsonObject jsonObject;
    ///
    ///     // Add the Json object to the array
    ///     jsonArray.push_back(jsonObject);
    ///
    ///     // Accessing elements in the array
    ///     CJsonObject firstObject = jsonArray[0];
    ///
    ///     // Reserve space for elements
    ///     jsonArray.allocate(10);
    /// @endcode
    ///
    /// The thread safety is ensured by the parent class Threading::CMutexVector.
    class CJsonArray : public Threading::CMutexVector<CJsonObject> {
    public:
        /// @brief Default constructor for CJsonArray.
        /// @details Initializes an empty CJsonArray.
        CJsonArray() = default;

        /// @brief Explicit constructor for CJsonArray from a standard vector of CJsonObject.
        /// @param i_oOther - The standard vector to initialize the CJsonArray.
        /// @details Initializes a CJsonArray from a standard vector of CJsonObject.
        explicit CJsonArray(std::vector<CJsonObject> &i_oOther) {
            Threading::CMutexVector<CJsonObject>::operator=(i_oOther);
        }

        /// @brief Explicit constructor for CJsonArray from a CMutexVector of CJsonObject.
        /// @param i_oOther - The CMutexVector to initialize the CJsonArray.
        /// @details Initializes a CJsonArray from a CMutexVector of CJsonObject.
        explicit CJsonArray(Threading::CMutexVector<CJsonObject> &i_oOther) {
            Threading::CMutexVector<CJsonObject>::operator=(i_oOther);
        }

        /// @brief Copy constructor for CJsonArray.
        /// @param i_oOther - The CJsonArray to copy.
        /// @details Initializes a CJsonArray by copying another CJsonArray.
        CJsonArray(const CJsonArray &i_oOther) : CMutexVector(i_oOther) { this->operator=(i_oOther); }

        /// @brief Move constructor for CJsonArray.
        /// @param i_oOther - The CJsonArray to move.
        /// @details Initializes a CJsonArray by moving another CJsonArray. The source CJsonArray is left in a valid but unspecified state after the move.
        CJsonArray(CJsonArray &&i_oOther) noexcept { this->operator=(std::move(i_oOther)); }

        /// @brief Default destructor for CJsonArray.
        ~CJsonArray() override = default;

    public:
        /// @brief Allocates space for n elements.
        /// @param i_nSize - The number of elements to allocate space for.
        /// @details Preallocates memory for a specified number of elements.
        void allocate(const size_t i_nSize) { Threading::CMutexVector<CJsonObject>::reserve(i_nSize); }

    public:
        /// @brief Returns a constant reference to the underlying CMutexVector.
        /// @return The underlying CMutexVector.
        inline const Threading::CMutexVector<CJsonObject> &data() const { return *this; }

    public:
        /// @brief Overload of assignment operator.
        /// @param i_oOther - The CJsonArray to copy.
        /// @return A reference to this CJsonArray.
        /// @details Assigns the values of another CJsonArray to this CJsonArray.
        inline CJsonArray &operator=(const CJsonArray &i_oOther) {
            Threading::CMutexVector<CJsonObject>::operator=(i_oOther);
            return *this;
        }

        /// @brief Overload of move assignment operator.
        /// @param i_oOther - The CJsonArray to move.
        /// @return A reference to this CJsonArray.
        /// @details Moves the values of another CJsonArray to this CJsonArray. The source CJsonArray is left in a valid but unspecified state after the move.
        inline CJsonArray &operator=(CJsonArray &&i_oOther) noexcept {
            Threading::CMutexVector<CJsonObject>::operator=(std::move(i_oOther));
            return *this;
        }
    };
}