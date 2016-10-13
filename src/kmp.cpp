#include "kmp.h"

namespace kmp {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;
		std::map<char, int> prefix = utils::getPrefixTable(pattern);

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;
		while (std::getline(file, line))
		{
			// ALGORITHM
			int t = 0;
			int p = 0;
			int new_p = p;
			int match_start = t;

			while (t < line.length())
			{
				// matching continues
				if (pattern[p] == line[t])
				{
					t++;
					p++;

					// final match
					// add a match and also update the match start location to the new position on the text
					if (p >= pattern.length())
					{
						data::PatternOccurrence occ;
						occ.text = line;
						occ.line = line_count;
						occ.column = match_start;
						results.push_back(occ);

						match_start = t;
					}
				}
				// align the pattern and the failed character correctly using the prefix table
				// also update the match start to where the beginning of the pattern is now located
				else if (p > 0)
				{
					new_p = prefix[p - 1];
					p = new_p;
					match_start = t - new_p;
				}
				// just shift the text, we're still at the first position of the pattern
				// also update the match start to that same location
				else
				{
					t++;
					match_start = t;
				}
			}

			line_count++;
		}

		return results;
	}
}