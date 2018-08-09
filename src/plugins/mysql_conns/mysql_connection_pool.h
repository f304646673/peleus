/*************************************************************************
    > File Name: mysql_connection_pool.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 01 May 2018 10:49:58 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_MYSQL_CONNS_POOL_MYSQL_CONNECTION_POOL_H
#define PELEUS_SRC_PLUGINS_MYSQL_CONNS_POOL_MYSQL_CONNECTION_POOL_H

#include <vector>
#include <string>
#include <pthread.h>
#include "mysql_connection.h"
#include "src/plugins/mysql_conns/configure/mysql_conns.pb.h"

namespace peleus {
namespace plugins {
namespace mysql_conns {

//class MysqlConnectionPool;

class MysqlSession;

class MysqlConnectionPool {
    friend class MysqlSession;
public:
    MysqlConnectionPool();
    ~MysqlConnectionPool();
public:
    void init(const peleus::plugins::configure::mysql_connection_pool& conf);
    int query(const std::string& sql, MysqlSession& session);
private:
    void recovery(MysqlConnection* conn);
    int query_once(const std::string& sql, MysqlSession& session);
    int query_from_pool(const std::string& sql, MysqlSession& session);
private:
    peleus::plugins::configure::mysql_connection_pool _conf;
    std::vector<MysqlConnection*> _unused;
    pthread_mutex_t _mutex;
    bool _use_pool = false;
};

class MysqlSession {
    friend class MysqlConnectionPool;
public:
    MysqlSession() {}
    ~MysqlSession() {
        if (_conn_pool && _conn) {
            _conn_pool->recovery(_conn);
        }
        if (_res) {
            ::mysql_free_result(_res);
            _res = NULL;
        }
    }
    MysqlSession(const MysqlSession&) = delete; 
    MysqlSession& operator=(const MysqlSession&) = delete; 
    void* operator new(size_t) = delete;
    void* operator new[](size_t) = delete;
    void operator delete(void *) = delete;
public:
    MYSQL_RES* _res = NULL;
private:
    MysqlConnection* _conn = NULL;
    MysqlConnectionPool* _conn_pool = NULL;
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_MYSQL_CONNS_POOL_MYSQL_CONNECTION_POOL_H
