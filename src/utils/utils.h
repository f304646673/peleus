/*************************************************************************
    > File Name: utils.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Fri 23 Mar 2018 11:12:45 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_UTILS_UTILS_H
#define PELEUS_SRC_UTILS_UTILS_H

#include "peleus_exception.h"

#define FALSE_THROW(check, fmt, arg...)                         \
    do {                                                        \
        if (!(check)) {                                         \
            char err_info[1024];                                \
            snprintf(err_info, sizeof(err_info), fmt, ## arg);  \
            peleus::utils::throw_exceptionex(err_info);\
        }                                                       \
    } while (0);                                                \

#endif // PELEUS_SRC_UTILS_UTILS_H
