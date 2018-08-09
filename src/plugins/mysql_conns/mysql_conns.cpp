/*************************************************************************
    > File Name: mysql_conns.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Mon 23 Apr 2018 08:55:58 PM CST
 ************************************************************************/
#include "mysql_conns.h"
#include <butil/logging.h>
#include <boost/algorithm/string.hpp> 
#include "mysql_error.h"
#include "src/utils/traversal_floder.h"
#include "src/utils/config_conv.h"

namespace peleus {
namespace plugins {
namespace mysql_conns {

using peleus::utils::TraversalCallback;
using peleus::utils::TraversalFloder;
using peleus::plugins::configure::mysql_connection_pool;

MysqlConns::MysqlConns() {
}

MysqlConns::~MysqlConns() {
    for (auto it = _conns.begin(); it != _conns.end(); it++) {
        if (it->second) {
            delete it->second;
            it->second = NULL;
        }
    }
}

void MysqlConns::init(const char* conf_floder_path) {
    TraversalCallback traversal_floder = [this](const char* path) {this->init(path);};
    TraversalCallback traversal_file = [this](const char* path) {this->init_from_file(path);};
    TraversalFloder traversal;
    traversal.set_callback(traversal_floder, traversal_file, __FILE__);
    traversal.init(conf_floder_path);
}

void MysqlConns::init_from_file(const char* conf_path) {
    mysql_connection_pool config;
    bool suc = peleus::utils::file2conf(conf_path, config);
    if (!suc) {
        LOG(ERROR) << "init " << conf_path << " error";
        return;
    }
    const std::string& conn_name = config.name();
    MysqlConnectionPool* conn_pool = init_conn_pool(config);
    if (!conn_pool) {
        LOG(ERROR) << "init mysql connection pool error:" << conn_name;
        return;
    }
    _conns[conn_name] = conn_pool;
}

MysqlConnectionPool* MysqlConns::init_conn_pool(const mysql_connection_pool& conf) {
    MysqlConnectionPool* conn_pool = new MysqlConnectionPool();
    conn_pool->init(conf);
    return conn_pool;
}


int MysqlConns::query(const std::string& conn_name, 
        const std::string& sql,
        MysqlSession& session)
{
    auto it = _conns.find(conn_name);
    if (it == _conns.end()) {
        LOG(ERROR) << "cant find mysql connection:" << conn_name.c_str();
        return NO_CONNECTION;
    }
    if (!it->second) {
        LOG(ERROR) << "mysql connection pool is null";
        return NULL_CONNECTION;
    }
    return it->second->query(sql, session);
}


}
}
}
