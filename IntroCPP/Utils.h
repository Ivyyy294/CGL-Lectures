#pragma once
#include <string>
#include <vector>

class Utils
{
	public:
		static std::vector<std::string> StrSplit (const std::string& data, const char c);
		static std::vector<std::string> StrSplit (const std::string& data, const std::string& str);
		static std::string StrRemove (const std::string& data, const std::string& str);
		static std::string StrToUpper(const std::string& val);
};

