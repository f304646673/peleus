/*************************************************************************
    > File Name: mysql_visitor_service.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 02 May 2018 03:07:45 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_MYSQL_VISITOR_MYSQL_VISITOR_SERVICE_H
#define PELEUS_SRC_PLUGINS_MYSQL_VISITOR_MYSQL_VISITOR_SERVICE_H
#include "src/plugins/mysql_visitor/interface/mysql_visitor_service.pb.h"
#include "src/entrance/entrance.h"
#include <brpc/server.h>
#include <brpc/redis.h>
#include "src/plugins/mysql_conns/mysql_conns.h"

namespace peleus {
namespace plugins {
namespace mysql_visitor {

class MysqlVisitorService : 
    public peleus::plugins::MysqlVisitorService,
    public peleus::entrance::Entrance
{
public:
    explicit MysqlVisitorService(const char* name);

public:
    virtual void query(::google::protobuf::RpcController* controller,
       const ::peleus::plugins::MysqlVisitorServiceRequest* request,
       ::peleus::plugins::MysqlVisitorServiceResponse* response,
       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
private:

    void parse_res(
            MYSQL_RES* res, 
            ::peleus::plugins::MysqlVisitorServiceResponse* response);

    void parse_session(
            peleus::plugins::mysql_conns::MysqlSession& session, 
            ::peleus::plugins::MysqlVisitorServiceResponse* response);
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_MYSQL_VISITOR_MYSQL_VISITOR_SERVICE_H
