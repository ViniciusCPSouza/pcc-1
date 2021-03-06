#ifndef SHIFT_OR_H
#define SHIFT_OR_H

#include <bitset>
#include <iostream>
#include <fstream>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

#include "pattern_occurrence.h"
#include "utils.h"

namespace shift_or {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif