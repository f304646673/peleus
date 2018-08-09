/*************************************************************************
    > File Name: entrance_factory.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 06:32:38 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_ENTRANCE_FACTORY_H
#define PELEUS_SRC_MODULES_ENTRANCE_FACTORY_H

#include <map>
#include <string>
#include <boost/serialization/singleton.hpp>

#include "module.h"
#include "src/entrance/entrance.h"
#include "src/modules/configure/entrance_factory.pb.h"

namespace peleus {
namespace modules {

class EntranceFactory :
    public Module<EntranceFactory>,
    public boost::serialization::singleton<EntranceFactory>
{
    friend class Module<EntranceFactory>;
public:
    EntranceFactory();
    ~EntranceFactory();
public:
    peleus::entrance::smart_ptr 
        create(const std::string& entrance_name);
private:
    virtual void on_init(const char*) override final;
    virtual const char* name() override final;

    void init_from_file(const char* conf_path);
private:
    typedef std::map<std::string, std::string> entrance_conf_map_t;

    entrance_conf_map_t _entrances_conf;
};

}
}

#endif // PELEUS_SRC_MODULES_ENTRANCE_FACTORY_H
