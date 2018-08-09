/*************************************************************************
    > File Name: set_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 07:10:28 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_SET_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_SET_SERIALIZATION_H

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
class SetSerialization : public Serialization<std::set<T> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_SET_SERIALIZATION_H
