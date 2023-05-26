#pragma once

#include "Devel.h"
#include <catch2/catch_test_macros.hpp>
#include <regex>

using namespace Devel;

TEST_CASE("RANGE", "[Random]") {
    REQUIRE(Random::Generate(15, 30) <= 30);
    REQUIRE(Random::Generate(15, 30) >= 14);
}

TEST_CASE("TEST_UNIQUE_UUID", "[Random]") {
    REQUIRE(Random::GenerateUUID() != Random::GenerateUUID());
}

TEST_CASE("TEST_UUID_STRUCTURE", "[Random]") {
    auto uuid = Random::GenerateUUID();
    REQUIRE(uuid.length() == 36);
    REQUIRE(uuid[8] == '-');
    REQUIRE(uuid[13] == '-');
    REQUIRE(uuid[18] == '-');
    REQUIRE(uuid[23] == '-');
    REQUIRE(uuid[14] == '4');
}

TEST_CASE("Random Number Generation Test", "[Random]") {

    SECTION("Generating int within range") {
        int randomInt = Devel::Random::Generate<int>(1, 10);
        REQUIRE(randomInt >= 1);
        REQUIRE(randomInt <= 10);

    }SECTION("Generating same min max") {
        int randomInt = Devel::Random::Generate<int>(10, 10);
        REQUIRE(randomInt == 10);
    }
}

TEST_CASE("UUID Generation Test", "[Random]") {
    std::string uuid = Devel::Random::GenerateUUID();

    SECTION("Checking UUID length") {
        REQUIRE(uuid.length() == 36);
    }

    SECTION("Checking UUID format") {
        std::regex uuidFormat("^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");
        REQUIRE(std::regex_match(uuid, uuidFormat));
    }
}