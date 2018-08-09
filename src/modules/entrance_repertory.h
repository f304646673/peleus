/*************************************************************************
    > File Name: entrance_repertory.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 28 Mar 2018 03:54:35 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_ENTRANCE_REPERTORY_H
#define PELEUS_SRC_MODULES_ENTRANCE_REPERTORY_H

#include <map>
#include <string>

#include "src/entrance/entrance.h"

namespace peleus {
namespace modules {

class EntranceRepertory {
public:
    EntranceRepertory();
    ~EntranceRepertory();
public:
    peleus::entrance::smart_ptr 
        get_entrance(const std::string& entrance_name);
private:
    typedef std::map<std::string,
        peleus::entrance::smart_ptr> entrance_map_t;

    entrance_map_t _entrances;
};

}
}

#endif // PELEUS_SRC_MODULES_ENTRANCE_REPERTORY_H
