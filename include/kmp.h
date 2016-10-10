#ifndef KMP_H
#define KMP_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "pattern_occurrence.h"

namespace kmp {
	std::map<char, int> getPrefixTable(std::string pattern);
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif