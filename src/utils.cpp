#include "utils.h"

namespace utils {
	std::string join(const std::vector<std::string> & data, std::string delimiter)
	{
		std::stringstream ss;
		for (std::vector<std::string>::const_iterator it = data.begin(); it < data.end(); it++)
		{
			ss << *it;
			if (it != data.end() - 1) ss << delimiter;
		}
		return ss.str();
	}

	std::vector<std::string> getPatterns(std::string filename)
	{
		std::vector<std::string> patterns;
		std::ifstream file(filename);
		std::string str;

		if(file.fail()){
      throw std::runtime_error("Patterns file does not exist!");
    }

		while (std::getline(file, str))
		{
		  patterns.push_back(str);
		}

		file.close();

		return patterns;
	}

	std::map<char, int> getPrefixTable(std::string pattern)
	{
		std::map<char, int> table;
		int max_prefix = 0;
		int current = 1;

		if (pattern.length() > 0)
		{
			// For each position of the pattern, calculate what is the longest prefix that is also a suffix
			table[0] = 0;
			while (current < pattern.length())
			{
				// increment the prefix size by one, because we found another of its elements
				if (pattern[max_prefix] == pattern[current])
				{
					max_prefix++;
					table[current] = max_prefix;
					current++;
				}
				// we were tracking a prefix that was also a suffix, but it failed,
				// so we go back to search for a smaller prefix that is also a suffix.
				// we ask the character at the 'max_prefix' position (the end of our longest prefix) if
				// he is also a prefix by taking it's max_prefix value as our own
				// this way, we'll be trying to continue a smaller prefix
				else if (max_prefix != 0)
				{
					max_prefix = table[max_prefix-1];
				}
				else
				{
					table[current] = 0;
					current++;
				}
			}
		}

		return table;
	}

	// Build a matrix with the rows representing the characters of the alphabet
	// and the columns being the positions of the pattern
	std::vector<int64_t> getBitMatrix(std::string pattern)
	{
		std::vector<int64_t> bitMatrix;

		for (int c = 0; c < 256; c++) bitMatrix.push_back(~0);
		for (int p = 0; p < pattern.length(); p++) bitMatrix[pattern[p]] &= ~(1UL << p);

		return bitMatrix;
	}
}
