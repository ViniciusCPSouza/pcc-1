#ifndef SHIFT_OR_H
#define SHIFT_OR_H

#include <bitset>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "pattern_occurrence.h"

namespace shift_or {
	std::map<int, std::bitset<64>> getBitMatrix(std::string pattern);
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif