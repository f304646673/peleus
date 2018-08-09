/*************************************************************************
    > File Name: mysql_connection.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 19 Dec 2018 03:48:55 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_CONNECTION_H
#define PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_CONNECTION_H

#include "src/plugins/mysql_conns/configure/mysql_conns.pb.h"

#include <algorithm>

#include <my_global.h>
#undef max
#undef min
#undef test

#include <m_ctype.h>
#include <mysql_com.h>
#include <mysql.h>
#include <getopt.h>
#include <sql_common.h>

#include <string>

namespace peleus {
namespace plugins {
namespace mysql_conns {

class MysqlConnection {
public:
    MysqlConnection();
    ~MysqlConnection();
public:
    void init(const peleus::plugins::configure::mysql_connection& conf);
    int mysql_real_query(const std::string& sql);
    MYSQL_RES* mysql_store_result();
private:
    int _reconnct();
    int _connect();
    void _disconnect();
private:
    peleus::plugins::configure::mysql_connection _conf;
    MYSQL* _conn;
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_CONNECTION_H
