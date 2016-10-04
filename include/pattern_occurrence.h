#ifndef PATTERN_OCCURRENCE_H
#define PATTERN_OCCURRENCE_H

#include <string>

struct PatternOccurrence
{
	std::string file;
	int line;
	int column;
};

#endif