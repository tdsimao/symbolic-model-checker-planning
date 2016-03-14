#include "gtest/gtest.h"


TEST(DummySuite, Positive) {
    EXPECT_EQ(1, 1);
}
TEST(DummySuite, Negative) {
    EXPECT_EQ(1, 1);
}


TEST(Calculator, Sum) {
    EXPECT_EQ(1, 0+1);
}

TEST(Calculator, Multiply) {
    EXPECT_EQ(4, 2*2);
}
