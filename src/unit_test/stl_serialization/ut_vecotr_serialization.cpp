/*************************************************************************
    > File Name: ut_vecotr_serialization.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 21 Mar 2018 02:34:18 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "./src/stl_serialization/vector_serialization.h"

using peleus::stl_serialization::VectorSerialization;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

struct TestData {
    int interger;
    double db;
    float fl;
    std::string str;
private:  
    friend class boost::serialization::access;  

    template<class Archive>  
    void serialize(Archive& ar, const unsigned int version) {  
        ar & interger;
        ar & db;
        ar & fl;
        ar & str;
    }
};

class UtVectorSerialization :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        VectorSerialization<TestData> vs_src;
        for (int i = 0; i < _size; i++) {
            TestData item;
            item.interger = i;
            item.db = i;
            item.fl = i;
            item.str = std::to_string(i);
            vs_src.push_back(item);
        }
        vs_src.serialization(_ost);
    }
    virtual void TearDown() {}
protected:
    int _size = 10000;
    std::ostringstream _ost;
};

TEST_F(UtVectorSerialization, SizeEq) {
    VectorSerialization<TestData> vs_des;
    std::istringstream ist(_ost.str());
    vs_des.unserialization(ist);
    ASSERT_EQ(_size, vs_des.size());
}

TEST_F(UtVectorSerialization, ElemEq) {
    VectorSerialization<TestData> vs_des;
    std::istringstream ist(_ost.str());
    vs_des.unserialization(ist);
    for (int i = 0; i < _size; i++) {
        const TestData& item = vs_des.at(i);
        ASSERT_EQ(item.interger, i);
        ASSERT_DOUBLE_EQ(item.db, i);
        ASSERT_FLOAT_EQ(item.db, i);
        std::string str = std::to_string(i);
        ASSERT_STREQ(item.str.c_str(), str.c_str());
    }
}

}
}
