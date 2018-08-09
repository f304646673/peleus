/*************************************************************************
    > File Name: redis_conns.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Mon 23 Apr 2018 08:45:38 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_REDIS_CONNS_REDIS_CONNS_H
#define PELEUS_SRC_PLUGINS_REDIS_CONNS_REDIS_CONNS_H

#include <brpc/channel.h>
#include <brpc/redis.h>
#include <boost/serialization/singleton.hpp>
#include "src/plugins/redis_conns/configure/redis_conns.pb.h"
#include "src/plugins/brpc_conns_template/brpc_conns_template.h"

namespace peleus {
namespace plugins {
namespace redis_conns {

class RedisConns :
    public boost::serialization::singleton<RedisConns>,
    public peleus::plugins::brpc_conns_template::BrpcConnsTemplate
                <peleus::plugins::configure::redis_conn_conf, 
                brpc::PROTOCOL_REDIS>
{
public:
    RedisConns();
    ~RedisConns();
public:
    bool access(const std::string& conn_name, 
            const std::string& command,
            brpc::RedisReply& reply);
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_REDIS_CONNS_REDIS_CONNS_H
