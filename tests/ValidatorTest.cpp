#include <gtest/gtest.h>
#include "../FileValidator.h"

using namespace std;

TEST(ValidatorTests, ValidatorTest){

    string file = "core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4";
    EXPECT_TRUE(isValidLz4(file));
}

TEST(ValidatorTests, ValidatorTestNoCore){

    string file = "Bad.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4";
    EXPECT_FALSE(isValidLz4(file));
}

TEST(ValidatorTests, ValidatorTestNoService){

    string file = "core.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4";
    EXPECT_FALSE(isValidLz4(file));
}

TEST(ValidatorTests, ValidatorTestWrongExt){

    string file = "core.Bad.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz5";
    EXPECT_FALSE(isValidLz4(file));
}

TEST(ValidatorTests, ValidatorTestNoHexValues){

    string file = "core.Bad.lz4";
    EXPECT_FALSE(isValidLz4(file));
}

TEST(ValidatorTests, ValidatorTestEmpty){

    string file = "";
    EXPECT_FALSE(isValidLz4(file));
}
