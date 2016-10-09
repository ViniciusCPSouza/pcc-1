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
		return patterns;
	}
}
