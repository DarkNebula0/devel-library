#pragma once

#include <catch2/catch_test_macros.hpp>
#include "IO/JsonObject/JsonObject.h"
#include "IO/JsonDocument/JsonDocument.h"
#include "Serializing/Serializing.h"

static constexpr char k_szTestString[] = "{\n"
"  \"glossary\": {\n"
"    \"title\": \"example glossary\",\n"
"    \"GlossDiv\": {\n"
"      \"title\": \"S\",\n"
"      \"GlossList\": {\n"
"        \"GlossEntry\": {\n"
"          \"ID\": \"SGML\",\n"
"          \"SortAs\": \"SGML\",\n"
"          \"GlossTerm\": \"Standard Generalized Markup Language\",\n"
"          \"Acronym\": \"SGML\",\n"
"          \"Abbrev\": \"ISO 8879:1986\",\n"
"          \"GlossDef\": {\n"
"            \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",\n"
"            \"GlossSeeAlso\": [\n"
"              \"GML\",\n"
"              \"XML\"\n"
"            ]\n"
"          },\n"
"          \"GlossSee\": \"markup\"\n"
"        }\n"
"      }\n"
"    }\n"
"  }\n"
"}";

TEST_CASE("PARSE_VALID_JSON", "[IO_JSON_TEST]") {
    IO::CJsonDocument oJsonDocument;
    REQUIRE_NOTHROW(oJsonDocument.parse(k_szTestString));

    // Test object data
    IO::CJsonObject oGlossary = oJsonDocument.getObject("glossary");
    REQUIRE(oJsonDocument["glossary"]["title"] == "example glossary"); // Test object data

    REQUIRE(oGlossary.get("title") == "example glossary");
    REQUIRE(oGlossary.get("GlossDiv").get("title") == "S");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("ID") == "SGML");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("SortAs") == "SGML");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("GlossTerm") ==
            "Standard Generalized Markup Language");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("Acronym") == "SGML");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("Abbrev") == "ISO 8879:1986");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("GlossDef").get("para") ==
            "A meta-markup language, used to create markup languages such as DocBook.");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("GlossDef").get(
            "GlossSeeAlso").toArray()[0] == "GML");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("GlossDef").get(
            "GlossSeeAlso").toArray()[1] == "XML");
    REQUIRE(oGlossary.get("GlossDiv").get("GlossList").get("GlossEntry").get("GlossSee") == "markup");
}

TEST_CASE("PARSE_INVALID_JSON", "[IO_JSON_TEST]") {
    IO::CJsonDocument oJsonDocument;

    // js object invalid key
    REQUIRE_THROWS(oJsonDocument.parse("{ test : \"test\" }"));

    // missing start bracket
    REQUIRE_THROWS(oJsonDocument.parse(" \"test\" : \"test\" }"));

    // missing colon
    REQUIRE_THROWS(oJsonDocument.parse("{ \"test\"  \"test\" }"));

    // empty string
    REQUIRE_THROWS(oJsonDocument.parse(""));
}

TEST_CASE("MINIFIED_LENGTH", "[IO_JSON_TEST]") {
    IO::CJsonDocument oJsonDocument;
    REQUIRE_NOTHROW(oJsonDocument.parse(k_szTestString));
    REQUIRE(oJsonDocument.serialize(false).length() == 360);
}

#pragma pack(push, 1)
namespace JsonModel {
	using namespace Serializing;

	struct GlossDef {
		IJsonString para = JsonFieldName("para");
		IJsonArray<IString<>> glossSeeAlso = JsonFieldName("GlossSeeAlso");
	};

	struct GlossEntry {
		IJsonString id = JsonFieldName("ID");
		IJsonString sortAs = JsonFieldName("SortAs");
		IJsonString glossTerm = JsonFieldName("GlossTerm");
		IJsonString acronym = JsonFieldName("Acronym");
		IJsonString abbrev = JsonFieldName("Abbrev");
		IJsonString glossSee = JsonFieldName("GlossSee");
		IJsonStruct<GlossDef> glossDef = JsonFieldName("GlossDef");
	};

	struct GlossList {
		IJsonStruct<GlossEntry> glossEntry = JsonFieldName("GlossEntry");
	};

	struct GlossDiv {
		IJsonString title = JsonFieldName("title");
		IJsonStruct<GlossList> glossList = JsonFieldName("GlossList");
	};

	struct Glossary {
		IJsonString title = JsonFieldName("title");
		IJsonStruct<GlossDiv> glossDiv = JsonFieldName("GlossDiv");
	};

	struct GlossaryOnlyTitle {
		IJsonString title = JsonFieldName("title");
	};

	struct RootModel {
		IJsonStruct<Glossary> glossary = JsonFieldName("glossary");
	};

	struct RootModelOnlyTitle {
		IJsonStruct<GlossaryOnlyTitle> glossary = JsonFieldName("glossary");
	};

	struct Test {
		IJsonArray<IString<>> glossSeeAlso = JsonFieldName("GlossSeeAlso");
	};

}
#pragma pack(pop)

TEST_CASE("DESERIALIZE_JSON_DOCUMENT", "[IO_JSON_TEST]") {
    IO::CJsonDocument oJsonDocument;
    REQUIRE_NOTHROW(oJsonDocument.parse(k_szTestString));

    REQUIRE(oJsonDocument["glossary"]["title"] == "example glossary"); // Test object data

    JsonModel::RootModel rootModel;
    REQUIRE_NOTHROW(Serializing::DeserializeDocument<JsonModel::RootModel>(rootModel, oJsonDocument, true));
    REQUIRE(rootModel.glossary->title == "example glossary");
    REQUIRE(rootModel.glossary->glossDiv->title == "S");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->id == "SGML");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->sortAs == "SGML");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->glossTerm == "Standard Generalized Markup Language");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->acronym == "SGML");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->abbrev == "ISO 8879:1986");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->glossSee == "markup");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->para ==
            "A meta-markup language, used to create markup languages such as DocBook.");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->glossSeeAlso->size() == 2);
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->glossSeeAlso[0] == "GML");
    REQUIRE(rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->glossSeeAlso[1] == "XML");
}

TEST_CASE("DESERIALIZE_MIXED_ARRAY", "[IO_JSON_TEST]") {
    IO::CJsonDocument oJsonDocument;
    REQUIRE_NOTHROW(oJsonDocument.parse("{\"test\": [1, \"test\", 2.5, true, false, null]}"));

#pragma pack(push, 1)
    struct Test {
        Serializing::IJsonArray<IO::CJsonObject> test = JsonFieldName("test");
    };
#pragma pack(pop)

    Test rootModel;
    REQUIRE_NOTHROW(Serializing::DeserializeDocument<Test>(rootModel, oJsonDocument, true));
    REQUIRE(rootModel.test->size() == 6);
    REQUIRE(rootModel.test[0].toInt() == 1);
    REQUIRE(rootModel.test[1] == "test");
    REQUIRE(rootModel.test[2].toDouble() == 2.5);
    REQUIRE(rootModel.test[3].toBool() == true);
    REQUIRE(rootModel.test[4].toBool() == false);
    REQUIRE(rootModel.test[5].isNull() == true);
}

TEST_CASE("SERIALIZE_JSON_DOCUMENT", "[IO_JSON_TEST]") {

	JsonModel::RootModel rootModel;

	rootModel.glossary->title = "example glossary";
	rootModel.glossary->glossDiv->title = "S";
	rootModel.glossary->glossDiv->glossList->glossEntry->id = "SGML";
	rootModel.glossary->glossDiv->glossList->glossEntry->sortAs = "SGML";
	rootModel.glossary->glossDiv->glossList->glossEntry->glossTerm = "Standard Generalized Markup Language";
	rootModel.glossary->glossDiv->glossList->glossEntry->acronym = "SGML";
	rootModel.glossary->glossDiv->glossList->glossEntry->abbrev = "ISO 8879:1986";
	rootModel.glossary->glossDiv->glossList->glossEntry->glossSee = "markup";
	rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->para = "A meta-markup language, used to create markup languages such as DocBook.";
	rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->glossSeeAlso->push_back("GML");
	rootModel.glossary->glossDiv->glossList->glossEntry->glossDef->glossSeeAlso->push_back("XML");

	IO::CJsonDocument oJsonDocument;

	REQUIRE_NOTHROW(Serializing::SerializeDocument(rootModel, oJsonDocument, true));

	REQUIRE(oJsonDocument.serialize(false).length() == 360);
}



