/*************************************************************************
    > File Name: mysql_connection.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 19 Dec 2018 03:51:27 PM CST
 ************************************************************************/
#include "mysql_connection.h"
#include <butil/logging.h>
#include <errmsg.h>
#include "mysql_error.h"

namespace peleus {
namespace plugins {
namespace mysql_conns {

using peleus::plugins::configure::mysql_connection;

MysqlConnection::MysqlConnection() {
    _conn = NULL;
}

MysqlConnection::~MysqlConnection() {
    _disconnect();
}

void MysqlConnection::init(const mysql_connection& conf) {
    _conf.CopyFrom(conf);
}

int MysqlConnection::mysql_real_query(const std::string& sql) {
    int ret = 0;
    if (!_conn) {
        ret = _reconnct();
        if (ret) {
            return ret;
        }
    }

    LOG(INFO) << "query sql:" << sql.c_str();
    const int max_retry = 2;
    for (auto i = 0; i < max_retry; i++) {
        ret = ::mysql_real_query(_conn, sql.c_str(), sql.length());
        if (0 == ret) {
            break;
        }
        else if (i < max_retry - 1){
            LOG(INFO) << "mysql connection is lost.retry " << i;
            int ret_re = _reconnct();
            if (ret_re) {
                LOG(WARNING) << "mysql connection is lost.retry error" << ret_re;
                return ret_re;
            }
        }
        else if (ret != CR_SERVER_LOST && ret != CR_SERVER_GONE_ERROR) {
            LOG(ERROR) << "query error:" << ret << " sql:" << sql.c_str();
            return ret;
        }
    }

    return ret;
}

MYSQL_RES* MysqlConnection::mysql_store_result() {
    if (_conn) {
        return ::mysql_store_result(_conn);
    }
    else {
        return NULL;
    }
}

int MysqlConnection::_reconnct() {
    if (_conn) {
        _disconnect();
    }
    return _connect();
}

int MysqlConnection::_connect() {
    _conn = mysql_init(NULL);
    if (!_conn) {
        return CR_OUT_OF_MEMORY;
    }
    unsigned long time_out = _conf.read_timeout();
    unsigned long conn_out = _conf.conn_timeout();
    mysql_options(_conn, MYSQL_OPT_READ_TIMEOUT, (char*)&time_out);
    mysql_options(_conn, MYSQL_OPT_CONNECT_TIMEOUT, (char*)&conn_out);

    if (!mysql_real_connect(_conn,
            _conf.host().c_str(),
            _conf.user().c_str(),
            _conf.password().c_str(),
            _conf.dbname().c_str(),
            _conf.port(),
            NULL, 0))
    {
        _disconnect();
        return CR_SERVER_GONE_ERROR;
    }

    int ret = mysql_set_character_set(_conn, _conf.character_set().c_str());
    if (ret) {
        _disconnect();
    }

    return ret;
}

void MysqlConnection::_disconnect() {
    if (_conn) {
        mysql_close(_conn);
        _conn = NULL;
    }
}

}
}
}
