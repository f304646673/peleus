/*************************************************************************
    > File Name: redis_conns.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Mon 23 Apr 2018 08:55:58 PM CST
 ************************************************************************/
#include "redis_conns.h"
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"
#include <boost/algorithm/string.hpp> 

namespace peleus {
namespace plugins {
namespace redis_conns {

using peleus::utils::TraversalCallback;
using peleus::utils::TraversalFloder;
using peleus::plugins::configure::redis_conn_conf;
using peleus::plugins::brpc_conns_template::BrpcConnsTemplate;

RedisConns::RedisConns() : BrpcConnsTemplate()  {
}

RedisConns::~RedisConns() {
}

bool RedisConns::access(const std::string& conn_name, 
        const std::string& command,
        brpc::RedisReply& reply) 
{
    auto it = _conns.find(conn_name);
    if (it == _conns.end()) {
        LOG(ERROR) << "can't find connection:" << conn_name;
        return false;
    }

    brpc::Channel* channel = it->second;
    if (!channel) {
        LOG(ERROR) << "connect is null:" << conn_name; 
        return false;
    }

    brpc::Controller cntl;
    brpc::RedisRequest request;
    brpc::RedisResponse response; 
    request.AddCommand(command);
    channel->CallMethod(NULL, &cntl, &request, &response, NULL);
    if (cntl.Failed()) {
        LOG(ERROR) << "failed to access redis-server: conn_name: " << conn_name
            << " command: " << command;
        return false;
    }

    // CopyFromDifferentArena
    reply.CopyFromSameArena(response.reply(0));

    return true;
}


}
}
}
