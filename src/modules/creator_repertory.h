/*************************************************************************
    > File Name: creator_repertory.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 07:00:18 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_MODULES_CREATOR_REPERTORY_H
#define PELEUS_SRC_MODULES_CREATOR_REPERTORY_H

#include <map>
#include <string>
#include <boost/serialization/singleton.hpp>

#include "module.h"
#include "src/entrance/entrance.h"

namespace peleus {
namespace modules {

class CreatorRepertory : 
    public Module<CreatorRepertory>,
    public boost::serialization::singleton<CreatorRepertory>
{
    friend class Module<CreatorRepertory>;
public:
    CreatorRepertory();
    ~CreatorRepertory();
public:
    bool register_creator(const char* name, 
        peleus::entrance::creator_t creator);

    peleus::entrance::creator_t 
        lookup_creator(const char* name);

private:
    virtual void on_init(const char*) override final;
    virtual const char* name() override final;
private:
    struct cstring_compare_t {
        bool operator() (const char * str1, const char * str2) const {
            return str1 != str2 && strcmp(str1, str2) < 0;
        }
    };

    typedef std::map<const char*,
        peleus::entrance::creator_t,
        cstring_compare_t> creator_map_t;
    
    creator_map_t _creators;
};

}
}

#endif // PELEUS_SRC_MODULES_CREATOR_REPERTORY_H
