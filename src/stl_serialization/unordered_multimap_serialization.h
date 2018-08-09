/*************************************************************************
    > File Name: unordered_multimap_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:12:55 AM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_UNORDERED_MULTIMAP_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_UNORDERED_MULTIMAP_SERIALIZATION_H

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
class UnorderedMultimapSerialization : public Serialization<std::unordered_multimap<T, T1> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_UNORDERED_MULTIMAP_SERIALIZATION_H
