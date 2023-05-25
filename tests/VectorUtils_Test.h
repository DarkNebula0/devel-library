#include "Devel.h"
#include <catch.hpp>

using namespace Devel::VectorUtils;
using namespace Catch;

TEST_CASE("VectorUtils functions are tested.", "[vector-utils]") {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    SECTION("IsDataInVector is tested with data present in vector") {
        int data = 3;
        size_t index = 0;
        bool isInVector = IsDataInVector(vec, data, &index);
        REQUIRE(isInVector == true);
        REQUIRE(index == 2);
    }

    SECTION("IsDataInVector is tested with data not present in vector") {
        int data = 6;
        size_t index = 0;
        bool isInVector = IsDataInVector(vec, data, &index);
        REQUIRE(isInVector == false);
    }

    SECTION("IsDataInVector is tested with data present in vector but without index") {
        int data = 4;
        bool isInVector = IsDataInVector(vec, data);
        REQUIRE(isInVector == true);
    }

    SECTION("IsDataInVector is tested with data not present in vector but without index") {
        int data = 7;
        bool isInVector = IsDataInVector(vec, data);
        REQUIRE(isInVector == false);
    }
}

TEST_CASE("IsDataInSortedVector returns correct results for various inputs", "[IsDataInSortedVector]") {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t index;

    SECTION("Check existing elements in vector") {
        REQUIRE(IsDataInSortedVector(vec, 1, &index));
        REQUIRE(index == 0);
        REQUIRE(IsDataInSortedVector(vec, 5, &index));
        REQUIRE(index == 4);
        REQUIRE(IsDataInSortedVector(vec, 9, &index));
        REQUIRE(index == 8);
    }

    SECTION("Check non-existing elements in vector") {
        REQUIRE_FALSE(IsDataInSortedVector(vec, 0, &index));
        REQUIRE_FALSE(IsDataInSortedVector(vec, 10, &index));
        REQUIRE_FALSE(IsDataInSortedVector(vec, -1, &index));
    }

    SECTION("Check elements without out index") {
        REQUIRE(IsDataInSortedVector(vec, 1));
        REQUIRE(IsDataInSortedVector(vec, 5));
        REQUIRE(IsDataInSortedVector(vec, 9));
        REQUIRE_FALSE(IsDataInSortedVector(vec, 0));
        REQUIRE_FALSE(IsDataInSortedVector(vec, 10));
        REQUIRE_FALSE(IsDataInSortedVector(vec, -1));
    }

    SECTION("Check with an empty vector") {
        std::vector<int> empty_vec;
        REQUIRE_FALSE(IsDataInSortedVector(empty_vec, 1, &index));
    }
}