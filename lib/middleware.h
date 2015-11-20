#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

#include <string>
#include "request.h"

class IMiddleware {
public:
  virtual void run(Request* request) = 0;
};

#endif
