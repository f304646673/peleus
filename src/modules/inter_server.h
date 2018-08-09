/*************************************************************************
    > File Name: inter_server.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 29 Mar 2018 01:08:27 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_INTER_SERVER_H
#define PELEUS_SRC_MODULES_INTER_SERVER_H

#include <string>
#include <boost/serialization/singleton.hpp>
#include <brpc/server.h>
#include <brpc/channel.h>

#include "module.h"
#include "entrance_repertory.h"
#include "src/modules/configure/inter_server.pb.h"

namespace peleus {
namespace modules {

class InterServer : 
    public Module<InterServer>,
    public boost::serialization::singleton<InterServer>
{
    friend class Module<InterServer>;
public:
    InterServer(void);
    ~InterServer(void);
public:
    brpc::Channel& get_channel();
private:
    void start();
    void init();
    void init_channel();
    void add_inter_service();
    void add_service(const std::string& entrance_name);
private:
    virtual void on_init(const char*) override final;
    virtual const char* name() override final;
    void init_from_file(const char* conf_path);
private:
    brpc::Channel _channel;
    brpc::Server _server;
    peleus::modules::configure::inter_server_conf _config;
    peleus::modules::EntranceRepertory _entrance_repertory;
};

}
}

#endif //  PELEUS_SRC_MODULES_INTER_SERVER_H
