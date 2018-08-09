/*************************************************************************
    > File Name: ut_multiset_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:04:54 AM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/multiset_serialization.h"

using peleus::stl_serialization::MultisetSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtMultisetSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        MultisetSerialization<int> ss_src;
        for (int i = 0; i < _size; i++) {
            ss_src.insert(i / _size_per_range);
        }
        ss_src.serialization(_ost);
    }
    virtual void TearDown() {}
protected:
    int _size_per_range = 10;
    int _size = 10000;
    std::ostringstream _ost;
};

TEST_F(UtMultisetSerialization, SizeEq) {
    MultisetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    ASSERT_EQ(_size, ss_des.size());
}

TEST_F(UtMultisetSerialization, ElemEq) {
    MultisetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    int i = 0;
    for (std::multiset<int>::iterator it = ss_des.begin(); it != ss_des.end(); it++) {
        ASSERT_EQ(*it, i++ / _size_per_range);
    }
}

}
}
