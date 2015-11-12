#ifndef __HTTP_H__
#define __HTTP_H__

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "middleware.h"
#include "router.h"

#define MIDDLEWARE_LIMIT 10

class HTTP {
private:
  int http_socket;
  int client_socket;
  socklen_t http_address_len;
  int buffer_size;
  char * request_header;
  struct sockaddr_in http_address;
  IMiddleware* plugins[MIDDLEWARE_LIMIT];

  // Base plugins
  Router* router;

public:
  HTTP();
  void init(int port);
  void start();
  void response(const char* msg);
  void use(IMiddleware* middleware);
};

#endif
