/*************************************************************************
    > File Name: ut_multimap_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 12:48:55 AM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/multimap_serialization.h"

using peleus::stl_serialization::MultimapSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtMultimapSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        MultimapSerialization<int, int> ms_src;
        for (int i = 0; i < _size; i++) {
            ms_src.insert(std::pair<int, int>(i / _size_per_range, i));
        }
        ms_src.serialization(_ost);
    }
    virtual void TearDown() {}
protected:
    int _size_per_range = 100;
    int _size = 10000;
    std::ostringstream _ost;
};

TEST_F(UtMultimapSerialization, SizeEq) {
    MultimapSerialization<int, int> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    ASSERT_EQ(_size, ms_des.size());
}

TEST_F(UtMultimapSerialization, ElemEq) {
    MultimapSerialization<int, int> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    int i = 0;
    for (std::multimap<int, int>::iterator it = ms_des.begin(); it != ms_des.end(); it++) {
        ASSERT_EQ(it->second, i++);
    }
}

}
}
