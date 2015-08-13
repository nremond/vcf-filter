#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

template <typename T>
std::string join(const T& v, const std::string& delim);

std::vector<std::string> splitn(std::vector<std::string> &vec, std::string &str, char delimiter);

std::pair<std::string, std::string> split2(std::string &str, char delimiter);


#endif /* UTILITIES_H */