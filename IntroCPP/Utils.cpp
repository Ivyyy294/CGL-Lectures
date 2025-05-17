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

std::vector<std::string> Utils::StrSplit(const std::string& data, const std::string& str)
{
	std::vector<std::string> substrings;
	size_t offset = 0;
	size_t index = data.find(str, offset);
	size_t strLength = str.length();

	while (index != std::string::npos)
	{
		substrings.emplace_back(data.substr(offset, index - offset));
		offset = index + strLength;
		index = data.find(str, offset);
	}

	if (offset < data.length())
		substrings.emplace_back(data.substr(offset, data.length() - offset));

	return substrings;
}

std::string Utils::StrRemove(const std::string& data, const std::string& str)
{
	std::string value = data;
	size_t index = data.find(str);

	while (index != std::string::npos)
	{
		value.erase(index, 1);
		index = value.find(str);
	}

	return value;
}

std::string Utils::StrToUpper(const std::string& val)
{
	std::string result;

	for (size_t i = 0; i < val.length(); ++i)
		result += std::toupper(val[i]);

	return result;
}
