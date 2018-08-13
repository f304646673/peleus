/*************************************************************************
    > File Name: plugin_loader.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 11:20:42 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_PLUGIN_LOADER_H
#define PELEUS_SRC_MODULES_PLUGIN_LOADER_H

#include <string>
#include <boost/serialization/singleton.hpp>

#include "module.h"
#include "src/modules/configure/plugin_loader.pb.h"

namespace peleus {
namespace modules {

class PluginLoader : 
	public Module<PluginLoader>,
	public boost::serialization::singleton<PluginLoader>
{
	friend class Module<PluginLoader>;
public:
	PluginLoader(void);
	~PluginLoader(void);

public:
	void load_plugin(const char* so_path, int static_flag, 
		const char* fun_name, const char* conf_path, int error_report);
	void load_plugin_and_run(
		 const char* so_path, int static_flag, 
		 const char* fun_name, const char* conf_path);
private:
	void init_from_file(const char* conf_path);
private:
	virtual void on_init(const char*) override final;
	virtual const char* name() override final;
};

}
}

#endif //  PELEUS_SRC_MODULES_PLUGIN_LOADER_H
