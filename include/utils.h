#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <bitset>
#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>

namespace utils {
	std::string join(const std::vector<std::string> & data, std::string delimiter);
	std::vector<std::string> getPatterns(std::string filename);
	std::map<char, int> getPrefixTable(std::string pattern);
	std::vector<int64_t> getBitMatrix(std::string pattern);
}

#endif