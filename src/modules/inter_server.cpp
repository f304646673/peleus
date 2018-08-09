/*************************************************************************
    > File Name: inter_server.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 29 Mar 2018 01:11:00 PM CST
 ************************************************************************/
#include "inter_server.h"

#include <dlfcn.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 

#include "src/utils/utils.h"
#include "entrance_factory.h"
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"

namespace peleus {
namespace modules {

using google::protobuf::Service;

using peleus::utils::file2conf;
using peleus::entrance::smart_ptr;
using peleus::modules::EntranceFactory;

using peleus::utils::TraversalFloder;
using peleus::utils::TraversalCallback;

using peleus::utils::err_str;
using peleus::utils::PeleusException;

using peleus::modules::configure::entrance_conf;
using peleus::modules::configure::query_inter_server_conf;

InterServer::InterServer(void) {
}

InterServer::~InterServer(void) {
}

brpc::Channel& InterServer::get_channel() {
    return _channel;
}

void InterServer::on_init(const char* conf_path) {
    bool suc = file2conf(conf_path, _config);
    if (!suc) {
        LOG(FATAL) << name() << " on_init Fatal";
    }
    if (_config.inter_servers_conf_path().empty()) {
        LOG(NOTICE) << "no inter service add";
        return;
    }
    init();
    start();
}

const char* InterServer::name() {
    return "inter_server";
}

void InterServer::init() {
    try {
        add_inter_service();
    }
    catch (PeleusException& e) {
        throw;
    }
    catch (const std::exception& exp) {
        throw;
    }
}

void InterServer::add_inter_service() {
    TraversalCallback traversal_file = [this](const char* path) {this->init_from_file(path);};
    TraversalFloder traversal;
    traversal.set_callback(NULL, traversal_file, __FILE__);
    traversal.init(_config.inter_servers_conf_path().c_str());
}

void InterServer::init_from_file(const char* conf_path) {
    entrance_conf config;
    bool suc = peleus::utils::file2conf(conf_path, config);
    if (!suc) {
        LOG(FATAL) << "init_from_file Fatal: " << conf_path;
        return;
    }
    add_service(config.name());
}

void InterServer::add_service(const std::string& entrance_name) {
    smart_ptr ptr = _entrance_repertory.get_entrance(entrance_name.c_str());
    Service* service = dynamic_cast<google::protobuf::Service*>(ptr.get());
    if (!service) {
        LOG(WARNING) << name() << " get service error";
    }
    if (_server.AddService(service, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        FALSE_THROW(0, "%s Add %s server error", name(), entrance_name.c_str());
    }
}

void InterServer::start() {
    brpc::ServerOptions options;
    options.idle_timeout_sec = _config.idle_timeout_sec();
    options.max_concurrency = _config.max_concurrency();
    try {
        if (_server.Start(_config.port(), &options) != 0) {
            FALSE_THROW(0, "%s start server error", name());
        }
        init_channel();
        //_server.RunUntilAskedToQuit();
    }
    catch (PeleusException& e) {
        throw;
    }
    catch (const std::exception& exp) {
        throw;
    }
}

void InterServer::init_channel() {
    brpc::ChannelOptions options;
    const query_inter_server_conf& conf = _config.query_conf();
    options.connection_type = conf.connection_type();
    options.connect_timeout_ms = conf.connect_timeout_ms();
    options.timeout_ms = conf.timeout_ms();
    options.max_retry = conf.max_retry();
    std::string server_lower = conf.server();
    transform(server_lower.begin(), server_lower.end(), server_lower.begin(), ::toupper);
    if (boost::istarts_with(server_lower, "bns://")) {
        if (_channel.Init(conf.server().c_str(), conf.balancer().c_str(), &options)) {
            FALSE_THROW(0, "%s fail to initialize channel %s", name(), conf.server().c_str());
        }
    }
    else {
        std::stringstream ss;
        ss << _config.port();
        std::string port = ss.str();
        std::string server_port = conf.server();
        server_port += ":";
        server_port += port;
        if (_channel.Init(server_port.c_str(), &options) != 0) {
            FALSE_THROW(0, "%s fail to initialize channel %s", name(), server_port.c_str());
        }
    }
}

}
}
