/*************************************************************************
    > File Name: vector_serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 03:41:16 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_VECTOR_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_VECTOR_SERIALIZATION_H

#include <vector>
#include <string>
#include <sstream>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>  
#include <boost/archive/binary_iarchive.hpp>  

#include "serialization.h"

namespace peleus {
namespace stl_serialization {

template<class T>
class VectorSerialization : public Serialization<std::vector<T> > {
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_VECTOR_SERIALIZATION_H
