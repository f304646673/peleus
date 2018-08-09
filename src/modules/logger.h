/*************************************************************************
    > File Name: logger.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 22 Dec 2018 06:29:12 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_LOGGER_H
#define PELEUS_SRC_MODULES_LOGGER_H

#include <string>
#include <boost/serialization/singleton.hpp>
#include "module.h"

namespace peleus {
namespace modules {

class Logger :
    public Module<Logger>,
    public boost::serialization::singleton<Logger>
{
    friend class Module<Logger>;
public:
    ~Logger();
private:
    virtual void on_init(const char* conf_path) override final;
    virtual const char* name() override final;
};

}
}

#endif // PELEUS_SRC_MODULES_LOGGER_H
