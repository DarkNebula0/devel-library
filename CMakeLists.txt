# CMakeList.txt : CMake project for Library, include source and define
# project specific logic here.
#

project(Library)

cmake_minimum_required (VERSION 3.8)

## Packages
find_package(Boost 1.80.0 REQUIRED COMPONENTS random)
find_path(RANG_INCLUDE_DIRS "rang.hpp")

set(LIBRARY_HEADER "Devel.h")

set(LIBRARY_SRC
        "Core/Timer/Timer.cpp"
        "IO/Dir/Dir.cpp"
        "IO/Buffer/DynamicBuffer/DynamicBuffer.cpp"
        "Core/Logger/Logger.cpp"
)

add_library(Library ${LIBRARY_SRC} ${LIBRARY_HEADER})
set_property(TARGET Library PROPERTY CXX_STANDARD 20)
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LIBRARY_INCLUDE_DIR} ${RANG_INCLUDE_DIRS})
target_link_libraries(Library PRIVATE ${BOOST_LIBRARIES})
target_include_directories(Library PRIVATE ${Boost_INCLUDE_DIRS})


add_subdirectory(tests)