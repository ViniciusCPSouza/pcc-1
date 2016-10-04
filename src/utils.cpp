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
}
