/**
 * @file type_conv.h
 * @author fangliang1988@gmail.com
 * @date 2015/07/16 02:37:53
 * @brief 
 *  
 **/
#ifndef  PELEUS_SRC_UTILS_TYPE_CONV_H
#define  PELEUS_SRC_UTILS_TYPE_CONV_H

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

template<class T>
std::string t2string(T v) {
    std::string ret;
    try {
        ret = boost::lexical_cast<std::string>(v);
    }
    catch (boost::bad_lexical_cast& e) {
        ret = "";
    }
    catch (std::bad_cast& e) {
        ret = "";
    }
    return ret;
}

template<class T>
T string2t(const std::string& v) {
    BOOST_MPL_ASSERT_MSG(
            (boost::is_same<T, int>::value || 
             boost::is_same<T, long>::value || 
             boost::is_same<T, unsigned long>::value ||
             boost::is_same<T, unsigned int>::value ||
             boost::is_same<T, unsigned long long>::value), 
            NON_INTEGRAL_TYPES_ARE_NOT_ALLOWED, (T));

    T ret = 0;
    try {
        ret = boost::lexical_cast<T>(v);
    }
    catch (boost::bad_lexical_cast& e) {
        ret = 0;
    }
    catch (std::bad_cast& e) {
        ret = 0;
    }
    return ret;
}

#endif  //PELEUS_SRC_UTILS_TYPE_CONV_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
