#pragma once
#include <string>
#include "CoinType.h"

class CurrencyManager
{
public:
	CurrencyManager();
	CurrencyManager(int platinum, int gold, int electrum, int silver, int copper);

	void AddCurrency ();

	//Called internally by AddCurrency(const std::string& currency )
	void AddCurrency (int platinum, int gold, int electrum, int silver, int copper);

	//Called internally AddCurrency (int copper, int silver, int electrum, int gold, int platinum)
	void AddCopper (int copper);
	void AddSilver (int silver);
	void AddElectrum (int electrum);
	void AddGold (int gold);
	void AddPlatinum (int platinum);

	std::string GetCurrentCurrencyAsString();

	//Called internally by GetCurrentCurrencyAsString()
	void GetCurrentCurrency (int& platinum, int& gold, int& electrum, int& silver, int& copper);

private:
	//Symbols for currencys
	const CoinType m_coinTypes[5] = { {1000, "PP"}, {100, "GP"}, {50, "EP"}, {10, "SP"}, {1, "CP"} };

	int m_copper = 0;

	void PrintInvalidInput();
};

