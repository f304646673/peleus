/*************************************************************************
    > File Name: mysql_visitor_service.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Wed 02 May 2018 03:07:56 PM CST
 ************************************************************************/
#include "mysql_visitor_service.h"

namespace peleus {
namespace plugins {
namespace mysql_visitor {

//using ::google::protobuf::RpcController;
//using ::peleus::plugins::MysqlVisitorServiceRequest;
//using ::peleus::plugins::MysqlVisitorServiceResponse;
//using ::google::protobuf::Closure;
using ::brpc::Controller;
using ::brpc::ClosureGuard;
using ::peleus::plugins::MysqlVisitorRow;
using ::peleus::plugins::mysql_conns::MysqlConns;
using ::peleus::plugins::mysql_conns::MysqlSession;

MysqlVisitorService::MysqlVisitorService(const char* name) :
    peleus::entrance::Entrance(name) {
}

void MysqlVisitorService::query(::google::protobuf::RpcController* controller,
    const ::peleus::plugins::MysqlVisitorServiceRequest* request,
    ::peleus::plugins::MysqlVisitorServiceResponse* response,
    ::google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    const std::string& conn_name = request->conn_name();
    const std::string& command = request->command();

    MysqlSession session;
    int ret = MysqlConns::get_mutable_instance().query(conn_name, command, session);
    parse_session(session, response);
    response->set_suc(0 == ret ? true : false);
}

void MysqlVisitorService::parse_session(
        MysqlSession& session, 
        ::peleus::plugins::MysqlVisitorServiceResponse* response)
{
    MYSQL_RES* res = session._res;
    if (!res) {
        return;
    }

    int row_size = mysql_num_rows(res);
    for (int i = 0; i < row_size; i++) {
        parse_res(res, response);
    }
}

void MysqlVisitorService::parse_res(
        MYSQL_RES* res, 
        ::peleus::plugins::MysqlVisitorServiceResponse* response)
{
    MysqlVisitorRow* row = response->add_rows();
    MYSQL_ROW res_row = mysql_fetch_row(res);
    if (!row) {
        LOG(ERROR) << "add_rows return null";
        return;
    }
    int field_size = mysql_num_fields(res); 
    for (int i = 0; i < field_size; i++) {
        row->add_column(std::string(res_row[i]));
    }

}

void MysqlVisitorService::on_init(const char* conf_path) {
}

void MysqlVisitorService::reset() {
}

}
}
}
