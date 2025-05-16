#pragma once
#include <string>
#include <vector>

class Utils
{
	public:
		static std::vector<std::string> StrSplit (const std::string& data, const char c);
		static std::string StrToUpper(const std::string& val);
};

