/*************************************************************************
    > File Name: creator_repertory.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 07:08:48 PM CST
 ************************************************************************/
#include "creator_repertory.h"
#include <butil/logging.h>

namespace peleus {
namespace modules {

using peleus::entrance::creator_t;
using peleus::entrance::smart_ptr;

CreatorRepertory::CreatorRepertory(void) {
}

CreatorRepertory::~CreatorRepertory(void) {
}

void CreatorRepertory::on_init(const char*) {
}

bool CreatorRepertory::register_creator(
    const char* name, creator_t creator) 
{
    if (_creators.end() != _creators.find(name)) { 
        LOG(TRACE) << name << " have registed";
        return true;
    }
    _creators[name] = creator;
    return true;
}

creator_t CreatorRepertory::lookup_creator(const char* name) {
    auto it = _creators.find(name);
    if (_creators.end() == it) { 
        LOG(FATAL) << "can't lookup " << name  << " creator";
        return NULL;
    }
    return it->second;
}

const char* CreatorRepertory::name() {
    return "creator_repertory";
}

}
}
