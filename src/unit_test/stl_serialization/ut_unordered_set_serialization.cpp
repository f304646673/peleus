/*************************************************************************
    > File Name: ut_unordered_set_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:49:32 AM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/unordered_set_serialization.h"

using peleus::stl_serialization::UnorderedSetSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtUnorderedSetSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        UnorderedSetSerialization<int> ss_src;
        for (int i = 0; i < _size; i++) {
            ss_src.insert(i);
        }
        ss_src.serialization(_ost);
    }
    virtual void TearDown() {}
protected:
    int _size = 10000;
    std::ostringstream _ost;
};

TEST_F(UtUnorderedSetSerialization, SizeEq) {
    UnorderedSetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    ASSERT_EQ(_size, ss_des.size());
}

TEST_F(UtUnorderedSetSerialization, ElemEq) {
    UnorderedSetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    for (int i = 0; i < _size; i++) {
        ASSERT_NE(ss_des.find(i), ss_des.end());
    }
}

}
}
