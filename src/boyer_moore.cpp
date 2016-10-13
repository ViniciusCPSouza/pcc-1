#include "boyer_moore.h"
#include "utils.h"

namespace boyer_moore {
	// for all chars in the alphabet, update their right-most position in the pattern
	std::vector<int> getBadCharacterTable(std::string pattern)
	{
		std::vector<int> table;
		table.assign(256, -1);

		for (int i = 0; i < pattern.length(); i++)
		{
			table[(int)pattern[i]] = i;
		}

		return table;
	}

	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;

		std::vector<int> bad_character_table = getBadCharacterTable(pattern);

		for(std::vector<int>::iterator it = bad_character_table.begin(); it < bad_character_table.end(); it++)
		{
			std::cout << *it << ",";
		}
		std::cout << std::endl;

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;
		while (std::getline(file, line))
		{
			// SETUP
			// ...

			// ALGORITHM
			int t = 0;
			int p = 0;

			while (t < line.length())
			{
				// ...
			}

			line_count++;
		}

		return results;
	}
}