/*************************************************************************
    > File Name: ut_map_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 11:11:46 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/map_serialization.h"

using peleus::stl_serialization::MapSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtMapSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        MapSerialization<int, std::string> ms_src;
        for (int i = 0; i < _size; i++) {
            ms_src[i] = " ";
        }
        ms_src.serialization(_ost);
    }
    virtual void TearDown() {}
protected:
    int _size = 10000;
    std::ostringstream _ost;
};

TEST_F(UtMapSerialization, SizeEq) {
    MapSerialization<int, std::string> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    ASSERT_EQ(_size, ms_des.size());
}

TEST_F(UtMapSerialization, ElemEq) {
    MapSerialization<int, std::string> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    int i = 0;
    for (std::map<int, std::string>::iterator it = ms_des.begin(); it != ms_des.end(); it++) {
        ASSERT_EQ(it->first, i++);
    }
}

}
}
