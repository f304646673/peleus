/*************************************************************************
    > File Name: main.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Sun 25 Mar 2018 12:07:35 AM CST
 ************************************************************************/
#include "src/modules/config_registry.h"
#include "src/modules/creator_repertory.h"
#include "src/modules/plugin_loader.h"
#include "src/modules/entrance_factory.h"
#include "src/modules/server.h"
#include "src/modules/inter_server.h"
#include "src/modules/logger.h"

#include "src/utils/utils.h"

using peleus::modules::ConfigRegistry;
using peleus::modules::CreatorRepertory;
using peleus::modules::PluginLoader;
using peleus::modules::EntranceFactory;
using peleus::modules::Server;
using peleus::modules::Logger;
using peleus::modules::InterServer;
using peleus::utils::PeleusException;
using peleus::utils::err_str;

int main() {
    try {
        ConfigRegistry::get_mutable_instance().initialize("../conf/config_registry.conf");
        Logger::get_mutable_instance().initialize();
        CreatorRepertory::get_mutable_instance().initialize();
        PluginLoader::get_mutable_instance().initialize();
        EntranceFactory::get_mutable_instance().initialize();
        InterServer::get_mutable_instance().initialize();
        Server::get_mutable_instance().initialize();
        Server::get_mutable_instance().start();
    }
    catch (PeleusException& e) {
        std::string s = *boost::get_error_info<err_str>(e);
        LOG(FATAL) << s.c_str();
    }
    catch (...) {
        LOG(FATAL) << "finnal error";
    }
    return 0;
}
