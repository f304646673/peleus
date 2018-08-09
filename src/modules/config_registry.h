/*************************************************************************
    > File Name: config_registry.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 08:22:37 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_CONFIG_REGISTRY_H
#define PELEUS_SRC_MODULES_CONFIG_REGISTRY_H

#include <map>
#include <string>
#include <boost/function.hpp>
#include <boost/serialization/singleton.hpp>

#include "src/modules/configure/config_registry.pb.h"

namespace peleus {
namespace modules {

typedef boost::function<void(
        const char*)> config_callback;

class ConfigRegistry : 
    public boost::serialization::singleton<ConfigRegistry>
{
public:
    ConfigRegistry(void);
    ~ConfigRegistry(void);  
public:
    bool initialize(const char* conf_path);

    bool register_config_dir(
            const char* name, 
            config_callback& f_config_proc) const;
private:
    void init_from_file(const char* conf_path);
private:
    peleus::modules::configure::config_registry_conf _config;
    struct std::map<std::string, std::string> _config_name_path;
};

}
}

#endif //  PELEUS_SRC_MODULES_CONFIG_REGISTRY_H
