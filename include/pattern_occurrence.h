#ifndef PATTERN_OCCURRENCE_H
#define PATTERN_OCCURRENCE_H

#include <string>

namespace data
{
	typedef struct PatternOccurrence
	{
		std::string text;
		int line;
		int column;
	} PatternOccurrence;
}

#endif