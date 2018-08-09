/*************************************************************************
    > File Name: unordered_multiset_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:40:25 AM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_UNORDERED_MULTISET_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_UNORDERED_MULTISET_SERIALIZATION_H

#include <string>
#include <sstream>
#include <unordered_set>
#include <boost/serialization/unordered_set.hpp>
#include <boost/archive/binary_oarchive.hpp>  
#include <boost/archive/binary_iarchive.hpp>  

#include "serialization.h"

namespace peleus {
namespace stl_serialization {

template<class T>
class UnorderedMultisetSerialization : public Serialization<std::unordered_multiset<T> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_UNORDERED_MULTISET_SERIALIZATION_H
