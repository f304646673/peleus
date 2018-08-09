/*************************************************************************
    > File Name: module.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 07:18:06 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_MODULE_H
#define PELEUS_SRC_MODULES_MODULE_H

#include <boost/bind.hpp>

#include "config_registry.h"

namespace peleus {
namespace modules {

template<class T>
class Module {
public:
    Module() {};
    virtual ~Module() {};
public:
    virtual bool initialize() final {
        config_callback fn = boost::bind(&T::on_init, dynamic_cast<T*>(this), _1);
        ConfigRegistry::get_mutable_instance().register_config_dir(dynamic_cast<T*>(this)->name(), fn);
        return true;
    };
private:
    virtual void on_init(const char*) = 0;
    virtual const char* name() = 0;
};

}
}

#endif // PELEUS_SRC_MODULES_MODULE_H
