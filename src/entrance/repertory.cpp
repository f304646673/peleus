/*************************************************************************
    > File Name: repertory.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 06:43:42 PM CST
 ************************************************************************/
#include "repertory.h"
#include "src/modules/creator_repertory.h"

namespace peleus {
namespace entrance {

bool register_creator(const char* name, creator_t creator) {
    return peleus::modules::CreatorRepertory::
        get_mutable_instance().register_creator(name, creator);
}

creator_t lookup_creator(const char* name) {
    return peleus::modules::CreatorRepertory::
        get_mutable_instance().lookup_creator(name);
}

}
}
