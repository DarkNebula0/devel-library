#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "NEW_TIMER_IS_STOPPED", "[CORE_TIMER_TEST]" ) {
    CTimer oTimer;
    REQUIRE( oTimer.isStarted() == false);
}

TEST_CASE( "AUTO_START", "[CORE_TIMER_TEST]" ) {
    CTimer oTimer(true);
    REQUIRE( oTimer.isStarted() == true);
}

TEST_CASE( "ELAPSED_TIME", "[CORE_TIMER_TEST]" ) {
    CTimer oTimer(true);
    CTimer oTimer2(true);
    REQUIRE( oTimer.elapsed() <= 50);
    while (!oTimer2.hasExpired(50));

    const uint64 nTime = oTimer.elapsed();
    REQUIRE( oTimer.elapsed() >= 50);
    REQUIRE( oTimer.elapsed() <= 55);
}