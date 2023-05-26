#pragma once

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "Serializing/Serializing.h"


TEST_CASE("SERIALIZE_AND_DESERIALIZE_STRUCT", "[IO_SERIALIZE_TEST]") {

#pragma pack(push, 1)
    struct TestStructVirtual : Serializing::IStruct {
        virtual ~TestStructVirtual() {
            std::cout << "virtual destructor" << std::endl;
        }

        Serializing::IInt<> iGold;
        Serializing::IString<> sName;
    };

    struct TestStruct : Serializing::IStruct {
        Serializing::IInt<> iGold;
        Serializing::IString<> sName;
    };
#pragma pack(pop)

    TestStructVirtual testStructVirtual;
    testStructVirtual.iGold = 100;
    testStructVirtual.sName = "test";

    CWriteStream oStream(100);
    Serializing::SerializeStream(testStructVirtual, oStream);

    TestStruct deserialized;
    TestStruct deserializedTestStructVirtual;
    CReadStream oStreamRead(oStream.buffer(), oStream.size(), false);
    REQUIRE_NOTHROW(Serializing::DeserializeStream(deserialized, oStreamRead));
    REQUIRE_NOTHROW(oStreamRead.setPosition(0));
    REQUIRE_NOTHROW(Serializing::DeserializeStream(deserializedTestStructVirtual, oStreamRead));

    REQUIRE(deserialized.iGold.value() == 100);
    REQUIRE(deserialized.sName == "test");
    REQUIRE(deserializedTestStructVirtual.iGold.value() == 100);
    REQUIRE(deserializedTestStructVirtual.sName == "test");

}