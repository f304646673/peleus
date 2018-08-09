/*************************************************************************
    > File Name: http_visitor_service.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 30 Mar 2018 04:32:12 PM CST
 ************************************************************************/
#include "http_visitor_service.h"
#include "./src/plugins/http_conns/http_conns.h"

namespace peleus {
namespace plugins {
namespace http_visitor {

using ::brpc::Controller;
using ::brpc::ClosureGuard;
using ::peleus::plugins::http_conns::HttpConns;
using ::peleus::plugins::HttpRequest;
using ::peleus::plugins::HttpResponse;

HttpVisitorService::HttpVisitorService(const char* name) :
    peleus::entrance::Entrance(name) {
}

void HttpVisitorService::query(::google::protobuf::RpcController* controller,
    const ::peleus::plugins::HttpVisitorServiceRequest* request,
    ::peleus::plugins::HttpVisitorServiceResponse* response,
    ::google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);

    HttpRequest http_request;
    http_request.set_conn_name(request->conn_name());
    http_request.set_uri(request->uri());
    http_request.set_post(request->post());
    http_request.set_post_data(request->post_data());

    HttpResponse http_response;

    HttpConns::get_mutable_instance().access(http_request, http_response);

    response->set_error_code(http_response.error_code());
    response->set_error_text(http_response.error_text());
    response->set_response(http_response.response());
}

void HttpVisitorService::on_init(const char* conf_path) {
}

void HttpVisitorService::reset() {
}

}
}
}
