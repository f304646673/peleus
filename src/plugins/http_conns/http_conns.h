/*************************************************************************
    > File Name: http_conns.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Mon 23 Apr 2018 08:45:38 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_HTTP_CONNS_HTTP_CONNS_H
#define PELEUS_SRC_PLUGINS_HTTP_CONNS_HTTP_CONNS_H

#include <brpc/channel.h>
#include <boost/serialization/singleton.hpp>
#include "src/plugins/http_conns/interface/http.pb.h"
#include "src/plugins/http_conns/configure/http_conns.pb.h"
#include "src/plugins/brpc_conns_template/brpc_conns_template.h"

namespace peleus {
namespace plugins {
namespace http_conns {

class HttpConns :
    public boost::serialization::singleton<HttpConns>,
    public peleus::plugins::brpc_conns_template::BrpcConnsTemplate
                <peleus::plugins::configure::http_conn_conf, 
                brpc::PROTOCOL_HTTP>
{
public:
    HttpConns();
    ~HttpConns();
public:
    bool access(const peleus::plugins::HttpRequest& request, 
            peleus::plugins::HttpResponse& response);
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_HTTP_CONNS_HTTP_CONNS_H
