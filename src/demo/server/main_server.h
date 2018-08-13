/*************************************************************************
    > File Name: main_server.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_DEMO_SERVER_MAIN_SERVER_H
#define PELEUS_SRC_DEMO_SERVER_MAIN_SERVER_H
#include "src/demo/proto/demo.pb.h"
#include "src/entrance/entrance.h"

namespace peleus {
namespace demo {
namespace server {

class MainServer : 
    public ::demo::EchoService,
    public peleus::entrance::Entrance
{
public:
	explicit MainServer(const char* name);

public:
	virtual void Echo(::google::protobuf::RpcController* controller,
                       const ::demo::EchoRequest* request,
                       ::demo::EchoResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}

#endif //  PELEUS_SRC_DEMO_SERVER_MAIN_SERVER_H
