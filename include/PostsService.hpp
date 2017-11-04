/* 
 * File:   PostsService.h
 * Author: Ian Esper <imesper@gmail.com>
 *
 */

#ifndef PostsSERVICE_H
#define PostsSERVICE_H

#include <BaseServiceServer.hpp>
#include <cpprest/http_client.h>

/**
 * @brief The PostsService class derived from BaseServiceServer
 */
class PostsService : public BaseServiceServer
{
public:
    /**
   * @brief PostsService Constructor
   * @param address Complete address to listen. <http://localhost:2000>
   */
  PostsService(utility::string_t address);
  virtual ~PostsService();
  /**
   * @brief handle_get Function that handles GET http method form the posts service class.
   * @param message Http Request message
   */
  void handle_get(web::http::http_request message);

};

#endif /* PostsSERVICE_H */
