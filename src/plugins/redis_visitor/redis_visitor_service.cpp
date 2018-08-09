/*************************************************************************
    > File Name: redis_visitor_service.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 30 Mar 2018 04:32:12 PM CST
 ************************************************************************/
#include "redis_visitor_service.h"
#include "./src/plugins/redis_conns/redis_conns.h"

namespace peleus {
namespace plugins {
namespace redis_visitor {

//using ::google::protobuf::RpcController;
//using ::peleus::plugins::RedisVisitorServiceRequest;
//using ::peleus::plugins::RedisVisitorServiceResponse;
//using ::google::protobuf::Closure;
using ::brpc::Controller;
using ::brpc::ClosureGuard;
using ::peleus::plugins::redis_conns::RedisConns;
using ::peleus::plugins::RedisVisitorReply;

RedisVisitorService::RedisVisitorService(const char* name) :
    peleus::entrance::Entrance(name) {
}

void RedisVisitorService::query(::google::protobuf::RpcController* controller,
    const ::peleus::plugins::RedisVisitorServiceRequest* request,
    ::peleus::plugins::RedisVisitorServiceResponse* response,
    ::google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    const std::string& conn_name = request->conn_name();
    const std::string& command = request->command();

    brpc::RedisReply reply;
    RedisVisitorReply* rp = response->mutable_reply() ;
    bool suc = RedisConns::get_mutable_instance().access(conn_name, command, reply);
    parse_reply(reply, rp);
    response->set_suc(suc);
}

void RedisVisitorService::parse_reply(
        const brpc::RedisReply& reply, 
        RedisVisitorReply* rp)
{
    if (reply.is_error()) {
        rp->set_type(RedisVisitorReply::ERROR);
        rp->set_error_message(reply.error_message());
    }
    else if (reply.is_integer()) {
        rp->set_type(RedisVisitorReply::INTEGER);
        rp->set_integer(reply.integer());
    }
    else if (reply.is_string()) {
        rp->set_type(RedisVisitorReply::STRING);
        rp->set_c_str(reply.c_str());
    }
    else if (reply.is_array()) {
        parse_reply_array(reply, rp);
    }
    else {
        rp->set_type(RedisVisitorReply::NIL);
    }
}

void RedisVisitorService::parse_reply_array(
        const brpc::RedisReply& reply, 
        RedisVisitorReply* rp)
{
    rp->set_type(RedisVisitorReply::ARRAY);
    for (size_t i = 0; i < reply.size(); i++) {
        const brpc::RedisReply& sub_reply = reply[i];
        RedisVisitorReply* sub_rp = rp->add_replies();
        parse_reply(sub_reply, sub_rp);
    }
}

void RedisVisitorService::on_init(const char* conf_path) {
}

void RedisVisitorService::reset() {
}

}
}
}
