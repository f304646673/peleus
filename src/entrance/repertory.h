/*************************************************************************
    > File Name: repertory.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 05:18:45 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_ENTRANCE_REPERTORY_H
#define PELEUS_SRC_ENTRANCE_REPERTORY_H

#include "entrance.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace peleus {
namespace entrance {

bool register_creator(const char*, creator_t);
creator_t lookup_creator(const char*);

template<class type> smart_ptr creator(const char* name) {
    return boost::make_shared<type>(name);
};

template<class type> bool register_class(const char* name) {
    return register_creator(name, creator<type>);
};

}
}

#endif // PELEUS_SRC_ENTRANCE_REPERTORY_H
