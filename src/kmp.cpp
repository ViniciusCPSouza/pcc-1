#include "kmp.h"

namespace kmp {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;
		while (std::getline(file, line))
		{
			// SETUP
			// ...

			// ALGORITHM
			// ...

			line_count++;
		}

		return results;
	}
}