#pragma once
#include <string>

struct CoinType
{
	CoinType(int coinConversion, std::string symbol);

	const std::string m_coinSymbol;
	const int m_coinConversion;
};

