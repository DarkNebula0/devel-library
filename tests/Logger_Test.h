#pragma once

#include "Devel.h"

#include <catch2/catch_test_macros.hpp>

using namespace Devel;

TEST_CASE("COLOR_TEST", "[CORE_LOGGER_TEST]") {
    Logging::Initialize();
    LOGE("RED ERROR TEXT ..........");
    LOGW("YELLOW WARNING TEXT ......");
    LOGI("Cyan INFO TEXT ..........");
    LOGD("Magenta DEBUG TEXT ......");
    REQUIRE(true);
}