#pragma once
#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel::IO;

TEST_CASE( "FORMAT", "[IO_PATH_TEST]" ) {
    CPath oPath("./");

    REQUIRE( oPath.toStdString() == "./");

    oPath.setPath("c:\\User\\Tree");

#ifdef _WIN32
    REQUIRE( oPath.toStdString() == "c:/User/Tree");
#else
    REQUIRE(oPath.toStdString() == "c:\\User\\Tree");
#endif

    oPath.setPath("c:\\User\\Tree/猫.txt");

#ifdef _WIN32
    REQUIRE( oPath.toStdString() == "c:/User/Tree/猫.txt");
#else
    REQUIRE( oPath.toStdString() == "c:\\User\\Tree/猫.txt");
#endif
}

TEST_CASE( "EXTENSION", "[IO_PATH_TEST]" ) {
    CPath oPath("ABC.txt");
    REQUIRE( oPath.toStdString() == "ABC.txt");
}

TEST_CASE( "HAS_EXTENSION", "[IO_PATH_TEST]" ) {
    CPath oPath("ABC");
    REQUIRE_FALSE(oPath.hasExtension());

    oPath += ".txt";
    REQUIRE(oPath.hasExtension());
}

TEST_CASE( "EXTENSION_REPLACE", "[IO_PATH_TEST]" ) {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.getFileExtension() == ".txt");

    oPath.replaceExtension(".png");
    REQUIRE(oPath.getFileExtension() == ".png");
}

TEST_CASE( "FILENAME", "[IO_PATH_TEST]" ) {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.getFileNameWithoutExtension() == "ABC");
}

#ifndef _WIN32
TEST_CASE( "HAS_FILENAME", "[IO_PATH_TEST]" ) {
    CPath oPath("testDir/");
    REQUIRE_FALSE(oPath.hasFilename());

    oPath += "ABC.txt";
    REQUIRE(oPath.hasFilename());

    oPath.removeFilename();
    REQUIRE_FALSE(oPath.hasFilename());
}
#endif

TEST_CASE( "FILENAME_REPLACE", "[IO_PATH_TEST]" ) {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.getFileNameWithoutExtension() == "ABC");

    oPath.replaceFilename("Tree");
    REQUIRE(oPath.getFileNameWithoutExtension() == "Tree");
}

TEST_CASE( "EXISTS", "[IO_PATH_TEST]" ) {
    CPath oPath("ABC.txt");
    REQUIRE_FALSE(CPath::exists("C:/Tree/Tree1"));

}