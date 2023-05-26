#include "Devel.h"
#include <catch2/catch_test_macros.hpp>

using namespace Devel::IO;

TEST_CASE("FORMAT", "[IO_PATH_TEST]") {
    CPath oPath("./");

    REQUIRE(oPath.toStdString() == "./");

    oPath.setPath("c:\\User\\Tree");

#ifdef _WIN32
    REQUIRE(oPath.toStdString() == "c:/User/Tree");
#else
    REQUIRE(oPath.toStdString() == "c:\\User\\Tree");
#endif

    oPath.setPath("c:\\User\\Tree/猫.txt");

#ifdef _WIN32
    REQUIRE(oPath.toStdString() == "c:/User/Tree/猫.txt");
#else
    REQUIRE(oPath.toStdString() == "c:\\User\\Tree/猫.txt");
#endif
}

TEST_CASE("EXTENSION", "[IO_PATH_TEST]") {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.toStdString() == "ABC.txt");
}

TEST_CASE("HAS_EXTENSION", "[IO_PATH_TEST]") {
    CPath oPath("ABC");
    REQUIRE_FALSE(oPath.hasExtension());

    oPath += ".txt";
    REQUIRE(oPath.hasExtension());
}

TEST_CASE("EXTENSION_REPLACE", "[IO_PATH_TEST]") {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.getFileExtension() == ".txt");

    oPath.replaceExtension(".png");
    REQUIRE(oPath.getFileExtension() == ".png");
}

TEST_CASE("FILENAME", "[IO_PATH_TEST]") {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.getFileNameWithoutExtension() == "ABC");
}

#ifndef _WIN32

TEST_CASE("HAS_FILENAME", "[IO_PATH_TEST]") {
    CPath oPath("testDir/");
    REQUIRE_FALSE(oPath.hasFilename());

    oPath += "ABC.txt";
    REQUIRE(oPath.hasFilename());

    oPath.removeFilename();
    REQUIRE_FALSE(oPath.hasFilename());
}

#endif

TEST_CASE("FILENAME_REPLACE", "[IO_PATH_TEST]") {
    CPath oPath("ABC.txt");
    REQUIRE(oPath.getFileNameWithoutExtension() == "ABC");

    oPath.replaceFilename("Tree");
    REQUIRE(oPath.getFileNameWithoutExtension() == "Tree");
}

TEST_CASE("EXISTS", "[IO_PATH_TEST]") {
    CPath oPath("ABC.txt");
    REQUIRE_FALSE(CPath::exists("C:/Tree/Tree1"));

}

TEST_CASE("CPath Tests", "[CPath]") {

    SECTION("CPath constructor and assignment operators") {
        fs::path fsPath("/test/path/file.txt");
        CPath path(fsPath);
        CPath pathCopy;
        pathCopy = path;
        REQUIRE(pathCopy.toStdString() == "/test/path/file.txt");

        CPath pathMove = std::move(path);
        REQUIRE(pathMove.toStdString() == "/test/path/file.txt");
    }

    SECTION("setPath") {
        CPath path;
        path.setPath("/test/path/file.txt");
        REQUIRE(path.toStdString() == "/test/path/file.txt");
    }

    SECTION("replaceFilename and replaceExtension") {
        CPath path("/test/path/file.txt");
        path.replaceFilename("new_file.txt");
        REQUIRE(path.toStdString() == "/test/path/new_file.txt");
        path.replaceExtension(".jpg");
        REQUIRE(path.toStdString() == "/test/path/new_file.jpg");
    }

    SECTION("various get methods") {
        CPath path("/test/path/file.txt");
        REQUIRE(path.getRootPath().string() == "/");
        REQUIRE(path.getParentPath().string() == "/test/path");
        REQUIRE(path.getFileNameWithoutExtension().string() == "file");
        REQUIRE(path.getFileExtension().string() == ".txt");
    }

    SECTION("removeFilename") {
        CPath path("/test/path/file.txt");
        path.removeFilename();
        REQUIRE(path.toStdString() == "/test/path/");
    }

    SECTION("toStdString and toStdWString") {
        CPath path("/test/path/file.txt");
        REQUIRE(path.toStdString() == "/test/path/file.txt");
        REQUIRE(path.toStdWString() == L"/test/path/file.txt");
    }

    SECTION("has methods") {
        CPath path("/test/path/file.txt");
        REQUIRE(path.hasFilename());
        REQUIRE(path.hasExtension());
    }

    SECTION("isAbsolutePath and isRelativePath") {

#ifdef _WIN32
        CPath path1("C:/test/path/file.txt");
#else
        CPath path1("/test/path/file.txt");
#endif
        CPath path2("test/path/file.txt");
        REQUIRE(path1.isAbsolutePath());
        REQUIRE_FALSE(path1.isRelativePath());
        REQUIRE_FALSE(path2.isAbsolutePath());
        REQUIRE(path2.isRelativePath());
    }

    SECTION("begin and end") {
        CPath path("/test/path/file.txt");
        std::vector<std::filesystem::path> elements(path.begin(), path.end());
        REQUIRE(elements[0] == "/");
        REQUIRE(elements[1] == "test");
        REQUIRE(elements[2] == "path");
        REQUIRE(elements[3] == "file.txt");
    }

    SECTION("operator+=") {
        CPath path("/test/path/");
        path += "file.txt";
        REQUIRE(path.toStdString() == "/test/path/file.txt");
    }
}