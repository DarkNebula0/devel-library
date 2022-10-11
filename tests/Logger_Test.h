#pragma once
#include "Devel.h"
#include "Core/Logger/Logger.cpp"
#include <catch2/catch_test_macros.hpp>

using namespace Devel;

TEST_CASE( "COLOR_TEST", "[CORE_LOGGER_TEST]" ) {
    Logger::Initialize();
    LOGE("RED ERROR TEXT ..........");
    LOGW("YELLOW WARNING TEXT ......");
    LOGI("Cyan INFO TEXT ..........");
    LOGD("Magenta DEBUG TEXT ......");
    REQUIRE(true);
}