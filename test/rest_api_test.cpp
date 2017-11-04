/* 
 * File:   rest_api_test.cpp
 * Author: Ian Esper <imesper@gmail.com>
 * 
 */

#include <gtest/gtest.h>
#include <iostream>

#include <BaseServiceServer.hpp>
#include <PostsService.hpp>

#include <cpprest/http_client.h>

using namespace std;
using namespace web;

TEST(BaseServiceTest, Authentication)
{
    // Tests factorial of negative numbers.
    utility::string_t uri = "http://localhost:2000";
    utility::string_t auth_test_uri = uri + "/authenticate";

    try
    {
        bool run = true;
        BaseServiceServer serviceServer(auth_test_uri);
        serviceServer.open().wait();
        while (run)
        {

            web::http::client::http_client client(uri);
            // First test should return 401, not sending the headers with basic auth
            uri_builder builder("/authenticate");
            client.request(http::methods::GET, builder.to_string()).then([](http::http_response response) {
                                                                       EXPECT_EQ(401, response.status_code());
                                                                   })
                .wait();

            // Second test should return 200, as the headers are set with basic auth
            http::http_request req(http::methods::GET);
            req.headers().add("Authorization", "Basic aWFuOjIxMDg3MQ==");
            req.set_request_uri("/authenticate");
            client.request(req).then([&](http::http_response response) {
                                   EXPECT_EQ(200, response.status_code());
                                   run = false;
                               })
                .wait();
        }
        serviceServer.close().wait();
    }
    catch (std::exception const &e)
    {
        cerr << e.what() << endl;
    }
    // }
}

TEST(PostsServiceTest, GetPosts)
{
    // Tests factorial of negative numbers.
    utility::string_t uri = "http://localhost:2000";
    utility::string_t posts_test_uri = uri + "/posts";

    try
    {
        PostsService postsService(posts_test_uri);

        postsService.open().wait();

        web::http::client::http_client client(uri);

        // First test should return 401, not sending the headers with basic auth
        uri_builder builder("/posts");
        client.request(http::methods::GET, builder.to_string()).then([&](http::http_response response) {
                                                                   EXPECT_EQ(401, response.status_code());

                                                               })
            .wait();

        // Second test should return 200, as the headers are set with basic auth
        http::http_request request(http::methods::GET);
        request.headers().add("Authorization", "Basic aWFuOjIxMDg3MQ==");
        request.set_request_uri("/posts");
        client.request(request).then([&](http::http_response response) {
                                   EXPECT_EQ(200, response.status_code());
                                   response.extract_json([](json::value body) {
                                       EXPECT_TRUE(body.size());
                                   });
                               })
            .wait();
        postsService.close().wait();
    }
    catch (std::exception const &e)
    {
        cerr << e.what() << endl;
    }
    // }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
