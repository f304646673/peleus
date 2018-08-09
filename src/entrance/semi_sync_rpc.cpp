/*************************************************************************
    > File Name: semi_sync_rpc.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 03 Apr 2018 10:16:34 PM CST
 ************************************************************************/
#include "semi_sync_rpc.h"
#include "src/modules/inter_server.h"

namespace peleus {
namespace entrance {

using peleus::modules::InterServer;

brpc::Channel& get_inter_channel() {
    return InterServer::get_mutable_instance().get_channel();
}

}
}
