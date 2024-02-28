#include "gmock/gmock.h"
#include "http_test_def.h"
#include "HttpParse.h"
#include "gtest/gtest.h"

using namespace testing;

class HttpParseTest: public Test {
public:
  std::shared_ptr<HttpParse> root;
  void SetUp() {
      root->init();
  }
  void TearDown() { root.reset(); }
};

TEST_F(HttpParseTest, RequestMethod) {
    root->parserAddr(get_request_string.c_str());
}


int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
