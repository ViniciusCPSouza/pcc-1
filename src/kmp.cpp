#include "kmp.h"

namespace kmp {
	std::map<char, int> getPrefixTable(std::string pattern)
	{
		std::map<char, int> table;
		int max_prefix = 0;

		if (pattern.length() > 0)
		{
			// For each position of the pattern, calculate what is the longest prefix that is also a suffix
			table[0] = 0;
			for (int current = 1; current < pattern.length(); current++)
			{
				// we were tracking a prefix that was also a suffix, but it failed,
				// so we go back to search for a smaller prefix that is also a suffix.
				// we ask the character at the 'max_prefix' position (the end of our longest prefix) if
				// he is also a prefix by taking it's max_prefix value as our own
				// this way, we'll be trying to continue a smaller prefix
				while (max_prefix > 0 && (pattern[max_prefix] != pattern[current])) max_prefix = table[max_prefix];

				// increment the prefix size by one, because we found another of its elements
				if (pattern[max_prefix] == pattern[current]) max_prefix++;

				// set the current char max_prefix with the value we calculated
				table[current] = max_prefix;
			}
		}

		return table;
	}

	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;
		while (std::getline(file, line))
		{
			// SETUP
			std::map<char, int> prefix = getPrefixTable(pattern);

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