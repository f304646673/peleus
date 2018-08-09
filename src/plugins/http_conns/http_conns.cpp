/*************************************************************************
    > File Name: http_conns.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Mon 23 Apr 2018 08:55:58 PM CST
 ************************************************************************/
#include "http_conns.h"
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"
#include <boost/algorithm/string.hpp> 

namespace peleus {
namespace plugins {
namespace http_conns {

using peleus::utils::TraversalCallback;
using peleus::utils::TraversalFloder;
using peleus::plugins::configure::http_conn_conf;
using peleus::plugins::HttpRequest;
using peleus::plugins::HttpResponse;

HttpConns::HttpConns() {
}

HttpConns::~HttpConns() {
}

bool HttpConns::access(const HttpRequest& request, HttpResponse& response) {
    const std::string& conn_name = request.conn_name();
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
    cntl.http_request().uri() = request.uri();
    cntl.http_request().set_version(1, 0);
    
    if (request.post()) {
        cntl.http_request().set_method(brpc::HTTP_METHOD_POST);
        cntl.request_attachment().append(request.post_data());
    }
    else {
        cntl.http_request().set_method(brpc::HTTP_METHOD_GET);
    }
    channel->CallMethod(NULL, &cntl, NULL, NULL, NULL);

    if (cntl.Failed()) {
        response.set_error_code(cntl.ErrorCode());
        response.set_error_text(cntl.ErrorText());
        return false;
    }
    else {
        response.set_error_code(0);
        response.set_error_text("");
    }
    response.set_response( cntl.response_attachment().to_string());

    return true;
}


}
}
}
