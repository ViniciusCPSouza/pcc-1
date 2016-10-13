#ifndef WU_MAMBER_H
#define WU_MAMBER_H

#include <bitset>
#include <iostream>
#include <fstream>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

#include "pattern_occurrence.h"
#include "utils.h"

namespace wu_mamber {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit);
}

#endif