#pragma once
#include <stdexcept>

/// @namespace Devel
/// @brief A namespace for development related classes and functions.
///
/// <b>Example</b>
///
/// @code{.cpp}
///     try {
///         // Some operations
///         throw Devel::IndexOutOfRangeException; // Throw the exception when an index is out of range
///     } catch (std::range_error &ex) {
///         std::cout << "Caught exception: " << ex.what() << std::endl;
///     }
/// @endcode
namespace Devel {
    /// @var static auto IndexOutOfRangeException
    /// @brief This exception is thrown when an index is out of the valid range.
    ///
    /// This variable is a predefined instance of std::range_error exception
    /// which is initialized with the error message "Index out of range!".
    static auto IndexOutOfRangeException = std::range_error("Index out of range!");

    /// @var static auto NoEntryFoundException
    /// @brief This exception is thrown when a required entry is not found.
    ///
    /// This variable is a predefined instance of std::range_error exception
    /// which is initialized with the error message "No entry found!".
    static auto NoEntryFoundException = std::range_error( "No entry found!");

    /// @var static auto ShouldNotExecuteException
    /// @brief This exception is thrown when a code block that should not be executed is reached.
    ///
    /// This variable is a predefined instance of std::logic_error exception
    /// which is initialized with the error message "This Code should not get executed!".
    static auto ShouldNotExecuteException = std::logic_error("This Code should not get executed!");
}