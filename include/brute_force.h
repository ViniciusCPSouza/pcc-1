#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <string>
#include <vector>

#include "pattern_occurrence.h"

namespace brute_force {
	std::vector<PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif