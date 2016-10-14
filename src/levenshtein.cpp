#include "levenshtein.h"

namespace levenshtein {

	std::vector<data::PatternOccurrence> search(std::string filename, std::string pattern, int edit)
	{
		std::vector<data::PatternOccurrence> results;

		std::ifstream file(filename);
		std::string line;
		int line_count = 0;

		std::vector<int> old_row;
		std::vector<int> row;
		int c_add, c_miss, c_rplc, c_rplc_cost = 0;

		while (std::getline(file, line))
		{
			old_row.clear();
			for (int x = 0; x <= line.length(); x++) old_row.push_back(0);

			for (int p = 0; p < pattern.length(); p++)
			{
				row.clear();
				row.push_back(p + 1);
				for (int t = 0; t < line.length(); t++)
				{
					c_add = row[t] + 1;
					c_miss = old_row[t + 1] + 1;
					c_rplc_cost = (pattern[p] == line[t]) ? 0 : 1;
					c_rplc = old_row[t] + c_rplc_cost;

					row.push_back(std::min(std::min(c_add, c_miss), c_rplc));
				}

				old_row = row;
			}

			for (int c = 0; c < row.size(); c++)
			{
				if (row[c] <= edit)
				{
					data::PatternOccurrence occ;
					occ.line = line_count;
					occ.column = c - 1;		// last column instead of first
					results.push_back(occ);
				}
			}

			line_count++;
		}

		return results;
	}
}