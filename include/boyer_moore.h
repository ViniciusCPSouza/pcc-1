#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <fstream>
#include <string>
#include <vector>

#include "pattern_occurrence.h"

namespace boyer_moore {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif