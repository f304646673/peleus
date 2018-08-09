/*************************************************************************
    > File Name: mysql_error.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 02 May 2018 01:29:58 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_ERROR_H
#define PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_ERROR_H

namespace peleus {
namespace plugins {
namespace mysql_conns {

const int LACK_CONNECTION = -9;
const int NO_CONNECTION = -8;
const int NULL_CONNECTION = -7;

}
}
}

#endif // PELEUS_SRC_PLUGINS_MYSQL_CONNS_MYSQL_ERROR_H
