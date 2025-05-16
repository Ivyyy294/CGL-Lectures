#include "Utils.h"

std::vector<std::string> Utils::StrSplit(const std::string& data, const char c)
{
	std::vector<std::string> substrings;
	size_t offset = 0;
	size_t index = data.find (c, offset);

	while (index != std::string::npos)
	{
		substrings.emplace_back (data.substr (offset, index - offset));
		offset = index + 1;
		index = data.find(c, offset);
	}

	if (offset < data.length())
		substrings.emplace_back(data.substr(offset, data.length() - offset));

    return substrings;
}

std::string Utils::StrToUpper(const std::string& val)
{
	std::string result;

	for (size_t i = 0; i < val.length(); ++i)
		result += std::toupper(val[i]);

	return result;
}
