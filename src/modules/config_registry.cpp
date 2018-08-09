/*************************************************************************
    > File Name: config_registry.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 08:28:39 PM CST
 ************************************************************************/
#include "config_registry.h"
#include <butil/logging.h>
#include <boost/lexical_cast.hpp>
#include "src/utils/config_conv.h"

namespace peleus {
namespace modules {

using ::peleus::modules::configure::module_conf;

ConfigRegistry::ConfigRegistry(void) {
}

ConfigRegistry::~ConfigRegistry(void) {
}

bool ConfigRegistry::initialize(const char* conf_path) {
    bool suc = peleus::utils::file2conf(conf_path, _config);
    LOG(DEBUG) << "ConfigRegistry::initialize from " << conf_path;
    if (!suc) {
        LOG(FATAL) << "ConfigRegistry::initialize Fatal";
        return suc;
    }
    
    int size = _config.modules_conf_size();
    for (int i = 0; i < size; i++) {
        const module_conf& conf = _config.modules_conf(i);
        _config_name_path[conf.name()] = conf.path();
        LOG(DEBUG) << "ConfigRegistry::initialize " 
                << conf.name().c_str() << " " << conf.path().c_str();
    }
    LOG(DEBUG) << "ConfigRegistry::initialize Success";
    return suc;
}

bool ConfigRegistry::register_config_dir(
    const char* name,
    config_callback& f_config_proc) const 
{
    auto it = _config_name_path.find(std::string(name));
    if (it == _config_name_path.end()) {
        LOG(WARNING) << "ConfigRegistry::register_config_dir search " << name << " failed";
        return false;
    }
    LOG(DEBUG) << "ConfigRegistry::register_config_dir search " << name << " path: " << it->second.c_str();
    f_config_proc(it->second.c_str());
    return true;
}

}
}
