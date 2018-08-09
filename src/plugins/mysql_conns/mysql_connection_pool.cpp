/*************************************************************************
    > File Name: mysql_connection_pool.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 01 May 2018 11:22:58 PM CST
 ************************************************************************/
#include "mysql_connection_pool.h"
#include <butil/logging.h>
#include "mysql_error.h"

namespace peleus {
namespace plugins {
namespace mysql_conns {

MysqlConnectionPool::MysqlConnectionPool() {
}

MysqlConnectionPool::~MysqlConnectionPool() {
    for (auto it = _unused.begin(); it != _unused.end(); it++) {
        if (*it) {
            delete *it;
            *it = NULL;
        }
    }
}

void MysqlConnectionPool::init(const peleus::plugins::
        configure::mysql_connection_pool& conf) {
    _conf.CopyFrom(conf);
    int size = _conf.size();
    if (size < 0) {
        _use_pool = false;
        return;
    }

    _use_pool = true;
    pthread_mutex_init(&_mutex, NULL);
    pthread_mutex_lock(&_mutex);
    for (int i = 0; i< size; i++) {
        MysqlConnection* conn = new MysqlConnection();
        conn->init(_conf.conn_info());
        _unused.push_back(conn);
    }
    pthread_mutex_unlock(&_mutex);
}

int MysqlConnectionPool::query(const std::string& sql, MysqlSession& session) {
    if (_use_pool) {
        return query_from_pool(sql, session);
    }
    return query_once(sql, session);
}

void MysqlConnectionPool::recovery(MysqlConnection* conn) {
    if (_use_pool) {
        pthread_mutex_lock(&_mutex);
        _unused.push_back(conn);
        pthread_mutex_unlock(&_mutex);
    }
}

int MysqlConnectionPool::query_once(const std::string& sql, MysqlSession& session) {
    MysqlConnection conn;
    conn.init(_conf.conn_info());
    int ret = conn.mysql_real_query(sql);
    session._res = conn.mysql_store_result();
    return ret;
}

int MysqlConnectionPool::query_from_pool(const std::string& sql, MysqlSession& session) {
    MysqlConnection* conn = NULL;
    pthread_mutex_lock(&_mutex);
    if (!_unused.empty()) {
        conn = _unused.back();
        _unused.pop_back();
    }
    pthread_mutex_unlock(&_mutex);
    if (!conn) {
        LOG(ERROR) << "need more connection";
        return LACK_CONNECTION;
    }

    int ret = conn->mysql_real_query(sql);
    session._res = conn->mysql_store_result();
    session._conn = conn;
    session._conn_pool = this;
    return ret;
}

}
}
}
