#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel::IO;

TEST_CASE("Testing CReadStream functionality", "[CReadStream]") {
    SECTION("CReadStream default constructor") {
        CReadStream readStream;
        REQUIRE(readStream.size() == 0);
        REQUIRE(readStream.position() == 0);
        REQUIRE(readStream.buffer() == nullptr);
    }

    SECTION("CReadStream custom constructor with buffer copy") {
        const char *testBuffer = "test";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        REQUIRE(readStream.size() == strlen(testBuffer));
        REQUIRE(readStream.buffer() != testBuffer);
    }

    SECTION("Testing setBuffer function") {
        CReadStream readStream;
        const char *testBuffer = "testing setBuffer";
        readStream.setBuffer(testBuffer, strlen(testBuffer), true);
        REQUIRE(readStream.size() == strlen(testBuffer));
        REQUIRE(readStream.buffer() != testBuffer);
    }

    SECTION("Testing getRaw function") {
        const char *testBuffer = "testing getRaw";
        CReadStream readStream(testBuffer, strlen(testBuffer) + 1, true);
        char *destination = new char[strlen(testBuffer) + 1];
        readStream.getRaw(destination, strlen(testBuffer) + 1);
        REQUIRE(strcmp(destination, testBuffer) == 0);
        delete[] destination;
    }

    SECTION("Testing getString function") {
        const char *testBuffer = "testing getString";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        std::string result = readStream.getString(strlen(testBuffer), false);
        REQUIRE(result == testBuffer);  // Should be the same
    }

    SECTION("Testing assignment operator") {
        const char *testBuffer = "testing operator=";
        CReadStream readStream1(testBuffer, strlen(testBuffer) + 1, true);
        CReadStream readStream2 = readStream1;
        REQUIRE(readStream2.size() == readStream1.size());
        REQUIRE(readStream2.position() == readStream1.position());
        REQUIRE(strcmp(readStream2.buffer(), readStream1.buffer()) == 0);  // Should be the same
    }

    SECTION("Testing isEoB function at start of buffer") {
        const char *testBuffer = "testing isEoB";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        REQUIRE(readStream.isEoB() == false);
    }

    SECTION("Testing isEoB function at end of buffer") {
        const char *testBuffer = "testing isEoB";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        readStream.seek(strlen(testBuffer));  // Seek to the end of the buffer
        REQUIRE(readStream.isEoB() == true);
    }

    SECTION("Testing seek function") {
        const char *testBuffer = "testing seek";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        size_t targetPosition = strlen(testBuffer) / 2;
        readStream.seek(targetPosition);
        REQUIRE(readStream.position() == targetPosition);
    }

    SECTION("Testing reset function") {
        const char *testBuffer = "testing reset";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        readStream.seek(strlen(testBuffer) / 2);  // Move to the middle of the buffer
        readStream.setPosition(0);
        REQUIRE(readStream.position() == 0);  // Position should be reset to 0
    }

    SECTION("Testing get function") {
        const char *testBuffer = "testing get";
        CReadStream readStream(testBuffer, strlen(testBuffer), true);
        char gotten = readStream.get<char>();
        REQUIRE(gotten == testBuffer[0]);  // Get should return the first character
        REQUIRE(readStream.position() == 1);  // Position should increase by 1 after get
    }
}