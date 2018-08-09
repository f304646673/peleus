/*************************************************************************
    > File Name: serialization.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 03:11:14 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_STLSERIALIZATION_SERIALIZATION_H
#define PELEUS_SRC_STLSERIALIZATION_SERIALIZATION_H

#include <string>
#include <sstream>
#include <boost/archive/binary_oarchive.hpp>  
#include <boost/archive/binary_iarchive.hpp>  

namespace peleus {
namespace stl_serialization {

template<class T>
class Serialization : public T {
public:

    void serialization(std::ostringstream& ostream) {
        boost::archive::binary_oarchive oa(ostream);
        oa << *this;
    }

    void unserialization(std::istringstream& istream) {
        boost::archive::binary_iarchive ia(istream);
        ia >> *this;
    }
private:  
    friend class boost::serialization::access;  

    template<class Archive>  
    void serialize(Archive& ar, const unsigned int version) {  
        ar & boost::serialization::base_object<T>(*this);  
    }
};

}
}

#endif // PELEUS_SRC_STLSERIALIZATION_SERIALIZATION_H
