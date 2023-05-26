#include "Devel.h"
#include <catch.hpp>

TEST_CASE("CDynamicBuffer Tests", "[CDynamicBuffer]") {

    SECTION("Default constructor") {
        Devel::IO::CDynamicBuffer buffer;
        REQUIRE(buffer.size() == 0);
        REQUIRE(buffer.allocatedSize() == 0);
    }

    SECTION("Size constructor") {
        Devel::IO::CDynamicBuffer buffer(10);
        REQUIRE(buffer.size() == 0);
        REQUIRE(buffer.allocatedSize() >= 10);
    }

    SECTION("Copy constructor") {
        Devel::IO::CDynamicBuffer original(10);
        Devel::IO::CDynamicBuffer copy(original);
        REQUIRE(copy.size() == original.size());
        REQUIRE(copy.allocatedSize() == original.allocatedSize());
    }

    SECTION("Move constructor") {
        Devel::IO::CDynamicBuffer original(10);
        Devel::IO::CDynamicBuffer moved(std::move(original));
        REQUIRE(moved.size() == 0);
        REQUIRE(moved.allocatedSize() >= 10);
        REQUIRE(original.size() == 0);
        REQUIRE(original.allocatedSize() == 0);
    }

    SECTION("Assignment operators") {
        Devel::IO::CDynamicBuffer original(10);
        Devel::IO::CDynamicBuffer assigned;
        assigned = original;
        REQUIRE(assigned.size() == original.size());
        REQUIRE(assigned.allocatedSize() == original.allocatedSize());

        Devel::IO::CDynamicBuffer moved;
        moved = std::move(original);
        REQUIRE(moved.size() == 0);
        REQUIRE(moved.allocatedSize() >= 10);
        REQUIRE(original.size() == 0);
        REQUIRE(original.allocatedSize() == 0);
    }

    SECTION("Reallocate method") {
        Devel::IO::CDynamicBuffer buffer;
        buffer.reallocate(20);
        REQUIRE(buffer.size() == 0);
        REQUIRE(buffer.allocatedSize() >= 20);
    }

    SECTION("Index operator") {
        Devel::IO::CDynamicBuffer buffer;
        REQUIRE_THROWS_AS(buffer[0], std::logic_error);
        buffer.reallocate(10);
        REQUIRE_NOTHROW(buffer[0]);
        REQUIRE_THROWS_AS(buffer[10], std::range_error);
    }
}