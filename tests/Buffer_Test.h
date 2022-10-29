#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel::IO;

TEST_CASE( "SIZE", "[IO_BUFFER_TEST]" ) {
    CDynamicBuffer oBuffer(5);
    REQUIRE( oBuffer.size() == 0);
    REQUIRE( oBuffer.allocatedSize() >= 5);
    REQUIRE( oBuffer.allocatedSize() <= 10);
}