#include "EncapsluateJson.h"
#include "json_def.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "json_struct_def.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/stringbuffer.h"
#include "struct_def.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace testing;

class EncapsluateJsonTest : public Test {
public:
  std::shared_ptr<EncapsluateJson> root;
  void SetUp() {
    root = std::make_shared<EncapsluateJson>();
    root->InitRead(IntegerJson.c_str());
  }
  void TearDown() { root.reset(); }
};

// parse json
TEST_F(EncapsluateJsonTest, ParseJson_Number_Test) {
  int32_t positiveInteger = 0;
  root->parse("positiveInteger", positiveInteger);
  EXPECT_EQ(positiveInteger, 42);

  int32_t negativeInteger = 0;
  int32_t zero = 0;
  root->parse("negativeInteger", negativeInteger);
  root->parse("zero", zero);
  EXPECT_EQ(negativeInteger, -17);
  EXPECT_EQ(zero, 0);

  root.reset(new EncapsluateJson());
  root->InitRead(floatJson.c_str());
  float positiveFloat = 0.0;
  float negativeFloat = 0.0;
  float scientificNotation = 0.0;
  root->parse("positiveFloat", positiveFloat);
  root->parse("negativeFloat", negativeFloat);
  root->parse("scientificNotation", scientificNotation);
  EXPECT_FLOAT_EQ(positiveFloat, 3.14);
  EXPECT_FLOAT_EQ(negativeFloat, -0.01);
  EXPECT_FLOAT_EQ(scientificNotation, 2.5e6);

  root.reset(new EncapsluateJson());
  root->InitRead(MaxInt32ValueJson.c_str());
  int32_t int32MaxValue = 0;
  int32_t int32MinValue = 0;
  root->parse("maxValue", int32MaxValue);
  root->parse("minValue", int32MinValue);
  EXPECT_EQ(int32MaxValue, 2147483647);
  EXPECT_EQ(int32MinValue, -2147483648);

  root.reset(new EncapsluateJson());
  root->InitRead(MaxUint32ValueJson.c_str());
  uint32_t uint32MaxValue = 0;
  uint32_t uint32MinValue = 0;
  root->parse("maxValue", uint32MaxValue);
  root->parse("minValue", uint32MinValue);
  EXPECT_EQ(uint32MaxValue, 4294967295);
  EXPECT_EQ(uint32MinValue, 0);

  root.reset(new EncapsluateJson());
  root->InitRead(MaxDoubleVaueJson.c_str());
  double maxDoubleValue = 0.0;
  double minDoubleValue = 0.0;
  root->parse("maxValue", maxDoubleValue);
  root->parse("minValue", minDoubleValue);
  EXPECT_DOUBLE_EQ(maxDoubleValue, 1.7976931348623157e+308);
  EXPECT_DOUBLE_EQ(minDoubleValue, -1.7976931348623157e+308);

  root.reset(new EncapsluateJson());
  root->InitRead(SpecialValueJson.c_str());
  int32_t notANumber = 0;
  int32_t infinity = 0;
  root->parse("notANumber", notANumber);
  root->parse("infinity", infinity);
  EXPECT_EQ(notANumber, -1);
  EXPECT_EQ(infinity, -1);

  root.reset(new EncapsluateJson());
  root->InitRead(DecimalValueJson.c_str());
  float decimalPoint1 = 0.0;
  float decimalPoint2 = 0.0;
  root->parse("decimalPoint1", decimalPoint1);
  root->parse("decimalPoint2", decimalPoint2);
  EXPECT_FLOAT_EQ(decimalPoint1, 123.45);
  EXPECT_FLOAT_EQ(decimalPoint2, 1e5);
}

// generate json
TEST_F(EncapsluateJsonTest, Parse_String_Test) {
  root.reset(new EncapsluateJson());
  root->InitRead(basicCharacter.c_str());
  std::string stringWithAlphabets = "";
  root->parse("stringWithAlphabets", stringWithAlphabets);
  EXPECT_STREQ(stringWithAlphabets.c_str(), "HelloWorld");

  std::string stringWithNumbers = "";
  std::string stringWithSpaces = "";
  std::string stringWithSpecialChars = "";
  root->parse("stringWithNumbers", stringWithNumbers);
  root->parse("stringWithSpaces", stringWithSpaces);
  root->parse("stringWithSpecialChars", stringWithSpecialChars);
  EXPECT_STREQ(stringWithNumbers.c_str(), "123456");
  EXPECT_STREQ(stringWithSpaces.c_str(), "   This is a string with spaces   ");
  EXPECT_STREQ(stringWithSpecialChars.c_str(), "!@#$%^&*()_+");

  root.reset(new EncapsluateJson());
  root->InitRead(EscapeCharacter.c_str());
  std::string escapedDoubleQuote = "";
  std::string escapedBackslash = "";
  std::string newLineAndTab = "";
  root->parse("escapedDoubleQuote", escapedDoubleQuote);
  root->parse("escapedBackslash", escapedBackslash);
  root->parse("newLineAndTab", newLineAndTab);
  EXPECT_STREQ(escapedDoubleQuote.c_str(),
               "This is a string with escaped double quote: \"quoted\"");
  EXPECT_STREQ(escapedBackslash.c_str(),
               "This is a string with escaped backslash: C:\\path\\to\\file");
  EXPECT_STREQ(newLineAndTab.c_str(),
               "This is a string with new line and tab:\n\tNew Line\tTab");

  root.reset(new EncapsluateJson());
  root->InitRead(UnicodeCharacter.c_str());
  std::string unicodeString = "";
  root->parse("unicodeString", unicodeString);
  EXPECT_STREQ(unicodeString.c_str(), "This is a Unicode string: \u4F60\u597D");

  root.reset(new EncapsluateJson());
  root->InitRead(SpecialCharacter.c_str());
  std::string stringWithBackspace = "";
  root->parse("stringWithSpaces", stringWithBackspace);
  EXPECT_STREQ(stringWithBackspace.c_str(), "");

  root.reset(new EncapsluateJson());
  root->InitRead(EmptyCharacter.c_str());
  std::string emptyString = "";
  std::string stringWithEmptyQuotes = "";
  root->parse("emptyString", emptyString);
  root->parse("stringWithEmptyQuotes", stringWithEmptyQuotes);
  EXPECT_STREQ(emptyString.c_str(), "");
  EXPECT_STREQ(stringWithEmptyQuotes.c_str(), "");

  root.reset(new EncapsluateJson());
  root->InitRead(longSentenceCharacter.c_str());
  std::string longstring = "";
  root->parse("longstring", longstring);
  EXPECT_STREQ(longstring.c_str(), longString);
}

void CheckLoginStructs(const Login& actual, const Login & res){
    EXPECT_STREQ(actual.userid.c_str(), res.userid.c_str());
    EXPECT_STREQ(actual.password.c_str(), res.password.c_str());
}

TEST_F(EncapsluateJsonTest, Parse_Struct_Test) {
    root.reset(new EncapsluateJson());
    root->InitRead(ObjectLogin.c_str());
    Login login;
    root->parse_Login("test", login);
    CheckLoginStructs(login, Login("114514", "password"));
}

void CheckVectorLoginStructs(const std::vector<Login>& actual, const std::vector<Login>& res){
    if (actual.size() != res.size()) {
        EXPECT_EQ(actual.size(), res.size());
        return;
    }
    for (size_t i = 0; i < actual.size(); ++i) {
        EXPECT_STREQ(actual[i].password.c_str(), res[i].password.c_str());
        EXPECT_STREQ(actual[i].userid.c_str(), res[i].userid.c_str());
    }
}

TEST_F(EncapsluateJsonTest, Parse_Array_Test) {
    root.reset(new EncapsluateJson());
    root->InitRead(ArrayLogin.c_str());
    std::vector<Login> rv;
    root->parse_Login_array("test", rv);
    CheckVectorLoginStructs(rv, {{"114514", "password"}, {"222pp", "rootadmin"}});
}

TEST_F(EncapsluateJsonTest, Write_CommonType_Test) {
    std::string tmp;
    root.reset(new EncapsluateJson());
    root->InitWriter();
    int32_t age = 33;
    root->writeJson("intage", age);
    tmp = root->GetResultCharacters();
    root->InitRead(tmp.c_str());
    int32_t intage;
    root->parse("intage", intage);
    EXPECT_EQ(intage, age);


    root.reset(new EncapsluateJson());
    root->InitWriter();
    float floatage = 33.34;
    root->writeJson("floatage",floatage);
    tmp = root->GetResultCharacters();
    root->InitRead(tmp.c_str());
    float floatage_1;
    root->parse("floatage", floatage_1);
    EXPECT_FLOAT_EQ(floatage, floatage_1);

    root.reset(new EncapsluateJson());
    root->InitWriter();
    double doubleage = 33.234324324;
    root->writeJson("doubleage", doubleage);
    EXPECT_STREQ(root->GetResultCharacters().c_str(), doubleageString.c_str());
    tmp = root->GetResultCharacters();
    root->InitRead(tmp.c_str());
    double doubleage_1;
    root->parse("doubleage", doubleage_1);
    EXPECT_DOUBLE_EQ(doubleage, doubleage_1);


    root.reset(new EncapsluateJson());
    root->InitWriter();
    std::string stringage = "3334";
    root->writeJson("stringage", stringage);
    EXPECT_STREQ(root->GetResultCharacters().c_str(), stringageString.c_str());
    tmp = root->GetResultCharacters();
    EXPECT_STREQ(tmp.c_str(), stringageString.c_str());

}

TEST_F(EncapsluateJsonTest, Write_Object_Array_Test) {
    root.reset(new EncapsluateJson());
    root->InitWriter();
    rapidjson::Value object(rapidjson::kObjectType);
    root->AppendToObject("a", 1, object);
    root->AppendToObject("b", 2, object);
    root->AppendToObject("c", 3, object);
    root->writeObject("Object", object);
    EXPECT_STREQ(root->GetResultCharacters().c_str(), stringObject_22.c_str());

    root.reset(new EncapsluateJson());
    root->InitWriter();
    rapidjson::Value object_fir(rapidjson::kObjectType);
    rapidjson::Value object_array(rapidjson::kArrayType);
    root->AppendToObject("a", 1, object_fir);
    root->AppendToObject("b", 2, object_fir);
    root->AppendToObject("c", 3, object_fir);
    root->AppendToArray(object_fir, object_array);
    root->writeObject("Object22", object_array);

    EXPECT_STREQ(root->GetResultCharacters().c_str(), stringArray_33.c_str());
}


// error handle

// special symbo

// nested json struct

// memory leak and Performance

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
