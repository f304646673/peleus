/*************************************************************************
    > File Name: map_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 11:09:11 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_MAP_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_MAP_SERIALIZATION_H

#include <map>
#include <string>
#include <sstream>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "serialization.h"

namespace peleus {
namespace stl_serialization {

template<class T, class T1>
class MapSerialization : public Serialization<std::map<T, T1> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_MAP_SERIALIZATION_H

