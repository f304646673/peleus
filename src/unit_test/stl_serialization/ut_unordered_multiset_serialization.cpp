/*************************************************************************
    > File Name: ut_unordered_multiset_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:54:07 AM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/unordered_multiset_serialization.h"

using peleus::stl_serialization::UnorderedMultisetSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtUnorderedMultisetSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        UnorderedMultisetSerialization<int> ss_src;
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

TEST_F(UtUnorderedMultisetSerialization, SizeEq) {
    UnorderedMultisetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    ASSERT_EQ(_size, ss_des.size());
}

TEST_F(UtUnorderedMultisetSerialization, ElemEq) {
    UnorderedMultisetSerialization<int> ss_des;
    std::istringstream ist(_ost.str());
    ss_des.unserialization(ist);
    for (int i = 0; i < _size; i++) {
        int range_index = i / _size_per_range;
        std::pair<std::unordered_set<int>::iterator, std::unordered_set<int>::iterator> ret;
        ret = ss_des.equal_range(range_index);
        int size_per_range = 0;
        for (std::unordered_set<int>::iterator it = ret.first; it != ret.second; it++) {
            size_per_range++;
        }
        ASSERT_EQ(size_per_range, _size_per_range);
    }
}

}
}
