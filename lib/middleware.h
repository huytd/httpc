#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

class IMiddleware {
public:
  virtual void run(const char * request_header) = 0;
};

#endif
