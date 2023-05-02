//int main(){return 0;}

#include <gtest/gtest.h>
#include <iostream>
#include "lib.h"

TEST(TEST_VER, CheckVersion) {
    EXPECT_EQ(version(), 1);
}
