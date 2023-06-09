﻿# CMakeList.txt : CMake project for tests, include source and define
# project specific logic here.
#

project(tests)

cmake_minimum_required(VERSION 3.8)

Set(TEST_HEADER "")
Set(TEST_SRC "main.cpp")
set(TEST_INCLUDE_DIR "../")

find_package(Catch2 3 REQUIRED)
find_path(RANG_INCLUDE_DIRS "rang.hpp")

add_executable(lib-tests ${TEST_SRC} ${TEST_HEADER})
set_property(TARGET lib-tests PROPERTY CXX_STANDARD 20)
target_include_directories(lib-tests PUBLIC ${CMAKE_SOURCE_DIR} ${TEST_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${RANG_INCLUDE_DIRS})
target_link_libraries(lib-tests PRIVATE Library Catch2::Catch2WithMain)

# Coverage
option(CODE_COVERAGE "Enable coverage reporting" OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lib-tests PUBLIC -O0 -g --coverage)
    target_link_libraries(lib-tests PUBLIC --coverage)
endif ()

include(CTest)
include(Catch)
catch_discover_tests(lib-tests)

