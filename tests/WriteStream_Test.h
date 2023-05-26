#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel::IO;

TEST_CASE("CWriteStream Initialization", "[CWriteStream]") {
    SECTION("Default constructor") {
        CWriteStream writeStream;
        REQUIRE(writeStream.size() == 0);
        REQUIRE(writeStream.allocatedSize() == 0);
    }

    SECTION("Size constructor") {
        CWriteStream writeStream(100);
        REQUIRE(writeStream.size() == 0);
        REQUIRE(writeStream.allocatedSize() >= 100);
    }

    SECTION("Move constructor") {
        CWriteStream original(100);
        CWriteStream moved(std::move(original));
        REQUIRE(moved.size() == 0);
        REQUIRE(moved.allocatedSize() >= 100);
        REQUIRE(original.size() == 0);
        REQUIRE(original.allocatedSize() == 0);
    }
}

TEST_CASE("CWriteStream Functions", "[CWriteStream]") {
    SECTION("clear") {
        CWriteStream writeStream(100);
        writeStream.clear();
        REQUIRE(writeStream.size() == 0);
    }

    SECTION("push") {
        CWriteStream writeStream;
        std::string testString = "Test";
        writeStream.push(testString.c_str(), testString.size());
        REQUIRE(writeStream.size() == testString.size());
    }

    SECTION("reallocate") {
        CWriteStream writeStream;
        writeStream.reallocate(100);
        REQUIRE(writeStream.allocatedSize() >= 100);
    }

    SECTION("replace") {
        CWriteStream writeStream;
        std::string testString = "Test";
        writeStream.push(testString.c_str(), testString.size());
        std::string replaceString = "Best";
        writeStream.replace(0, replaceString.c_str(), replaceString.size());
        REQUIRE(writeStream.size() == testString.size());
    }
}
