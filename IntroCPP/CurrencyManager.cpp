#include "CurrencyManager.h"
#include <string.h>
#include <iostream>

CurrencyManager::CurrencyManager()
{
}

CurrencyManager::CurrencyManager(int platinum, int gold, int electrum, int silver, int copper)
{
	AddCurrency(platinum, gold, electrum, silver, copper);
}

void CurrencyManager::AddCurrency()
{
	std::cout << "Enter coin update (e.g., '+ 2 GP' or '- 3 CP')" << std::endl;

	char sign;
	std::string coinType;
	int quantity;

	std::cin >> sign;
	
	if (sign != '-' && sign != '+')
	{
		PrintInvalidInput();
		return;
	}
	
	std::cin >> quantity >> coinType;

	int index = -1;

	for (int i = 0; i < 5; ++i)
	{
		if (coinType == m_coinTypes[i].m_coinSymbol)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		int delta = quantity * m_coinTypes[index].m_coinConversion;

		if (sign == '-')
			delta = -delta;

		AddCopper(delta);
	}
	else
		PrintInvalidInput();
}

void CurrencyManager::AddCurrency(int platinum, int gold, int electrum, int silver, int copper)
{
	AddPlatinum(platinum);
	AddGold(gold);
	AddElectrum(electrum);
	AddSilver(silver);
	AddCopper(copper);
}

void CurrencyManager::AddCopper(int copper)
{
	m_copper += copper * m_coinTypes[4].m_coinConversion;
}

void CurrencyManager::AddSilver(int silver)
{
	m_copper += silver * m_coinTypes[3].m_coinConversion;
}

void CurrencyManager::AddElectrum(int electrum)
{
	m_copper += electrum * m_coinTypes[2].m_coinConversion;
}

void CurrencyManager::AddGold(int gold)
{
	m_copper += gold * m_coinTypes[1].m_coinConversion;
}

void CurrencyManager::AddPlatinum(int platinum)
{
	m_copper += platinum * m_coinTypes[0].m_coinConversion;
}

std::string CurrencyManager::GetCurrentCurrencyAsString()
{
	int currency[5];
	std::string currencyStr;

	GetCurrentCurrency(currency[0], currency[1], currency[2], currency[3], currency[4]);


	for (size_t i = 0; i < 5; ++i)
	{
		if (currency[i] > 0)
		{
			if (currencyStr.length() > 0)
				currencyStr += ", ";

			currencyStr += std::to_string(currency[i]) + m_coinTypes[i].m_coinSymbol;
		}
	}
	return currencyStr;
}

void CurrencyManager::GetCurrentCurrency(int& platinum, int& gold, int& electrum, int& silver, int& copper)
{
	int coinsLeft = m_copper;

	platinum = 0;
	gold = 0;
	electrum = 0;
	silver = 0;
	copper = 0;

	platinum = coinsLeft / m_coinTypes[0].m_coinConversion;
	coinsLeft = coinsLeft % m_coinTypes[0].m_coinConversion;

	gold = coinsLeft / m_coinTypes[1].m_coinConversion;
	coinsLeft = coinsLeft % m_coinTypes[1].m_coinConversion;

	electrum = coinsLeft / m_coinTypes[2].m_coinConversion;
	coinsLeft = coinsLeft % m_coinTypes[2].m_coinConversion;

	silver = coinsLeft / m_coinTypes[3].m_coinConversion;
	coinsLeft = coinsLeft % m_coinTypes[3].m_coinConversion;

	copper = coinsLeft / m_coinTypes[4].m_coinConversion;
	coinsLeft = coinsLeft % m_coinTypes[4].m_coinConversion;
}

void CurrencyManager::PrintInvalidInput()
{
	std::cin.clear();
	std::cout << "Invalid input!" << std::endl;
}
