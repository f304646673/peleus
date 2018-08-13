/*************************************************************************
    > File Name: main_server.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "main_server.h"
#include <brpc/server.h>
#include "src/entrance/semi_sync_rpc.h"
#include "src/plugins/redis_visitor/interface/redis_visitor_service.pb.h"
#include "src/plugins/mysql_visitor/interface/mysql_visitor_service.pb.h"

namespace peleus {
namespace demo {
namespace server {

using ::peleus::entrance::SemiSyncRpc;
using ::peleus::plugins::RedisVisitorServiceRequest;
using ::peleus::plugins::RedisVisitorServiceResponse;
using ::peleus::plugins::RedisVisitorService_Stub;
using ::peleus::plugins::RedisVisitorReply;
using ::peleus::plugins::MysqlVisitorServiceRequest;
using ::peleus::plugins::MysqlVisitorServiceResponse;
using ::peleus::plugins::MysqlVisitorService_Stub;
using ::peleus::plugins::MysqlVisitorRow;

using ::brpc::ClosureGuard;
using ::brpc::Controller;

MainServer::MainServer(const char* name) :
    peleus::entrance::Entrance(name)
{
}

void MainServer::Echo(
    google::protobuf::RpcController* cntl_base,
    const ::demo::EchoRequest* request,
    ::demo::EchoResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    RedisVisitorServiceRequest redis_request;
    RedisVisitorServiceResponse redis_response;
    redis_request.set_command("get test_redis_key");
    redis_request.set_conn_name("redis_server_address");

    MysqlVisitorServiceRequest mysql_request;
    MysqlVisitorServiceResponse mysql_response;
    mysql_request.set_command("select feed_id from reco_feed_list where id=1000");
    mysql_request.set_conn_name("netdisk_reco_conn");

    SemiSyncRpc sync;
    sync.add<RedisVisitorService_Stub>(NULL, &RedisVisitorService_Stub::query,
            &redis_request, &redis_response);
    sync.add<MysqlVisitorService_Stub>(NULL, &MysqlVisitorService_Stub::query,
            &mysql_request, &mysql_response);
    sync.join();

    std::string response_str;

    if (redis_response.suc()) {
        response_str += "redis:suc\n";
        const RedisVisitorReply& rp = redis_response.reply();
        if (rp.type() == RedisVisitorReply::STRING) {
            response_str += rp.c_str();
        }
    }
    else {
        response_str += "redis:failed\n";
    }

    if (mysql_response.suc()) {
        response_str += "mysql:suc\n";
        auto size = mysql_response.rows_size();
        for (auto i = 0; i < size; i++) {
            const MysqlVisitorRow& row = mysql_response.rows(i);
            auto column_size = row.column_size();
            for (auto j = 0; j < column_size; j++) {
                response_str += row.column(j);
                response_str += "\n";
            }
        }
    }
    else {
        response_str += "mysql:failed\n";
    }

    response->set_message(response_str);
}

void MainServer::on_init(const char* conf_path) {
}

void MainServer::reset() {
}

}
}
}
