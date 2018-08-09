/*************************************************************************
    > File Name: ut_mysql_conns.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 02 May 2018 01:34:28 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "src/plugins/mysql_conns/mysql_conns.h"

using peleus::plugins::mysql_conns::MysqlConns;
using peleus::plugins::mysql_conns::MysqlSession;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtMysqlConns :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        MysqlConns::get_mutable_instance().init("./conf/mysql_conns/");
    }
    virtual void TearDown() {}
protected:
    std::string _id = "1000";
    std::string _feed_id = "123456789";
    std::string _table = "reco_feed_list";
};

TEST_F(UtMysqlConns, Insert) {
    std::stringstream ss;
    ss << "insert into " << _table << "(id, feed_id) values(" 
        << _id << "," << _feed_id << ") ON DUPLICATE KEY UPDATE feed_id=" << _feed_id;
    std::string command = ss.str();

    std::string conn_name = "netdisk_reco_conn";
    MysqlSession session;
    int ret = MysqlConns::get_mutable_instance().query(conn_name, command, session);
    ASSERT_EQ(0, ret);
    
    MYSQL_RES* res = session._res;
    ASSERT_EQ(NULL, res);
}

TEST_F(UtMysqlConns, Select) {
    std::stringstream ss;
    ss << "select feed_id from " << _table << " where id =1000";
    std::string command = ss.str();

    std::string conn_name = "netdisk_reco_conn";
    MysqlSession session;
    int ret = MysqlConns::get_mutable_instance().query(conn_name, command, session);
    ASSERT_EQ(0, ret);
    
    MYSQL_RES* res = session._res;
    int row_size = mysql_num_rows(res);
    ASSERT_EQ(1, row_size);
    int field_size = mysql_num_fields(res);
    ASSERT_EQ(1, field_size);
    for (int i = 0; i < row_size; i++) {
        MYSQL_ROW row = mysql_fetch_row(res);
        ASSERT_STREQ(row[0], _feed_id.c_str());
    }
}

}
}
