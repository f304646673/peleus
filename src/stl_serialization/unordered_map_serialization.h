/*************************************************************************
    > File Name: unordered_map_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 11:31:22 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_UNORDERED_MAP_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_UNORDERED_MAP_SERIALIZATION_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/binary_oarchive.hpp>  
#include <boost/archive/binary_iarchive.hpp>  

#include "serialization.h"

namespace peleus {
namespace stl_serialization {

template<class T, class T1>
class UnorderedMapSerialization : public Serialization<std::unordered_map<T, T1> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_UNORDERED_MAP_SERIALIZATION_H
