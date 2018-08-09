/*************************************************************************
    > File Name: traversal_floder.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 04 May 2018 06:19:11 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_UTILS_TRAVERSAL_FLODER_H
#define PELEUS_SRC_UTILS_TRAVERSAL_FLODER_H

#include <string>
#include <fstream>
#include <streambuf>
#include <butil/logging.h>
#include <functional>
#include <boost/filesystem.hpp>

namespace peleus {
namespace utils {

typedef std::function<void(const char* path)> TraversalCallback;

class TraversalFloder {
public:
    void set_callback(
            TraversalCallback traversal_floder,
            TraversalCallback traversal_file,
            const char* file_path = __FILE__)
    {
        _traversal_floder = traversal_floder;
        _traversal_file = traversal_file;
        _file_path = std::string(file_path);
    }

    void init(const char* conf_floder_path) {
        boost::filesystem::path full_path = boost::filesystem::system_complete(
                        boost::filesystem::path(std::string(conf_floder_path)));
        if (!boost::filesystem::exists(full_path)) {
            LOG(ERROR) << _file_path << conf_floder_path << " not exist";
            return;
        }
        
        if (!boost::filesystem::is_directory(full_path)) {
            LOG(ERROR) << _file_path << conf_floder_path << " is not directory";
            return;
        }

        boost::filesystem::directory_iterator end;
        for (boost::filesystem::directory_iterator iter(full_path); iter != end; ++iter) {
            if (boost::filesystem::is_directory(*iter) && _traversal_floder) {
                _traversal_floder(iter->path().string().c_str());
            }
            else if (!boost::filesystem::is_directory(*iter) && _traversal_file) {
                _traversal_file(iter->path().string().c_str());
            }
        }
    }

private:
    TraversalCallback _traversal_floder = NULL;
    TraversalCallback _traversal_file = NULL;
    std::string _file_path;
};

}
}

#endif // PELEUS_SRC_UTILS_TRAVERSAL_FLODER_H
