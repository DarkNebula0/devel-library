#pragma once

#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("NEW_TIMER_IS_STOPPED", "[CORE_TIMER_TEST]") {
    CTimer oTimer;
    REQUIRE(oTimer.isStarted() == false);
}

TEST_CASE("AUTO_START", "[CORE_TIMER_TEST]") {
    CTimer oTimer(true);
    REQUIRE(oTimer.isStarted() == true);
}

TEST_CASE("ELAPSED_TIME", "[CORE_TIMER_TEST]") {
    CTimer oTimer(true);
    CTimer oTimer2(true);
    REQUIRE(oTimer.elapsed() <= 50);
    while (!oTimer2.hasExpired(50));

    const uint64 nTime = oTimer.elapsed();
    REQUIRE(oTimer.elapsed() >= 50);
    REQUIRE(oTimer.elapsed() <= 55);
}

TEST_CASE("CTimer Test", "[Timer]") {

    SECTION("Checking timer auto start") {
        Devel::CTimer timer(true);
        REQUIRE(timer.isStarted() == true);
    }

    SECTION("Checking timer manual start") {
        Devel::CTimer timer;
        timer.start();
        REQUIRE(timer.isStarted() == true);
    }

    SECTION("Checking timer clear and reset") {
        Devel::CTimer timer(true);
        timer.clear();
        REQUIRE(timer.isStarted() == false);

        timer.start();
        timer.reset();
        REQUIRE(timer.isStarted() == false);
    }

    SECTION("Checking timer elapsed time") {
        Devel::CTimer timer(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        REQUIRE(timer.elapsed() >= 50);
    }

    SECTION("Checking timer hasExpired function") {
        Devel::CTimer timer(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        REQUIRE(timer.hasExpired(40) == true);
        REQUIRE(timer.hasExpired(60) == false);
    }

    SECTION("Checking timer restart") {
        Devel::CTimer timer(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        timer.restart();
        REQUIRE(timer.elapsed() < 50);
    }
}