#include "brute_force.h"

namespace brute_force {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;
		while (std::getline(file, line))
		{
			// TEXT
			for (int t = 0; t < line.length(); t++)
			{
				// PATTERN
				bool found = true;
				for (int p = 0; p < pattern.length(); p++)
				{
					if (pattern[p] != line[t + p])
					{
						found = false;
						break;
					}
				}

				if (found)
				{
					data::PatternOccurrence occ;
					occ.text = line;
					occ.line = line_count;
					occ.column = t;
					results.push_back(occ);
				}
			}
			line_count++;
		}

		return results;
	}
}