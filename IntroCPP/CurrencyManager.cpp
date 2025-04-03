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
		if (coinType == m_coinSymbol[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		int delta = quantity * m_coinConversion[index];

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
	m_copper += copper * m_coinConversion[4];
}

void CurrencyManager::AddSilver(int silver)
{
	m_copper += silver * m_coinConversion[3];
}

void CurrencyManager::AddElectrum(int electrum)
{
	m_copper += electrum * m_coinConversion[2];
}

void CurrencyManager::AddGold(int gold)
{
	m_copper += gold * m_coinConversion[1];
}

void CurrencyManager::AddPlatinum(int platinum)
{
	m_copper += platinum * m_coinConversion[0];
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
			currencyStr += std::to_string(currency[i]) + m_coinSymbol[i];

			if (i < 4)
				currencyStr += ", ";
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

	platinum = coinsLeft / m_coinConversion[0];
	coinsLeft = coinsLeft % m_coinConversion[0];

	gold = coinsLeft / m_coinConversion[1];
	coinsLeft = coinsLeft % m_coinConversion[1];

	electrum = coinsLeft / m_coinConversion[2];
	coinsLeft = coinsLeft % m_coinConversion[2];

	silver = coinsLeft / m_coinConversion[3];
	coinsLeft = coinsLeft % m_coinConversion[3];

	copper = coinsLeft / m_coinConversion[4];
	coinsLeft = coinsLeft % m_coinConversion[4];
}

void CurrencyManager::PrintInvalidInput()
{
	std::cin.clear();
	std::cout << "Invalid input!" << std::endl;
}
