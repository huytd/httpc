#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "util.h"

class Request {
private:
    RequestHeader _header;
    std::string _url;
    std::string _method;
    std::string _params;
    StringPair _postdata;

public:
    void parseHeader(std::string requestHeader);
    RequestHeader getHeaders();
    std::string getUrl();
    std::string getMethod();
    std::string getParams();
    StringPair getPostData();
};

#endif
