/*************************************************************************
    > File Name: entrance_factory.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 27 Mar 2018 06:45:44 PM CST
 ************************************************************************/
#include "entrance_factory.h"
#include <butil/logging.h>
#include "creator_repertory.h"
#include "src/utils/utils.h"
#include "src/utils/config_conv.h"
#include "src/utils/traversal_floder.h"

namespace peleus {
namespace modules {

using peleus::utils::err_str;
using peleus::utils::PeleusException;

using peleus::entrance::smart_ptr;
using peleus::entrance::creator_t;

using peleus::modules::CreatorRepertory;
using peleus::modules::configure::entrance_conf;

using peleus::utils::TraversalFloder;
using peleus::utils::TraversalCallback;

EntranceFactory::EntranceFactory(void) {
}

EntranceFactory::~EntranceFactory(void) {
}

void EntranceFactory::on_init(const char* conf_floder_path) {
    TraversalCallback traversal_floder = [this](const char* path) {this->on_init(path);};
    TraversalCallback traversal_file = [this](const char* path) {this->init_from_file(path);};
    TraversalFloder traversal;
    traversal.set_callback(traversal_floder, traversal_file, __FILE__);
    traversal.init(conf_floder_path);
}

void EntranceFactory::init_from_file(const char* conf_path) {
    entrance_conf config;
    bool suc = peleus::utils::file2conf(conf_path, config);
    if (!suc) {
        LOG(FATAL) << "init_from_file Fatal: " << conf_path;
        return;
    }

    _entrances_conf[config.name()] = config.path();
}

smart_ptr EntranceFactory::create(const std::string& entrance_name) {
    smart_ptr sp;
    try {
        auto it = _entrances_conf.find(entrance_name);
        FALSE_THROW(!(it == _entrances_conf.end()), "%s create get %s conf error", name(), entrance_name.c_str());
        creator_t create_fun = CreatorRepertory::get_mutable_instance().lookup_creator(entrance_name.c_str());
        FALSE_THROW(create_fun, "%s create lookup %s creator error", name(), entrance_name.c_str());
        sp = create_fun(entrance_name.c_str());
        FALSE_THROW(sp.get(), "%s create create %s error", name(), entrance_name.c_str());
        sp->on_init(it->second.c_str());
    }
    catch (PeleusException& e) {
        throw;
    }
    catch (const std::exception& exp) {
        throw;
    }
    return sp;
}

const char* EntranceFactory::name() {
    return "entrance_factory";
}

}
}
