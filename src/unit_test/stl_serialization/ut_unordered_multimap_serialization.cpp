/*************************************************************************
    > File Name: ut_unordered_multimap_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:16:30 AM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/unordered_multimap_serialization.h"

using peleus::stl_serialization::UnorderedMultimapSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtUnorderedMultimapSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        UnorderedMultimapSerialization<int, int> ms_src;
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

TEST_F(UtUnorderedMultimapSerialization, SizeEq) {
    UnorderedMultimapSerialization<int, int> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    ASSERT_EQ(_size, ms_des.size());
}

TEST_F(UtUnorderedMultimapSerialization, FindEle) {
    // 因为unordered特性，序列化前后元素顺序是不一致的
    UnorderedMultimapSerialization<int, int> ms_des;
    std::istringstream ist(_ost.str());
    ms_des.unserialization(ist);
    for (int i = 0; i < _size; i++) {
        int range_index = i / _size_per_range;
        std::pair<std::unordered_multimap<int, int>::iterator,
            std::unordered_multimap<int, int>::iterator> ret;
        ret = ms_des.equal_range(range_index);
        bool find = false;
        for (std::unordered_multimap<int, int>::iterator it = ret.first; it != ret.second; it++) {
            if (it->second == i) {
                find = true;
                break;
            }
        }
        ASSERT_TRUE(find);
    }
}

}
}
