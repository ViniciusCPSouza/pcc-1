#include "shift_or.h"
#include "utils.h"

namespace shift_or {
	// Build a matrix with the rows representing the characters of the alphabet
	// and the columns being the positions of the pattern
	std::map<int, std::bitset<64>> getBitMatrix(std::string pattern)
	{
		std::map<int, std::bitset<64>> bitMatrix;

		for (int c = 0; c < 256; c++)
		{
			std::bitset<64> bits("1111111111111111111111111111111111111111111111111111111111111111");

			for (int p = 0; p < pattern.length(); p++)
			{
				if (pattern[p] == (char) c) bits[63 - p] = 0;
			}

			bitMatrix[c] = bits;
		}

		return bitMatrix;	
	}

	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;
		std::map<int, std::bitset<64>> bitMatrix = getBitMatrix(pattern);

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;
		while (std::getline(file, line))
		{
			// supporting pattern with length up to 64 characters
			std::bitset<64> s("1111111111111111111111111111111111111111111111111111111111111111");

			// ALGORITHM
			for (int t = 0; t < line.length(); t++)
			{
				s = (s >> 1) | bitMatrix[(int)line[t]];
				if (s[63 - (pattern.length() - 1)] == 0)
				{
					data::PatternOccurrence occ;
					occ.text = line;
					occ.line = line_count;
					occ.column = t - pattern.length() + 1;
					results.push_back(occ);
				}
			}

			line_count++;
		}

		return results;
	}
}