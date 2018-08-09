/*************************************************************************
    > File Name: mysql_conns.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 01 May 2018 10:01:16 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_CONNS_H
#define PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_CONNS_H

#include "mysql_connection_pool.h"
#include <boost/serialization/singleton.hpp>
#include "src/plugins/mysql_conns/configure/mysql_conns.pb.h"

namespace peleus {
namespace plugins {
namespace mysql_conns {

class MysqlConns :
    public boost::serialization::singleton<MysqlConns>
{
public:
    MysqlConns();
    ~MysqlConns();
public:
    void init(const char* conf_path);
    int query(const std::string& conn_name,
            const std::string& sql,
            MysqlSession& session);
private:
    void init_from_file(const char* conf_floder_path);
    MysqlConnectionPool* init_conn_pool(
            const peleus::plugins::configure::mysql_connection_pool& conf);
private:
    std::map<std::string, MysqlConnectionPool*> _conns;
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_CONNS_H
