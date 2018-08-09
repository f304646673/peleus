/*************************************************************************
    > File Name: ut_http_conns.cpp
    > Author: fangliang
    > Mail: fangliang1988@gmail.com 
    > Created Time: Thu 22 Mar 2018 07:13:08 PM CST
 ************************************************************************/
#include "gtest/gtest.h"
#include "src/plugins/http_conns/http_conns.h"

using peleus::plugins::http_conns::HttpConns;
using peleus::plugins::HttpRequest;
using peleus::plugins::HttpResponse;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace peleus {
namespace unit_test {

class UtHttpConns :
    public ::testing::Test 
{
protected:
    virtual void SetUp() {
        HttpConns::get_mutable_instance().init("./conf/http_conns/");
    }
    virtual void TearDown() {}
};

TEST_F(UtHttpConns, CheckDNS) {
    HttpRequest request;
    request.set_conn_name("test_host");
    request.set_uri("/");
    request.set_post(false);

    HttpResponse response;
    bool ret = HttpConns::get_mutable_instance().access(request, response);
    ASSERT_TRUE(ret);
    ASSERT_EQ(0, response.error_code());
}

TEST_F(UtHttpConns, CheckIpPort) {
    HttpRequest request;
    request.set_conn_name("test_ip");
    request.set_uri("/");
    request.set_post(false);
    //request.set_post_data("{\"message\":\"hello world!\"}");

    HttpResponse response;
    bool ret = HttpConns::get_mutable_instance().access(request, response);
    ASSERT_TRUE(ret);
    ASSERT_EQ(0, response.error_code());
}

}
}
