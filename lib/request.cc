#include "request.h"

void Request::parseHeader(std::string requestHeader) {
    StringArray lines = Util::split(requestHeader, '\n');
    int i = 0; int count = 0;
    while (lines[i] != "\r") {
        // GET
        if (lines[i].find("GET") == 0) {
            _url = lines[i].substr(5);
            _url = _url.substr(0, _url.find(" HTTP/1.1"));
            StringArray url_parsed = Util::split(_url, '?');
            if (url_parsed.size() == 2) {
                _url = url_parsed[0];
                _params = url_parsed[1];
            }
            _method = "GET";
            printf("> METHOD: GET - URL: %s - PARAMS: %s\n", _url.c_str(), _params.c_str());
        }
        // POST
        else if (lines[i].find("POST") == 0) {
            _url = lines[i].substr(6);
            _url = _url.substr(0, _url.find(" HTTP/1.1"));
            _method = "POST";
            printf("> METHOD: POST - URL: %s\n", _url.c_str());
        }
        // Get the headers
        else {
            StringArray header_parsed = Util::split(lines[i], ':');
            if (header_parsed.size() >= 2) {
                _header.insert(std::pair<std::string, std::string>(header_parsed[0], lines[i].substr(header_parsed[0].length() + 2)));
                printf("> [%s] = %s\n", header_parsed[0].c_str(), lines[i].substr(header_parsed[0].length() + 2).c_str());
            } else {
                printf("==%s.\n", lines[i].c_str());
            }
        }
        count += lines[i].length() + 1;
        i++;
    }
    printf("Stopped at: %d\n\n", count);
    printf("Remain data: %s\n", requestHeader.substr(count).c_str());
    // TODO: Get data
}

RequestHeader Request::getHeaders() {
    return _header;
}

std::string Request::getUrl() {
    return _url;
}

std::string Request::getMethod() {
    return _method;
}

std::string Request::getParams() {
    return _params;
}

StringPair Request::getPostData() {
    return _postdata;
}
