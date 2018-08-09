/*************************************************************************
    > File Name: config_conv.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 08:37:40 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_UTILS_CONFIG_CONV_H
#define PELEUS_SRC_UTILS_CONFIG_CONV_H

#include <string>
#include <fstream>
#include <streambuf> 
#include <butil/logging.h>
#include <boost/filesystem.hpp>
#include <google/protobuf/text_format.h>

namespace peleus {
namespace utils {

template <class T>
bool file2conf(const char* path, T& t) {
    if (!boost::filesystem::exists(path)) {
        LOG(ERROR) << path << " is not exist";
        return false;
    }
    std::ifstream infile(path);
    std::string content = std::string(std::istreambuf_iterator<char>(infile), 
            std::istreambuf_iterator<char>());
    return  google::protobuf::TextFormat::ParseFromString(content, &t);
}

}
}

#endif // PELEUS_SRC_UTILS_CONFIG_CONV_H
