#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

#include <sys/socket.h>
#include <string>
#include "request.h"

class IMiddleware {
public:
  virtual void run(int socket, Request* request) = 0;
};

#endif
