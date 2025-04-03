#pragma once
#include <string>
#include <iostream>

class RomanNumeral
{
public:
	RomanNumeral() {};
	RomanNumeral (const int value);
	RomanNumeral (const std::string& value);

	void setValue (const int value);
	void setValue (const std::string& value);

	int getValue() const;
	std::string getNotation() const;

	RomanNumeral operator+ (const int value) const;
	RomanNumeral operator+ (const std::string& value) const;

	RomanNumeral operator- (const int value) const;
	RomanNumeral operator- (const std::string& value) const;

	RomanNumeral& operator= (const int value);
	RomanNumeral& operator= (const std::string& value);

	friend int& operator<< (int& target, RomanNumeral& source);
	friend std::string& operator<< (std::string& target, RomanNumeral& source);
	friend std::ostream& operator<< (std::ostream& target, RomanNumeral& source);

	friend int& operator>> (int& source, RomanNumeral& target);
	friend std::string& operator>> (std::string& source, RomanNumeral& target);
	friend std::istream& operator>> (std::istream& in, RomanNumeral& target);

private:
	struct RomanLetter
	{
		const int m_value = 0;
		const char m_letter = 0;
		const int m_allowedSubstractionIndex = -1;
	};

	RomanLetter m_romanNumbers[7] = { 
		{1000, 'M', 2}
		, {500, 'D', 2}
		, {100, 'C', 4}
		, {50, 'L', 4}
		, {10, 'X', 6}
		, {5, 'V', 6}
		, {1, 'I', -1}};

	int m_value = 0;

	int toArabic (const std::string& value) const;
	std::string toRoman (const int value) const;
};
