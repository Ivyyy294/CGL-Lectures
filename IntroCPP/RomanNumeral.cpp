#include "RomanNumeral.h"

RomanNumeral::RomanNumeral(const int value)
	: m_value (value)
{}

RomanNumeral::RomanNumeral(const std::string& value)
	: m_value (toArabic (value))
{}

RomanNumeral RomanNumeral::operator+(const int value) const
{
	return RomanNumeral(m_value + value);
}

RomanNumeral RomanNumeral::operator+(const std::string& value) const
{
	return RomanNumeral(m_value + toArabic(value));
}

RomanNumeral RomanNumeral::operator-(const int value) const
{
	return RomanNumeral(m_value - value);
}

RomanNumeral RomanNumeral::operator-(const std::string& value) const
{
	return RomanNumeral(m_value - toArabic(value));
}

RomanNumeral& RomanNumeral::operator=(const int value)
{
	m_value = value;
	return *this;
}

RomanNumeral& RomanNumeral::operator=(const std::string& value)
{
	m_value = toArabic(value);
	return *this;
}

void RomanNumeral::setValue(const int value)
{
	m_value = value;
}

void RomanNumeral::setValue(const std::string& value)
{
	m_value += toArabic(value);
}

int RomanNumeral::getValue() const
{
	return m_value;
}

std::string RomanNumeral::getNotation() const
{
	return toRoman(m_value);
}

int RomanNumeral::toArabic(const std::string& value) const
{
	size_t strIndex = 0;
	int arabicValue = 0;

	for (size_t strIndex = 0; strIndex < value.length(); ++strIndex)
	{
		for (size_t i = 0; i < 7; ++i)
		{
			const char currentChar = std::toupper (value[strIndex]);
			const char currentLetter = m_romanNumbers[i].m_letter;
			const int currentLetterValue = m_romanNumbers[i].m_value;

			if (currentChar == currentLetter)
			{
				arabicValue += currentLetterValue;
				break;
			}
			else if (strIndex + 1 < value.length())
			{
				const char nextChar = value[strIndex + 1];

				int substractionIndex = m_romanNumbers[i].m_allowedSubstractionIndex;
				const char substractionLetter = m_romanNumbers[substractionIndex].m_letter;

				if (currentChar == substractionLetter && nextChar == currentLetter)
				{
					const int substractionLetterValue = m_romanNumbers[substractionIndex].m_value;
					
					arabicValue += currentLetterValue - substractionLetterValue;

					//Additional index increase
					strIndex++;
					break;
				}
			}
		}
	}

	return arabicValue;
}

std::string RomanNumeral::toRoman(const int value) const
{
	std::string romanVal = "";
	int bufferValue = value;

	for (size_t i = 0; i < 7 && bufferValue > 0; ++i)
	{
		size_t letterCoefficient = bufferValue / m_romanNumbers[i].m_value;
		
		if (letterCoefficient > 0)
		{
			bufferValue = bufferValue % m_romanNumbers[i].m_value;
	
			for (size_t j = 0; j < letterCoefficient; ++j)
				romanVal += m_romanNumbers[i].m_letter;
		}

		//Check for posssible Substraction
		int substractionIndex = m_romanNumbers[i].m_allowedSubstractionIndex;

		if (substractionIndex >= 0)
		{
			int checkValue = m_romanNumbers[i].m_value - m_romanNumbers[substractionIndex].m_value;
			letterCoefficient = bufferValue / checkValue;

			if (bufferValue >= checkValue)
			{
				bufferValue -= checkValue;
				romanVal += m_romanNumbers[substractionIndex].m_letter;
				romanVal += m_romanNumbers[i].m_letter;
			}
		}
	}

	if (romanVal.length() == 0)
		return "NULL";
	else
		return romanVal;
}

int& operator<<(int& target, RomanNumeral& source)
{
	target = source.getValue();
	return target;
}

std::string& operator<<(std::string& target, RomanNumeral& source)
{
	target = source.getNotation();
	return target;
}

std::ostream& operator<< (std::ostream& os, RomanNumeral& source)
{
	os << source.getNotation();
	return os;
}

int& operator>>(int& source, RomanNumeral& target)
{
	target.setValue(source);
	return source;
	// TODO: insert return statement here
}

std::string& operator>>(std::string& source, RomanNumeral& target)
{
	target.setValue(source);
	return source;
}

std::istream& operator>>(std::istream& in, RomanNumeral& target)
{
	// TODO: insert return statement here
	int intVal;

	in >> intVal;

	if (!in.fail())
		target = intVal;
	else
	{
		in.clear();
		std::string strVal;
		in >> strVal;
		target = strVal;
	}

	return in;
}
