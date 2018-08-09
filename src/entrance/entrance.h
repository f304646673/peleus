/*************************************************************************
    > File Name: entrance.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 06:24:30 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_ENTRANCE_ENTRANCE_H
#define PELEUS_SRC_ENTRANCE_ENTRANCE_H

#include "component.h"
#include <boost/shared_ptr.hpp>

namespace peleus {
namespace entrance {

class Entrance : public Component {
public:
    explicit Entrance(const char* name) : Component(name) {
    };
    virtual ~Entrance() {};
public:
    virtual void on_init(const char*) = 0;
    virtual void reset() = 0;
};

typedef boost::shared_ptr<Entrance> smart_ptr;
typedef smart_ptr (*creator_t)(const char*);

}
}

#endif // PELEUS_SRC_ENTRANCE_ENTRANCE_H

