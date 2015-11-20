#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <vector>

#define StringArray std::vector<std::string>
#define StringPair std::map<std::string, std::string>
#define RequestHeader std::map<std::string, std::string>

class Util {
public:
    static std::vector<std::string> split(const std::string& s, char c);
};

#endif
