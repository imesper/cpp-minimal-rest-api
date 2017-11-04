/*
 * BaseServiceServer.cpp
 * Author: Ian Esper <imesper@gmail.com>
 *
 */

#include <BaseServiceServer.hpp>

using namespace std;

BaseServiceServer::~BaseServiceServer()
{
    close();
}

BaseServiceServer::BaseServiceServer(utility::string_t address) : address(address)
{
    try
    {
        // Create the listener smart pointer
        m_listener = make_shared<web::http::experimental::listener::http_listener>(address);
        // Start the support for GET method
        m_listener->support(web::http::methods::GET, std::bind(&BaseServiceServer::handle_get, this, placeholders::_1));
    }
    catch (const std::exception &e)
    {
        ucerr << "Constructor Error: " << e.what() << endl;
    }
}

pplx::task<void> BaseServiceServer::open()
{
    return m_listener->open().then([&](pplx::task<void> t) {
        ucout << "Listening on Address: " << this->address << endl;
        handle_error(t);
    });
}

pplx::task<void> BaseServiceServer::close()
{
    return m_listener->close().then([&](pplx::task<void> t) { handle_error(t); });
}

pplx::task<bool> BaseServiceServer::authenticate(web::http::http_request message)
{
    // Extracting the authorization field in header and returns an iterator
    auto it = message.headers().find(web::http::header_names::authorization);

    // Extract value from iterator
    utility::string_t credentials64 = it->second;

    // Check for basic authentication (Just for demontration a better method or authentication server should be used)
    if (credentials64.substr(0, 5) == "Basic")
    {
        vector<unsigned char> creds = utility::conversions::from_base64(credentials64.erase(0, 6));

        utility::string_t credentials(creds.begin(), creds.end());
        // Not authenticating with a databse not hardcoded, just check if the header exists
        return pplx::task_from_result(true);
    }
    //  returning false if auth header not found
    return pplx::task_from_result(false);
}

void BaseServiceServer::handle_get(web::http::http_request message)
{
    // Starting with unauthorize reply
    int res = web::http::status_codes::Unauthorized;

    // Checking for authorization header
    if (message.headers().has(web::http::header_names::authorization))
    {
        // Trying to authenticate. See comment on authenticate function
        authenticate(message).then([&](const bool &value) {
            if (value)
            {
                // Set reply status to 200
                res = web::http::status_codes::OK;
            }
        })
                .then([&](pplx::task<void> t) {
            handle_error(t, "BaseService");
        })
        .wait();
    }
    // Reply the sender
    message.reply(res);
}

void BaseServiceServer::handle_error(pplx::task<void> &t, utility::string_t msg)
{
    try
    {
        t.get();
    }
    catch (const std::exception &e)
    {
        ucerr << "Error handler " << msg << " " << e.what() << endl;
    }
}
