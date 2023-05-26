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
    }SECTION("Constructor from std::string") {
        std::string str = "example string";
        CCharArray<50> arr(str);

        REQUIRE(strcmp(arr.c_str(), str.c_str()) == 0);
    }

    SECTION("Constructor from initializer_list") {
        CCharArray<50> arr({'e', 'x', 'a', 'm', 'p', 'l', 'e'});

        REQUIRE(strcmp(arr.c_str(), "example") == 0);
    }

    SECTION("Constructor from other CCharArray") {
        CCharArray<50> arr1("example string");
        CCharArray<50> arr2(arr1);

        REQUIRE(strcmp(arr2.c_str(), arr1.c_str()) == 0);
    }

    SECTION("Set from std::string") {
        CCharArray<50> arr;
        arr.set("example string");

        REQUIRE(strcmp(arr.c_str(), "example string") == 0);
    }

    SECTION("Set from other CCharArray") {
        CCharArray<50> arr1("example string");
        CCharArray<50> arr2;
        arr2.set(arr1);

        REQUIRE(strcmp(arr2.c_str(), arr1.c_str()) == 0);
    }

    SECTION("Begin and End") {
        CCharArray<50> arr("example string");

        REQUIRE(*arr.begin() == 'e');
        REQUIRE(*(arr.end() - 1) == '\0');
    }

    SECTION("First and Last") {
        CCharArray<50> arr("example string");

        REQUIRE(arr.first() == 'e');
        REQUIRE(arr.last() == '\0');
    }

    SECTION("At") {
        CCharArray<50> arr("example string");
        REQUIRE(arr.at(6) == 'e');
    }

    SECTION("Operator =") {
        CCharArray<50> arr1;
        CCharArray<50> arr2("example string");
        arr1 = arr2;

        REQUIRE(strcmp(arr1.c_str(), arr2.c_str()) == 0);

        std::string str = "new string";
        arr1 = str;

        REQUIRE(strcmp(arr1.c_str(), str.c_str()) == 0);
    }

    SECTION("Operator ==") {
        CCharArray<50> arr1("example string");
        CCharArray<50> arr2(arr1);

        REQUIRE((arr1 == arr2));
    }

    SECTION("Operator !=") {
        CCharArray<50> arr1("example string");
        CCharArray<50> arr2("different string");

        REQUIRE((arr1 != arr2));

        std::string str = "new string";
        REQUIRE((arr1 != str));
    }

    SECTION("Cast to char*") {
        CCharArray<50> arr("example string");
        char *cstr = arr;

        REQUIRE(strcmp(cstr, arr.c_str()) == 0);
    }

    SECTION("Cast to const char*") {
        CCharArray<50> arr("example string");
        const char *cstr = arr;

        REQUIRE(strcmp(cstr, arr.c_str()) == 0);
    }
}