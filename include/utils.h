#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>

namespace utils {
	std::string join(const std::vector<std::string> & data, std::string delimiter);
	std::vector<std::string> getPatterns(std::string filename);
	std::map<char, int> getPrefixTable(std::string pattern);
}

#endif