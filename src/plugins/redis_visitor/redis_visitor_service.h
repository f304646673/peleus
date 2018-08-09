/*************************************************************************
    > File Name: redis_visitor_service.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 30 Mar 2018 02:22:05 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_REDIS_VISITOR_REDIS_VISITOR_SERVICE_H
#define PELEUS_SRC_PLUGINS_REDIS_VISITOR_REDIS_VISITOR_SERVICE_H
#include "src/plugins/redis_visitor/interface/redis_visitor_service.pb.h"
#include "src/entrance/entrance.h"
#include <brpc/server.h>
#include <brpc/redis.h>

namespace peleus {
namespace plugins {
namespace redis_visitor {

class RedisVisitorService : 
    public peleus::plugins::RedisVisitorService,
    public peleus::entrance::Entrance
{
public:
    explicit RedisVisitorService(const char* name);

public:
    virtual void query(::google::protobuf::RpcController* controller,
       const ::peleus::plugins::RedisVisitorServiceRequest* request,
       ::peleus::plugins::RedisVisitorServiceResponse* response,
       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
private:
    void parse_reply(
            const brpc::RedisReply& reply, 
            ::peleus::plugins::RedisVisitorReply* rp);
    void parse_reply_array(
            const brpc::RedisReply& reply, 
            ::peleus::plugins::RedisVisitorReply* rp);
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_REDIS_VISITOR_REDIS_VISITOR_SERVICE_H
