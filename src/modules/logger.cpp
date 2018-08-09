/*************************************************************************
    > File Name: logger.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 22 Dec 2018 06:42:07 PM CST
 ************************************************************************/
#include "logger.h"
#include <butil/logging.h>

namespace peleus {
namespace modules {

Logger::~Logger() {
}

void Logger::on_init(const char* conf_path) {
//    if (logging::ComlogSink::GetInstance()->SetupFromConfig(conf_path) != 0) {
//        LOG(ERROR) << "Fail to setup comlog from " << conf_path;
//    }
}

const char* Logger::name() {
    return "logger";
}

}
}
