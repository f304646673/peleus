/*************************************************************************
    > File Name: ut_set_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 07:13:08 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/set_serialization.h"

using peleus::stl_serialization::SetSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtSetSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        SetSerialization<int> ss_src;
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

TEST_F(UtSetSerialization, SizeEq) {
    SetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    ASSERT_EQ(_size, ss_des.size());
}

TEST_F(UtSetSerialization, ElemEq) {
    SetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    int i = 0;
    for (std::set<int>::iterator it = ss_des.begin(); it != ss_des.end(); it++) {
        ASSERT_EQ(*it, i++);
    }
}

}
}
