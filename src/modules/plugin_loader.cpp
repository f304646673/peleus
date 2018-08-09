/*************************************************************************
    > File Name: plugin_loader.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 11:25:27 PM CST
 ************************************************************************/
#include "plugin_loader.h"

#include <dlfcn.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <butil/logging.h>

#include "src/utils/utils.h"
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"

namespace peleus {
namespace modules {

using peleus::modules::configure::plugin_conf;
using peleus::utils::PeleusException;
using peleus::utils::err_str;

using peleus::utils::TraversalCallback;
using peleus::utils::TraversalFloder;

PluginLoader::PluginLoader(void) {
}

PluginLoader::~PluginLoader(void) {
}

void PluginLoader::on_init(const char* conf_floder_path) {
    TraversalCallback traversal_floder = [this](const char* path) {this->on_init(path);};
    TraversalCallback traversal_file = [this](const char* path) {this->init_from_file(path);};
    TraversalFloder traversal;
    traversal.set_callback(traversal_floder, traversal_file, __FILE__);
    traversal.init(conf_floder_path);
}

void PluginLoader::init_from_file(const char* conf_path) {
    peleus::modules::configure::plugin_conf config;
    bool suc = peleus::utils::file2conf(conf_path, config);
    if (!suc) {
        LOG(FATAL) << "PluginLoader::on_init Fatal";
        return;
    }

    load_plugin(config.path().c_str(), config.static_flag(), 
        config.func().c_str(), config.conf_path().c_str(), config.error_report());
}

const char* PluginLoader::name() {
    return "plugin_loader";
}

typedef bool (*module_init_func_t)(const char*);

void PluginLoader::load_plugin_and_run(
         const char* so_path, int static_flag, const char* fun_name, const char* conf_path) {
    module_init_func_t init_func = NULL;
    if (!static_flag) {
        FALSE_THROW(boost::filesystem::exists(so_path), 
                "%s can't find %s file", name(), so_path);
        void* handle = dlopen(so_path, RTLD_NOW | RTLD_GLOBAL);
        if (!handle) {
            const char* err_reason = dlerror();
            FALSE_THROW(!err_reason, 
                "%s load %s error.reason : %s", name(), so_path, err_reason);
            FALSE_THROW(0, "%s load %s error", name(), so_path);
        }
        init_func = (module_init_func_t)dlsym(handle, fun_name);
    }
    else {
        init_func = (module_init_func_t)dlsym((void*)RTLD_LOCAL, fun_name);
    }
    
    FALSE_THROW(init_func, "%s get function %s error", name(), fun_name);
    FALSE_THROW(init_func(conf_path), "%s call plugin %s func %s error", name(), so_path, fun_name)
}

void PluginLoader::load_plugin(const char* so_path, int static_flag, 
        const char* fun_name, const char* conf_path, int error_report)
{
    LOG(DEBUG) << "PluginLoader::load_plugin func(" << fun_name
            << ") path(" << so_path
            << ") error_report(" << error_report
            << ") static_flag(" << static_flag
            << ")";
    //FALSE_THROW(fun_name && so_path, "%s load_plugin fun_name or so_path is null", name());
    
    try {
        load_plugin_and_run(so_path, static_flag, fun_name, conf_path);
    }
    catch (PeleusException& e) {
        if (error_report) {
            throw;
        }
        else {
            std::string err = *boost::get_error_info<err_str>(e);
            LOG(FATAL) << err.c_str();
        }
    }
    catch (const std::exception& exp) {
        if (error_report) {
            throw;
        }
        else {
            LOG(FATAL) << "crash reson: " << exp.what();
        }
    }
}

}
}
