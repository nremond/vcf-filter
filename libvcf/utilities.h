#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

std::string join(const std::vector<std::string>& v, const std::string& delim);

std::vector<std::string> splitn( std::vector<std::string> &vec, const std::string &str, const char delimiter);

std::pair<std::string, std::string> split2(const std::string &str, const char delimiter);


#endif /* UTILITIES_H */