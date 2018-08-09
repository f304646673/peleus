/*************************************************************************
    > File Name: server.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:55:11 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_SERVER_H
#define PELEUS_SRC_MODULES_SERVER_H

#include <string>
#include <boost/serialization/singleton.hpp>
#include <brpc/server.h>

#include "module.h"
#include "entrance_repertory.h"
#include "src/modules/configure/server.pb.h"

namespace peleus {
namespace modules {

class Server : 
    public Module<Server>,
    public boost::serialization::singleton<Server>
{
    friend class Module<Server>;
public:
    Server(void);
    ~Server(void);
public:
    void start();
private:
    void _init();
private:
    virtual void on_init(const char*) override final;
    virtual const char* name() override final;
    void init_from_file(const char* conf_path);
private:
    brpc::Server _server;
    peleus::modules::configure::server_conf _config;
    peleus::modules::EntranceRepertory _entrance_repertory;
};

}
}

#endif //  PELEUS_SRC_MODULES_SERVER_H
