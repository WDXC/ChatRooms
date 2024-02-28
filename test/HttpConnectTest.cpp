#include "gmock/gmock.h"
#include <chrono>
#include "HttpConnect.h"
#include "gtest/gtest.h"
#include <codecvt>
#include <thread>

using namespace testing;

class HttpConnectTest : public Test {
    public:
        std::shared_ptr<HttpConnect> root;
        void SetUp() {
            root->Init();
        }
        void TearDown() {root.reset();}
};

TEST_F(HttpConnectTest, InSureConnect) {
    //
}


int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
