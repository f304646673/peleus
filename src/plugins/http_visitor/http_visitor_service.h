/*************************************************************************
    > File Name: http_visitor_service.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 30 Mar 2018 02:22:05 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_HTTP_VISITOR_HTTP_VISITOR_SERVICE_H
#define PELEUS_SRC_PLUGINS_HTTP_VISITOR_HTTP_VISITOR_SERVICE_H
//#include "src/plugins/http_conns/interface/http.pb.h"
#include "src/plugins/http_visitor/interface/http_visitor_service.pb.h"
#include "src/entrance/entrance.h"
#include <brpc/server.h>

namespace peleus {
namespace plugins {
namespace http_visitor {

class HttpVisitorService : 
    public peleus::plugins::HttpVisitorService,
    public peleus::entrance::Entrance
{
public:
    explicit HttpVisitorService(const char* name);

public:
    virtual void query(::google::protobuf::RpcController* controller,
       const ::peleus::plugins::HttpVisitorServiceRequest* request,
       ::peleus::plugins::HttpVisitorServiceResponse* response,
       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_HTTP_VISITOR_HTTP_VISITOR_SERVICE_H
