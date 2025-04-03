#pragma once
#include <string>

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
	const std::string m_coinSymbol[5] = {"PP", "GP", "EP", "SP", "CP"};
	const int m_coinConversion[5] = {1000, 100, 50, 10, 1};

	int m_copper = 0;

	void PrintInvalidInput();
};

