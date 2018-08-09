/*************************************************************************
    > File Name: ut_unordered_map_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 11:37:32 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/unordered_map_serialization.h"

using peleus::stl_serialization::UnorderedMapSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtUnorderedMapSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        UnorderedMapSerialization<int, std::string> ms_src;
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

TEST_F(UtUnorderedMapSerialization, SizeEq) {
    UnorderedMapSerialization<int, std::string> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    ASSERT_EQ(_size, ms_des.size());
}

TEST_F(UtUnorderedMapSerialization, FindEle) {
    // 因为unordered特性，序列化前后元素顺序是不一致的
    UnorderedMapSerialization<int, std::string> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    for (int i = 0; i < _size; i++) {
        ASSERT_NE(ms_des.find(i), ms_des.end());
    }
}

}
}
