/*************************************************************************
    > File Name: main.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 28 Mar 2018 07:00:15 PM CST
 ************************************************************************/
#include <brpc/server.h>
#include <brpc/channel.h>
#include "src/demo/proto/demo.pb.h"
#include "main_server.h"

int main(int argc, const char** argv) {
    brpc::Server server;
    peleus::demo::server_simple::MainServer echo_service_impl;
    if (server.AddService(&echo_service_impl, 
          brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        std::cout << "Fail to add service" << std::endl;
        return -1;
    }

    brpc::ServerOptions options;
    options.idle_timeout_sec = 1000;
    options.max_concurrency = 1000;
    options.internal_port = 8066;
    if (server.Start(8065, &options) != 0) {
        std::cout << "Fail to start EchoServer" << std::endl;
        return -1;
    }

    server.RunUntilAskedToQuit();
    return 0;
}
