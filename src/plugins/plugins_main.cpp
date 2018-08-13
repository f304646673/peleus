/*************************************************************************
    > File Name: plugins_main.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 03 Apr 2018 10:37:35 PM CST
 ************************************************************************/
#include "src/entrance/repertory.h"
#include "http_conns/http_conns.h"
#include "http_visitor/http_visitor_service.h"
#include "redis_conns/redis_conns.h"
#include "redis_visitor/redis_visitor_service.h"
#include "mysql_conns/mysql_conns.h"
#include "mysql_visitor/mysql_visitor_service.h"
#include "src/utils/config_conv.h"
#include "src/plugins/configure/plugins_conf.pb.h"

using peleus::entrance::register_class;
using peleus::plugins::http_conns::HttpConns;
using peleus::plugins::http_visitor::HttpVisitorService;
using peleus::plugins::redis_conns::RedisConns;
using peleus::plugins::redis_visitor::RedisVisitorService;
using peleus::plugins::redis_conns::RedisConns;
using peleus::plugins::mysql_visitor::MysqlVisitorService;
using peleus::plugins::mysql_conns::MysqlConns;
using peleus::plugins::configure::plugin_conf;
using peleus::plugins::configure::plugins_conf;
using peleus::utils::file2conf;

extern "C" {
    bool plugins_main(const char*);
};

#define USE(x, y)   \
    if (item_conf.name() == x) {    \
        y::get_mutable_instance().init(item_conf.conf_path().c_str());    \
    }

#define REG(x, y, z)    \
    if (item_conf.name() == x) {   \
        return register_class<y>(z);    \
    }

bool load_moudle(const plugin_conf& item_conf) {
    if (!item_conf.on()) {
        return true;
    }

    USE("http_conns", HttpConns);
    USE("redis_conns", RedisConns);
    USE("mysql_conns", MysqlConns);
    REG("http_visitor_service", HttpVisitorService, "HttpVisitorService");
    REG("redis_visitor_service", RedisVisitorService, "RedisVisitorService");
    REG("mysql_visitor_service", MysqlVisitorService, "MysqlVisitorService");

    return true;
}

bool plugins_main(const char* conf_path) {
    plugins_conf config;
    bool suc = file2conf(conf_path, config);
    if (!suc) {
        LOG(ERROR) << "conv config error:" << conf_path;
        return false;
    }

    size_t size = config.conf_size();

    for (size_t i = 0; i < size; i++) {
        const plugin_conf& item_conf = config.conf(i);
        if (!load_moudle(item_conf)) {
            break;
        }
    }

    return true;
}
