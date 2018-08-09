/*************************************************************************
    > File Name: ut_redis_conns.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 07:13:08 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "src/plugins/redis_conns/redis_conns.h"

using peleus::plugins::redis_conns::RedisConns;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtRedisConns :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        RedisConns::get_mutable_instance().init("./conf/redis_conns/");
    }
    virtual void TearDown() {}
protected:
    std::string _key = "test_redis_key";
    std::string _value = "test_redis_value";
};

TEST_F(UtRedisConns, Set) {
    std::stringstream ss;
    ss << "Set " << _key << " " << _value;
    std::string command = ss.str();

    std::string conn_name = "ksarch_offline_redis";
    brpc::RedisReply reply;
    bool result_set = RedisConns::get_mutable_instance().access(conn_name, command, reply);
    ASSERT_TRUE(result_set);
    ASSERT_FALSE(reply.is_error());
    ASSERT_STREQ("OK", reply.c_str());
}

TEST_F(UtRedisConns, Get) {
    std::stringstream ss;
    ss << "Get " << _key;
    std::string command = ss.str();

    std::string conn_name = "ksarch_offline_redis";
    brpc::RedisReply reply;
    bool result_set = RedisConns::get_mutable_instance().access(conn_name, command, reply);
    ASSERT_TRUE(result_set);
    ASSERT_FALSE(reply.is_error());
    ASSERT_TRUE(reply.is_string());
    ASSERT_STREQ(_value.c_str(), reply.c_str());
}

}
}
