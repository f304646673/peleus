/*************************************************************************
    > File Name: multimap_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 12:44:15 AM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_MULTIMAP_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_MULTIMAP_SERIALIZATION_H

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
class MultimapSerialization : public Serialization<std::multimap<T, T1> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_MULTIMAP_SERIALIZATION_H
