#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

TEST_CASE( "RANGE", "[Random]" ) {
    REQUIRE( Random::Generate(15, 30) <= 30);
    REQUIRE( Random::Generate(15, 30) >= 14);
}

TEST_CASE( "TEST_UNIQUE_UUID", "[Random]" ) {
    REQUIRE( Random::GenerateUUID() != Random::GenerateUUID());
}

TEST_CASE( "TEST_UUID_STRUCTURE", "[Random]" ) {
    auto uuid = Random::GenerateUUID();
    REQUIRE( uuid.length() == 36);
    REQUIRE( uuid[8] == '-');
    REQUIRE( uuid[13] == '-');
    REQUIRE( uuid[18] == '-');
    REQUIRE( uuid[23] == '-');
    REQUIRE( uuid[14] == '4');
}