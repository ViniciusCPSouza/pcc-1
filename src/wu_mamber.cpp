#include "wu_mamber.h"

namespace wu_mamber {

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

			std::vector<int64_t> s;
			std::vector<int64_t> old_s;
			int64_t s_add, s_miss, s_rplc = 0;
			while (std::getline(file, line))
			{
				s.clear();
				old_s.clear();
				s_add, s_miss, s_rplc = 0;
				for (int q = 0; q <= edit; q++) s.push_back(~1L);

				// ALGORITHM
				for (int t = 0; t < line.length(); t++)
				{
					old_s = s;
					s[0] |= bitMatrix[line[t]];
					s[0] <<= 1;

					// for each edit distanece
					for (int q = 1; q <= edit; q++)
					{
						// additional character
						s_add = old_s[q - 1];

						// missing character
						s_miss = s[q - 1] << 1;

						// substitution
						s_rplc = (s_add & (old_s[q] | bitMatrix[line[t]])) << 1;

						s[q] = s_add & s_miss & s_rplc;
					}

					if ((s[edit] & (1L << pattern.length())) == 0)
					{
						data::PatternOccurrence occ;
						occ.line = line_count;
						occ.column = t;		// last column instead of first
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