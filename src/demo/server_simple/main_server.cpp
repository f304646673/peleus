/*************************************************************************
    > File Name: main_server.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "main_server.h"
#include <brpc/server.h>

namespace peleus {
namespace demo {
namespace server_simple {

using ::demo::EchoRequest;
using ::demo::EchoResponse;
using brpc::ClosureGuard;
using brpc::Controller;

MainServer::MainServer()
{
}

void MainServer::Echo(
    google::protobuf::RpcController* cntl_base,
    const EchoRequest* request,
    EchoResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());
    response->set_message(request->message());
}

}
}
}
