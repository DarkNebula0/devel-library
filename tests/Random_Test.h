#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

TEST_CASE( "unique", "[Random]" ) {
    Random::Generate(15, 30);
    REQUIRE( Random::Generate(15, 30) != Random::Generate(15, 30));
}

TEST_CASE( "range", "[Random]" ) {
    REQUIRE( Random::Generate(15, 30) <= 30);
    REQUIRE( Random::Generate(15, 30) >= 14);
}