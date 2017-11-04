/*
 * File:   main.cpp
 * Author: Ian Esper <imesper@gmail.com>
 *
 */

#include <cstdlib>
#include <memory>
#include <iostream>
#include <exception>

#include <cxxopts.hpp>

#include <BaseServiceServer.hpp>
#include <PostsService.hpp>

using namespace std;

/**
 * @brief main Main function of the Minimal Rest API.
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
    utility::string_t host = "http://";

    try
    {
        // Using the HeardOnly cxxopts project to read GNU style arguments
        cxxopts::Options options("run_minimal-rest-api", "Starts minimal rest api server. Default host is localhost on port 2000");

        options.add_options()
                ("h,host", "Hostname", cxxopts::value<string>()->default_value("localhost"))
                ("p,port", "port to listen on", cxxopts::value<string>()->default_value("2000"))
                ("help", "Print help")
                ;


        options.parse(argc, argv);

        if (options.count("help"))
        {
            std::cout << options.help({""}) << std::endl;
            exit(0);
        }

        host += options["host"].as<string>() + ":" + options["port"].as<string>();
        ucout << host << endl;
    } catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    /* Instantiating the servers the whole CPPRESTSDK is based on PPL Parallel Patterns Library, it's
    * a parallel library from microsoft that provides a paralellism, starting a new thread whenever it's necessary.
    */
    BaseServiceServer serviceServer(host + U("/authenticate"));
    PostsService postsServer(host + U("/posts"));

    try
    {
        // Starting the base service tasks
        serviceServer.open().wait();
        // Starting the posts service tasks
        postsServer.open().wait();
        // Running indefinitely
        while (true)
            ;
    }
    catch (std::exception const &e)
    {
        // Error caught are printed on stderr
        ucerr << e.what() << endl;
    }
    return 0;
}
