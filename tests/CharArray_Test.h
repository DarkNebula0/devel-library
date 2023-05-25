#pragma once

#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

TEST_CASE("TEST_CHARARRAY_LENGTH", "[CHAR_ARRAY_TEST]") {
    CCharArray<15> oCharArray;
    REQUIRE(oCharArray.length() == 0);
    REQUIRE(oCharArray.maxLength() == 15);
}

TEST_CASE("TEST_CHARARRAY_VALUE", "[CHAR_ARRAY_TEST]") {
    CCharArray<5> oCharArray;
    oCharArray = "Hello Word";

    REQUIRE(oCharArray.length() == 5);
    REQUIRE(oCharArray.maxLength() == 5);
    REQUIRE(oCharArray == "Hello");
}

TEST_CASE("CCharArray functions are tested.", "[cchararray]") {
    SECTION("Initialization, assignment and equality tests.") {
        constexpr size_t Size = 10;
        CCharArray<Size> arr1("Hello");
        CCharArray<Size> arr2("Hello");

        REQUIRE(arr1 == arr2);

        CCharArray<Size> arr3(arr1);

        REQUIRE(arr3 == arr1);

        CCharArray<Size> arr4;
        arr4 = arr1;

        REQUIRE(arr4 == arr1);
        REQUIRE(arr1.length() == 5);
        REQUIRE(arr1.maxLength() == Size);

        CCharArray<Size> arr5("World");
        REQUIRE(arr5 != arr1);
        REQUIRE(arr5.length() == 5);

        std::string str("Hello");
        REQUIRE(arr1 == str);
        REQUIRE(arr1 != "World");
    }

    SECTION("set() function tests.") {
        constexpr size_t Size = 10;
        CCharArray<Size> arr1;
        arr1.set("Test");
        REQUIRE(arr1 == "Test");

        CCharArray<Size> arr2("Hello");
        arr1.set(arr2);
        REQUIRE(arr1 == arr2);
    }

    SECTION("Testing iterator functions.") {
        constexpr size_t Size = 10;
        CCharArray<Size> arr1("Hello");
        REQUIRE(*arr1.begin() == 'H');
        REQUIRE(arr1.end() - arr1.begin() == 10);
    }

    SECTION("Testing element access functions.") {
        constexpr size_t Size = 10;
        CCharArray<Size> arr1("Hello");
        REQUIRE(arr1.first() == 'H');
        REQUIRE(arr1.last() == '\0');
        REQUIRE(arr1.at(4) == 'o');
    }

    SECTION("Testing toStdString() function.") {
        constexpr size_t Size = 10;
        CCharArray<Size> arr1("Hello");
        REQUIRE(arr1.toStdString() == "Hello");
    }
}