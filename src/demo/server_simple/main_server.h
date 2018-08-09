/*************************************************************************
    > File Name: main_server.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_DEMO_SERVER_SIMPLE_MAIN_SERVER_H
#define PELEUS_SRC_DEMO_SERVER_SIMPLE_MAIN_SERVER_H
#include "src/demo/proto/demo.pb.h"

namespace peleus {
namespace demo {
namespace server_simple {

class MainServer : 
    public ::demo::EchoService
{
public:
    explicit MainServer();

public:
  virtual void Echo(::google::protobuf::RpcController* controller,
                       const ::demo::EchoRequest* request,
                       ::demo::EchoResponse* response,
                       ::google::protobuf::Closure* done) override;
};

}
}
}

#endif //  PELEUS_SRC_DEMO_SERVER_SIMPLE_MAIN_SERVER_H
