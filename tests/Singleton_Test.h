#pragma once

#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

class CSingletonTest : public CSingleton<CSingletonTest> {
private:
    friend class CSingleton<CSingletonTest>;

public:
    CSingletonTest() = default;

    ~CSingletonTest() = default;

public:
    int testValue = 0;
};

TEST_CASE("UNIQUE", "[SINGLETON_TEST]") {
    REQUIRE(CSingletonTest::instance() == CSingletonTest::instance());
}

TEST_CASE("Singleton Behavior Test", "[Singleton]") {
    SECTION("Checking instance creation") {
        CSingletonTest *instance = CSingletonTest::instance();
        REQUIRE(instance != nullptr);
    }

    SECTION("Checking instance uniqueness") {
        CSingletonTest *firstInstance = CSingletonTest::instance();
        CSingletonTest *secondInstance = CSingletonTest::instance();
        REQUIRE(firstInstance == secondInstance);
    }

    SECTION("Checking Singleton property modification") {
        REQUIRE(CSingletonTest::instance()->testValue == 0);
        CSingletonTest::instance()->testValue = 123;
        REQUIRE(CSingletonTest::instance()->testValue == 123);
    }
}