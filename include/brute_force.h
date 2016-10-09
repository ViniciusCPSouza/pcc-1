#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <fstream>
#include <string>
#include <vector>

#include "pattern_occurrence.h"

namespace brute_force {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif