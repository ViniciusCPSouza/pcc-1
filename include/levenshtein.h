#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "pattern_occurrence.h"
#include "utils.h"

namespace levenshtein {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif