/*************************************************************************
    > File Name: multiset_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 01:02:02 AM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_MULTISET_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_MULTISET_SERIALIZATION_H

#include <set>
#include <string>
#include <sstream>
#include <boost/serialization/set.hpp>
#include <boost/archive/binary_oarchive.hpp>  
#include <boost/archive/binary_iarchive.hpp>  

#include "serialization.h"

namespace peleus {
namespace stl_serialization {

template<class T>
class MultisetSerialization : public Serialization<std::multiset<T> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_MULTISET_SERIALIZATION_H
