#include "shift_or.h"

namespace shift_or {
	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;

		// supporting pattern with length up to 64 characters
		if (pattern.length() <= 63)
		{
			std::vector<int64_t> bitMatrix = utils::getBitMatrix(pattern);

			std::ifstream file(filename);
			std::string line;
			int line_count = 0;
			int64_t s = 0;
			while (std::getline(file, line))
			{
				s = ~1L;

				// ALGORITHM
				for (int t = 0; t < line.length(); t++)
				{
					s |= bitMatrix[line[t]];
					s <<= 1;
					if ((s & (1L << pattern.length())) == 0)
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
		}
		else
		{
			std::cout << "Pattern longer than 64 characters!" << std::endl;
		}

		return results;
	}
}