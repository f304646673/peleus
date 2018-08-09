/*************************************************************************
    > File Name: component.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 06:00:05 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_ENTRANCE_COMPONENT_H
#define PELEUS_SRC_ENTRANCE_COMPONENT_H

#include <string>

namespace peleus {
namespace entrance {

class Component {
public:
    explicit Component(const char* name) : _name(std::string(name)) {
    };
    virtual ~Component() {};
public:
    const char* name() const {
        return _name.c_str();
    };
public:
    virtual void on_init(const char* conf_path) = 0;
    virtual void reset() = 0;
private:
    Component();
private:
    std::string _name;
};

}
}

#endif // PELEUS_SRC_ENTRANCE_COMPONENT_H

