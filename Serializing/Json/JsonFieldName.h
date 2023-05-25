#pragma once

#include <string_view>
#include <type_traits>

/// @namespace Devel::Serializing
/// @brief The namespace encapsulating serializing related functionality in the Devel framework.
namespace Devel::Serializing {
    /// @class Devel::Serializing::CJsonFieldName
    /// @brief A class representing a JSON field name.
    ///
    /// This class encapsulates a JSON field name and provides access to the underlying name string.
    ///
    /// <b>Example</b>
    ///
    /// This class represents a JSON field name and provides access to the underlying name string.
    ///
    /// Here is an example of how to use the CJsonFieldName class:
    ///
    /// @code{.cpp}
    ///     #include "CJsonFieldName.h"
    ///     #include <iostream>
    ///
    ///     using namespace Devel::Serializing;
    ///
    ///     int main() {
    ///         // Create a CJsonFieldName object with a C-style string
    ///         CJsonFieldName fieldName("age");
    ///
    ///         // Access the underlying name string
    ///         const char* name = fieldName.name();
    ///
    ///         // Print the field name
    ///         std::cout << "Field name: " << name << std::endl;
    ///
    ///         // Create a CJsonFieldName object with a std::string_view
    ///         std::string_view viewName = "name";
    ///         CJsonFieldName fieldName2(viewName);
    ///
    ///         // Access the underlying name string
    ///         const char* name2 = fieldName2.name();
    ///
    ///         // Print the field name
    ///         std::cout << "Field name 2: " << name2 << std::endl;
    ///
    ///         return 0;
    ///     }
    /// @endcode
    class CJsonFieldName {
    public:
        /// @brief Constructs a CJsonFieldName object with a C-style string.
        /// @param i_pName The C-style string representing the field name.
        explicit CJsonFieldName(const char *i_pName) : m_pName(i_pName) {}

        /// @brief Constructs a CJsonFieldName object with a std::string_view.
        /// @param i_stName The std::string_view representing the field name.
        explicit CJsonFieldName(const std::string_view i_stName) : m_pName(i_stName.data()) {}

        /// @brief Copy constructor for CJsonFieldName.
        /// @param i_oOther The CJsonFieldName object to be copied.
        CJsonFieldName(const CJsonFieldName &i_oOther) = default;

        /// @brief Move constructor for CJsonFieldName.
        /// @param i_oOther The CJsonFieldName object to be moved.
        CJsonFieldName(CJsonFieldName &&i_oOther) noexcept: m_pName(i_oOther.m_pName) {}

        /// @brief Destructor for CJsonFieldName.
        ~CJsonFieldName() = default;

        /// @brief Copy assignment operator for CJsonFieldName.
        /// @param i_oOther The CJsonFieldName object to be assigned.
        /// @return A reference to the assigned CJsonFieldName object.
        CJsonFieldName &operator=(const CJsonFieldName &i_oOther) {
            m_pName = i_oOther.m_pName;
            return *this;
        }

        /// @brief Move assignment operator for CJsonFieldName.
        /// @param i_oOther The CJsonFieldName object to be moved.
        /// @return A reference to the moved CJsonFieldName object.
        CJsonFieldName &operator=(CJsonFieldName &&i_oOther) {
            m_pName = i_oOther.m_pName;
            return *this;
        }

        /// @brief Retrieves the underlying name string.
        /// @return A pointer to the underlying name string.
        [[nodiscard]] const char *name() const { return m_pName; }

    private:
        /// @var char* m_pName
        /// @brief The underlying name string.
        const char *m_pName;
    };
}