/*************************************************************************
    > File Name: semi_sync_rpc.h
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Tue 03 Apr 2018 02:25:10 PM CST
 ************************************************************************/
#ifndef PELEUS_SRC_ENTRANCE_SEMI_SYNC_RPC_H
#define PELEUS_SRC_ENTRANCE_SEMI_SYNC_RPC_H

#include <string>
#include <vector>
#include <brpc/server.h>
#include <brpc/channel.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace peleus {
namespace entrance {

brpc::Channel& get_inter_channel();

using OnRPCDoneCb = boost::function<void(::google::protobuf::RpcController*, 
                                            ::google::protobuf::Closure*)>;

class OnRPCDone : public google::protobuf::Closure {
public:
    void Run() {
        if (_cntl.Failed()) {
            //printf("client error %s\n", _cntl.ErrorText().c_str());
            _suc = false;
        } else {
            //printf("client receive suc\n");
            _suc = true;
        }
    }

    void excute(OnRPCDoneCb& m, int timeout) {
        if (timeout > 0) {
            _cntl.set_timeout_ms(timeout);
        }
        _id = _cntl.call_id();
        m(&_cntl, this);
    }

    bool join() {
        brpc::Join(_id);
        return _suc;
    }

private:
    bool _suc = false;
    bthread_id_t _id;
    brpc::Controller _cntl;
};

class SemiSyncRpc {
public:
    template<class TS, class TM, class TREQ, class TRES>
    void add(brpc::Channel* channel, TM m, const TREQ* request, TRES* response, int timeout = -1) {
        OnRPCDone* done = new OnRPCDone;
        if (!channel) {
            brpc::Channel& ref_channel = get_inter_channel();
            channel = &ref_channel;
        }
        TS stub(channel);
        OnRPCDoneCb method = boost::bind(m, &stub, _1, request, response, _2);
        done->excute(method, timeout);
        _vec_done.push_back(done);
    }

    void join() {
        for (auto it = _vec_done.begin(); it != _vec_done.end(); it++) {
            (*it)->join();
            delete (*it);
        }
    }
private:
    std::vector<OnRPCDone*> _vec_done;
};


template<class TRES>
static void OnRPCDone(baidu::rpc::Controller* cntl, TRES* response) {
    std::unique_ptr<TRES> response_guard(response);
    std::unique_ptr<baidu::rpc::Controller> cntl_guard(cntl);
    if (cntl->Failed()) {
    } else {
    }
}

template<class TS, class TRES, class TM, class TREQ>
void asyn_rpc_without_response(baidu::rpc::Channel* channel,
        TM m, const TREQ* request, int timeout = -1)
 {
    TRES* new_response = new TRES();
    if (!channel) {
        baidu::rpc::Channel& ref_channel = get_inter_channel();
        channel = &ref_channel;
    }
    TS stub(channel);
    OnRPCDoneCb method = boost::bind(m, &stub, _1, request, new_response, _2);

    baidu::rpc::Controller* cntl = new baidu::rpc::Controller();
    auto func = OnRPCDone<TRES>;
    google::protobuf::Closure* done = baidu::rpc::NewCallback(func, cntl, new_response);

    method(cntl, done);
}

}
}

#endif // PELEUS_SRC_ENTRANCE_SEMI_SYNC_RPC_H
