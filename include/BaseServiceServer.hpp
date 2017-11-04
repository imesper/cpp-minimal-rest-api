/*
 * File:   BaseServiceServer.h
 * Author: Ian Esper <imesper@gmail.com>
 *
 */

#ifndef BaseSERVICESERVER_H
#define BaseSERVICESERVER_H

#include <cpprest/http_listener.h>
#include <memory>
#include <iostream>
#include <exception>
#include <set>
#include <string>
#include <vector>
#include <cpprest/json.h>

#include <map>

using namespace std;
using namespace web;

/**
 * @brief The BaseServiceServer class
 */
class BaseServiceServer
{
public:
    /**
   * @brief BaseServiceServer Constructor
   * @param address -> Complete address to listen. <http://localhost:2000>
   */
  BaseServiceServer(utility::string_t address);

  virtual ~BaseServiceServer();
  /**
   * @brief open
   * @return Task from PPL library
   */
  pplx::task<void> open();
  /**
   * @brief close
   * @return Task from PPL library
   */
  pplx::task<void> close();
  /**
   * @brief handle_get Function that handles GET http method form the base class.
   * @param message Http Request message
   */
  virtual void handle_get(http::http_request message);


protected:

  pplx::task<bool> authenticate(http::http_request message);
  /**
   * @brief handle_error
   * @param t
   */
  static void handle_error(pplx::task<void> &t, utility::string_t msg = "");
private:
  /**
   * @brief address
   */
  utility::string_t address;
  /**
   * @brief m_listener Http Server listener.
   */
  shared_ptr<http::experimental::listener::http_listener> m_listener;
};

#endif /* BaseSERVICESERVER_H */
