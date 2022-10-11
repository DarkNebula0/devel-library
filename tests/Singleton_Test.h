#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

class CSingletonTest : public CSingleton<CSingletonTest>
{
private:
    friend class CSingleton<CSingletonTest>;
public:
    CSingletonTest() = default;
    ~CSingletonTest() = default;
};

TEST_CASE( "UNIQUE", "[SINGLETON_TEST]" ) {
    REQUIRE( CSingletonTest::instance() == CSingletonTest::instance());
}