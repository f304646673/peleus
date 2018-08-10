/*************************************************************************
    > File Name: server.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:57:48 PM CST
 ************************************************************************/
#include "server.h"

#include <dlfcn.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include "entrance_factory.h"
#include "src/utils/utils.h"
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"

namespace peleus {
namespace modules {

using google::protobuf::Service;

using peleus::utils::err_str;
using peleus::utils::PeleusException;

using peleus::entrance::smart_ptr;
using peleus::modules::EntranceFactory;
using peleus::modules::configure::entrance_conf;

using peleus::utils::TraversalFloder;
using peleus::utils::TraversalCallback;

Server::Server(void) {
}

Server::~Server(void) {
}

void Server::on_init(const char* conf_path) {
    bool suc = peleus::utils::file2conf(conf_path, _config);
    if (!suc) {
        LOG(ERROR) << "Server::on_init Fatal";
    }
    _init();
}

const char* Server::name() {
    return "server";
}

void Server::_init() {
    TraversalCallback traversal_file = [this](const char* path) {this->init_from_file(path);};
    TraversalFloder traversal;
    traversal.set_callback(NULL, traversal_file, __FILE__);
    traversal.init(_config.main_server_conf_path().c_str());
}

void Server::init_from_file(const char* conf_path) {
    try {
        entrance_conf config;
        bool suc = peleus::utils::file2conf(conf_path, config);
        if (!suc) {
            FALSE_THROW(0, "init_from_file Fatal: %s", conf_path);
        }

        smart_ptr ptr = _entrance_repertory.get_entrance(config.name().c_str());
        Service* service = dynamic_cast<google::protobuf::Service*>(ptr.get());
        if (!service) {
            FALSE_THROW(0, "%s get service error", config.name().c_str());
        }
        if (_server.AddService(service, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
            FALSE_THROW(0, "%s Add %s server error", name(), config.name().c_str());
        }
    }
    catch (PeleusException& e) {
        throw;
    }
    catch (const std::exception& exp) {
        throw;
    }
}

void Server::start() {
    brpc::ServerOptions options;
    options.idle_timeout_sec = _config.idle_timeout_sec();
    options.max_concurrency = _config.max_concurrency();
    options.num_threads = _config.num_threads();
    options.internal_port = _config.internal_port();
    try {
        if (_server.Start(_config.port(), &options) != 0) {
            FALSE_THROW(0, "%s start server error", name());
        }
        _server.RunUntilAskedToQuit();
    }
    catch (PeleusException& e) {
        throw;
    }
    catch (const std::exception& exp) {
        throw;
    }
}

}
}
