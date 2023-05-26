#include "Devel.h"
#include <catch.hpp>

using namespace Devel;

// Dummy class for testing purposes
class CDummy {
public:
    CDummy() : num(10) {}

    ~CDummy() {}

    int getNum() { return num; }

private:
    int num;
};

TEST_CASE("CObjectData tests") {
    SECTION("Constructor and assignment") {
        CObjectData data1 = CObjectData::get<CDummy>();
        CObjectData data2 = data1;

        REQUIRE(data1.size() == data2.size());
        REQUIRE(data1.hasVirtual() == data2.hasVirtual());
    }

    SECTION("Template methods") {
        CObjectData data = CObjectData::get<CDummy>();
        CDummy *obj = data.construct<CDummy>();

        REQUIRE(obj != nullptr);
        REQUIRE(obj->getNum() == 10);

        std::shared_ptr<CDummy> sharedObj = data.constructShared<CDummy>();

        REQUIRE(sharedObj != nullptr);
        REQUIRE(sharedObj->getNum() == 10);

        data.deconstruct(obj);
    }

    SECTION("Getters") {
        CObjectData data = CObjectData::get<CDummy>();

        REQUIRE(data.constructor() != nullptr);
        REQUIRE(data.constructorShared() != nullptr);
        REQUIRE(data.deconstructor() != nullptr);
        REQUIRE(data.size() == sizeof(CDummy));
        REQUIRE(data.hasVirtual() == std::has_virtual_destructor<CDummy>::value);
    }
}
