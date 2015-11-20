#ifndef __ROUTER_H__
#define __ROUTER_H__

#include <stdio.h>
#include <string>
#include "middleware.h"
#include "request.h"

class Router: public IMiddleware {
public:
  Router();
  void run(int socket, Request* request);
};

#endif
