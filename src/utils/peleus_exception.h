/*************************************************************************
    > File Name: peleus_exception.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 11:08:36 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_UTILS_PELEUS_EXCEPTION_H
#define PELEUS_SRC_UTILS_PELEUS_EXCEPTION_H

#include <iostream>
#include <exception>
#include <boost/exception/all.hpp>

namespace peleus {
namespace utils {

struct PeleusException:
    virtual std::exception,
    virtual boost::exception 
{
};

typedef boost::error_info<struct tag_err_str, std::string> err_str;

void inline throw_exceptionex(const char* msg) {
    throw PeleusException() << err_str(msg);
}

}
}

#endif // PELEUS_SRC_UTILS_PELEUS_EXCEPTION_H
