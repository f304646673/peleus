/*************************************************************************
    > File Name: brpc_conns_template.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Mon 07 May 2018 06:06:05 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_BRPC_CONNS_TEMPLATE_BRPC_CONNS_TEMPLATE_H
#define PELEUS_SRC_PLUGINS_BRPC_CONNS_TEMPLATE_BRPC_CONNS_TEMPLATE_H

#include <brpc/channel.h>
#include <boost/algorithm/string.hpp> 
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"

namespace peleus {
namespace plugins {
namespace brpc_conns_template {

template<class Conf, brpc::ProtocolType type>
class BrpcConnsTemplate {
public:
    BrpcConnsTemplate() : _type(type) {
    }

    ~BrpcConnsTemplate() {
    }

public:
    void init(const char* conf_floder_path) {
        peleus::utils::TraversalCallback traversal_floder = 
            [this](const char* path) {this->init(path);};

        peleus::utils::TraversalCallback traversal_file =
            [this](const char* path) {this->init_from_file(path);};

        peleus::utils::TraversalFloder traversal;
        traversal.set_callback(traversal_floder, traversal_file, __FILE__);
        traversal.init(conf_floder_path);
    };

private:

    void init_from_file(const char* conf_path) {
        Conf config;
        bool suc = peleus::utils::file2conf(conf_path, config);
        if (!suc) {
            LOG(ERROR) << "init " << conf_path << " error";
            return;
        }
        
        const std::string& conn_name = config.name();
        brpc::Channel* channel = init_conn(config);
        if (!channel) {
            LOG(ERROR) << "init channel error:" << conn_name;
            return;
        }
        _conns[conn_name] = channel;
    }

    brpc::Channel* init_conn(const Conf& conf) {

        brpc::Channel* channel = new (std::nothrow) brpc::Channel;
        if (!channel) {
            LOG(ERROR) << "create channel error";
            return channel;
        }

        brpc::ChannelOptions options;
        options.protocol = _type;
        options.connection_type = conf.connect_type();
        options.timeout_ms = conf.timeout_ms();
        options.max_retry = conf.max_retry();
        options.backup_request_ms = conf.backup_request_ms();
        
        int init_ret = 0;
        const std::string& bns_or_ipport = conf.bns_or_ipport();
        if (boost::istarts_with(bns_or_ipport, "bns://")) {
            const std::string& load_balancer_name = conf.load_balancer_name();
            init_ret = channel->Init(bns_or_ipport.c_str(), load_balancer_name.c_str(), &options);
        }
        else {
            init_ret = channel->Init(bns_or_ipport.c_str(), &options);
        }

        if (init_ret) {
            delete channel;
            channel = NULL;
            LOG(ERROR) << "init channel error:" << bns_or_ipport;
        }

        return channel;
    }

protected:
    std::map<std::string, brpc::Channel*> _conns;

private:
    brpc::ProtocolType _type;
};

}
}
}

#endif // PELEUS_SRC_PLUGINS_BRPC_CONNS_TEMPLATE_BRPC_CONNS_TEMPLATE_H
