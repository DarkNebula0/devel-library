#pragma once
#include <stdexcept>

namespace Devel {
    static auto IndexOutOfRangeException = std::range_error("Index out of range!");
    static auto NoEntryFoundException = std::range_error( "No entry found!");
    static auto ShouldNotExecuteException = std::logic_error("This Code should not get executed!");
}