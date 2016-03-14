#include "gtest/gtest.h"
#include "smcp.h"


//class SymbolicActionTest : public ::testing::Test {
//
//protected:
//
//    virtual void SetUp() {
//        a1 = SymbolicAction("a1");
//        a2 = SymbolicAction("a2");
//
//
//    }
////    virtual void TearDown(){  }
//    SymbolicAction a1;
//    SymbolicAction a2;
//
//};
//
//
//TEST_F(SymbolicActionTest, GetName) {
//    EXPECT_EQ("a1", a1.name());
//    EXPECT_EQ("a2", a2.name());
//}



// The fixture for testing class Foo.
class SymbolicActionTest : public ::testing::Test {

    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

//    SymbolicActionTest() {
//            // You can do set-up work for each test here.
//        }

//        virtual ~FooTest() {
//            // You can do clean-up work that doesn't throw exceptions here.
//        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        virtual void SetUp() {
            a1 = SymbolicAction("a1");
            a2 = SymbolicAction();
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

//    // Objects declared here can be used by all tests in the test case for Foo.
    SymbolicAction a1;
    SymbolicAction a2;



};

TEST_F(SymbolicActionTest, ConstructorWithName) {
    EXPECT_EQ("a1", a1.name());
}
TEST_F(SymbolicActionTest, ConstructorWithoutName) {
    EXPECT_EQ("", a2.name());
}
//SymbolicAction SymbolicActionTest::a1= SymbolicAction("");
//SymbolicAction SymbolicActionTest::a2= SymbolicAction("");



