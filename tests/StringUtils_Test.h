#include "Devel.h"
#include <catch.hpp>

using namespace Devel::StringUtils;
using namespace Catch;


TEST_CASE("Test Split function") {
    // Test splitting empty string
    std::vector<std::string> result = Split("", ' ');
    REQUIRE(result.size() == 0);

    // Test splitting string without delimiters
    result = Split("HelloWorld", ' ');
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == "HelloWorld");

    // Test splitting string with delimiters
    result = Split("Hello World Test", ' ');
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "Hello");
    REQUIRE(result[1] == "World");
    REQUIRE(result[2] == "Test");

    // Test splitting string with consecutive delimiters
    result = Split("Hello  World   Test", ' ');
    REQUIRE(result.size() == 6);
    REQUIRE(result[0] == "Hello");
    REQUIRE(result[2] == "World");
    REQUIRE(result[5] == "Test");

    // Test splitting string with delimiters at the start and end
    result = Split(" Hello World Test ", ' ');
    REQUIRE(result.size() == 5);
    REQUIRE(result[1] == "Hello");
    REQUIRE(result[2] == "World");
    REQUIRE(result[3] == "Test");
}

TEST_CASE("Test Join function") {
    // Test joining empty vector
    std::vector<std::string> input = {};
    std::string result = Join(input, ' ');
    REQUIRE(result == "");

    // Test joining vector of strings
    input = {"Hello", "World", "Test"};
    result = Join(input, ' ');
    REQUIRE(result == "Hello World Test");
}

TEST_CASE("Test Replace function") {
    // Test replacing character in empty string
    std::string result;
    Replace(result, 'a', 'b');
    REQUIRE(result.empty());


    // Test replacing character in string without the character
    result = "HelloWorld";
    result = Replace(result, 'a', 'b');
    REQUIRE(result == "HelloWorld");

    // Test replacing character in string with the character
    result = "HelloWorld";
    result = Replace(result, 'o', 'a');
    REQUIRE(result == "HellaWarld");
}

TEST_CASE("Test ToInt64 function") {
    // Test converting empty string
    long long result = ToInt64("");
    REQUIRE(result == 0);

    // Test converting string to int
    result = ToInt64("123");
    REQUIRE(result == 123);
}

TEST_CASE("Test ToUInt64 function") {
    // Test converting empty string
    unsigned long long result = ToUInt64("");
    REQUIRE(result == 0);

    // Test converting string to int
    result = ToUInt64("123");
    REQUIRE(result == 123);
}

TEST_CASE("Test ToInt function") {
    // Test converting empty string
    int result = ToInt("");
    REQUIRE(result == 0);

    // Test converting string to int
    result = ToInt("123");
    REQUIRE(result == 123);
}

TEST_CASE("Test ToUInt function") {
    // Test converting empty string
    unsigned int result = ToUInt("");
    REQUIRE(result == 0);

    // Test converting string to int
    result = ToUInt("123");
    REQUIRE(result == 123);
}

TEST_CASE("Test ToFloat function") {
    // Test converting empty string
    float result = ToFloat("");
    REQUIRE(result == Approx(0.0f));

    // Test converting string to float
    result = ToFloat("123.456");
    REQUIRE(result == Approx(123.456f));
}

TEST_CASE("Test ToDouble function") {
    // Test converting empty string
    double result = ToDouble("");
    REQUIRE(result == Approx(0.0));

    // Test converting string to double
    result = ToDouble("123.456");
    REQUIRE(result == Approx(123.456));
}

TEST_CASE("Test Contains function") {
    // Test searching in empty string
    bool result = Contains("", "test");
    REQUIRE(result == false);

    // Test searching string without the search term
    result = Contains("HelloWorld", "test");
    REQUIRE(result == false);

    // Test searching string with the search term
    result = Contains("HelloWorld", "World");
    REQUIRE(result == true);

    // Test case insensitive search
    result = Contains("HelloWorld", "world", false);
    REQUIRE(result == true);
}

TEST_CASE("Test ToArray function") {
    char dest[50];
    std::string source = "Hello, World!";

    Devel::StringUtils::ToArray(dest, source);
    REQUIRE(std::string(dest) == source);

    // resetting dest
    memset(dest, 0, sizeof(dest));

    const char *source_c_str = "Hello, World!";
    Devel::StringUtils::ToArray(dest, source_c_str);
    REQUIRE(std::string(dest) == source);
}

TEST_CASE("Test FromArray function") {
    const char source[50] = "Hello, World!";
    std::string result = Devel::StringUtils::FromArray(source);
    REQUIRE(result == std::string(source));
}

TEST_CASE("Test ToHex function") {
    int num = 170; // 0xaa in hexadecimal
    std::string result = Devel::StringUtils::ToHex(num);
    REQUIRE(result == "0xaa");
}

TEST_CASE("StringUtils functions are tested.", "[string-utils]") {

    SECTION("Repeat is tested") {
        std::string repeatedString = Repeat("Hello", 3);
        REQUIRE(repeatedString == "HelloHelloHello");
    }

    SECTION("ToLowerCopy is tested") {
        std::string lowerCopy = ToLowerCopy("Hello");
        REQUIRE(lowerCopy == "hello");
    }

    SECTION("ToLower is tested") {
        std::string str = "Hello";
        ToLower(str);
        REQUIRE(str == "hello");
    }

    SECTION("ToUpperCopy is tested") {
        std::string upperCopy = ToUpperCopy("Hello");
        REQUIRE(upperCopy == "HELLO");
    }

    SECTION("ToUpper is tested") {
        std::string str = "Hello";
        ToUpper(str);
        REQUIRE(str == "HELLO");
    }

    SECTION("Size is tested") {
        size_t size = Size("Hello", 10);
        REQUIRE(size == 5);
    }

    SECTION("Set is tested") {
        char destination[10] = {};
        Set(destination, "Hello", 5, 10);
        REQUIRE(strcmp(destination, "Hello") == 0);
    }

    SECTION("Get is tested") {
        char source[10] = "Hello";
        std::string got = Get(source, 10);
        REQUIRE(got == "Hello");
    }

    SECTION("Count is tested") {
        size_t count = Count("Hello, world!", ',');
        REQUIRE(count == 1);
    }

    SECTION("Replace is tested") {
        std::string replaced = Replace("Hello, world!", "world", "universe");
        REQUIRE(replaced == "Hello, universe!");
    }
    
    SECTION("Set with C-string is tested") {
        char destination[10] = {};
        Set(destination, "Hello", 10);
        REQUIRE(strcmp(destination, "Hello") == 0);
    }

    SECTION("Set with std::string is tested") {
        char destination[10] = {};
        Set(destination, std::string("Hello"), 10);
        REQUIRE(strcmp(destination, "Hello") == 0);
    }

}