#ifndef __ROUTER_H__
#define __ROUTER_H__

#include <stdio.h>
#include "middleware.h"

class Router: public IMiddleware {
public:
  Router();
  void run(const char * request_header);
};

#endif
