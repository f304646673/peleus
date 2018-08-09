/*************************************************************************
    > File Name: entrance_repertory.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 28 Mar 2018 03:59:18 PM CST
 ************************************************************************/
#include "entrance_repertory.h"
#include <butil/logging.h>
#include "entrance_factory.h"
#include "src/utils/utils.h"
#include "src/utils/config_conv.h"

namespace peleus {
namespace modules {

using peleus::entrance::smart_ptr;
using peleus::utils::PeleusException;
using peleus::utils::err_str;
using peleus::modules::EntranceFactory;

EntranceRepertory::EntranceRepertory() {
}

EntranceRepertory::~EntranceRepertory() {
}

smart_ptr EntranceRepertory::get_entrance(const std::string& entrance_name) {
    auto it = _entrances.find(entrance_name);
    if (it != _entrances.end()) {
        return it->second;
    }
    smart_ptr sp = EntranceFactory::get_mutable_instance().create(entrance_name);
        
    try {
        FALSE_THROW(sp.get(), "EntranceRepertory::get_entrance create %s error", entrance_name.c_str());
    }
    catch (PeleusException& e) {
        throw;
    }
    catch (const std::exception& exp) {
        throw;
    }
    _entrances[entrance_name] = sp;
    return sp;
}

}
}
