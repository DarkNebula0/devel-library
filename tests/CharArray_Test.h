#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

TEST_CASE( "Test char array length", "[CHAR_ARRAY_TEST]" ) {
    CCharArray<15> oCharArray;
    REQUIRE( oCharArray.length() ==0 );
    REQUIRE( oCharArray.maxLength()== 15 );
}

TEST_CASE( "Test char array value", "[CHAR_ARRAY_TEST]" ) {
    CCharArray<5> oCharArray;
    oCharArray = "Hello Word";

    REQUIRE( oCharArray.length() ==5 );
    REQUIRE( oCharArray.maxLength()== 5 );
    REQUIRE( oCharArray == "Hello" );
}
