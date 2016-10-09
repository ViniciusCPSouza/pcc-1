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
			std::string::size_type start_pos = 0;
			while (( start_pos = line.find( pattern, start_pos ) ) != std::string::npos)
			{
			  data::PatternOccurrence occ;
				occ.text = line;
				occ.line = line_count;
				occ.column = start_pos;
				results.push_back(occ);
			  start_pos++;
			}
			line_count++;
		}

		return results;
	}
}