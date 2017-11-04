/*
 * File:   PostsService.cpp
 * Author: Ian Esper <imesper@gmail.com>
 *
 */

#include "../include/PostsService.hpp"

using namespace std;
using namespace web;

PostsService::PostsService(utility::string_t address) : BaseServiceServer(address)
{
}

PostsService::~PostsService()
{
}

void PostsService::handle_get(http::http_request message)
{
    http::status_code res = http::status_codes::Unauthorized;

    if (message.headers().has(http::header_names::authorization))
    {

        authenticate(message).then([&](const bool auth) {
            if (auth)
            {
                // Defining a hardcoded URL of a test service that returns a JSON.
                utility::string_t posts_uri = "http://jsonplaceholder.typicode.com/";

                // Instantiation a http client to consume the service.
                http::client::http_client client(posts_uri);

                // Completing the url
                uri_builder builder("/posts");

                // Making the asynchronous request. On lambda capturing variables by reference and receiving a repsonse.
                client.request(http::methods::GET, builder.to_string())
                        .then([&](http::http_response response) {
                    // If response is 200 / OK -> extract the json. If not return null value
                    if (response.status_code() == http::status_codes::OK)
                    {
                        return response.extract_json();
                    }

                    return pplx::task_from_result(json::value());
                })
                .then([&](json::value json) {
                    // Set the reply body according to the response set status to ok, even if it is empty, because empty is right.
                    message.set_body(json);
                    res = http::status_codes::OK;
                })
                // Wait the execution of this tasks
                .wait();
            }
        })
                // Handles any error on the pipeline authenticate
                .then([&](pplx::task<void> t) {
            handle_error(t, "PostsService Auth Pipeline");
        })
        .wait();
    }
    // Reply to sender.
    message.reply(res, message.body(), "application/json");
}

