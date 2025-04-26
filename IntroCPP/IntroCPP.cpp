// IntroCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MonsterManager.h"
//#include "romanNumeral.h"
//#include "Inventory.h"
int main()
{
	MonsterManager monsterManager;

	monsterManager.AddMonsterEnd (new Monster {"Goblin", 7});
	monsterManager.AddMonsterEnd (new Monster {"Adult Red Dragon", 256});
	monsterManager.AddMonsterEnd (new Monster {"Barlgura", 68});
	monsterManager.AddMonsterEnd (new Monster {"Goblin", 7});
	monsterManager.AddMonsterEnd (new Monster {"Ettercap", 44});
	monsterManager.AddMonsterEnd (new Monster {"Flameskull", 40});
	monsterManager.AddMonsterEnd (new Monster {"Goblin", 7});
	monsterManager.AddMonsterEnd (new Monster {"Flameskull", 40});
	monsterManager.AddMonsterEnd (new Monster {"Frost Salamander", 168});
	monsterManager.AddMonsterEnd (new Monster {"Poltergeist", 22});
	monsterManager.AddMonsterEnd (new Monster {"Star Spawn Hulk", 136});
	monsterManager.AddMonsterEnd (new Monster {"Poltergeist", 22});
	monsterManager.AddMonsterEnd (new Monster {"Gorgon", 114});
	monsterManager.AddMonsterEnd (new Monster {"Yuan-ti Malison", 66});

	monsterManager.PrintInstruction();
	monsterManager.ProcessInstruction();
	monsterManager.DeleteMonsterList();
	//Inventory inventory;
	//inventory.Populate();
	//inventory.OpenInventory();
	//RomanNumeral romanNumeral1, romanNumeral2, romanNumeralResult;
	//std::cout << "Give me two roman numerals:" << std::endl;
	//std::cin >> romanNumeral1 >> romanNumeral2;
	//romanNumeralResult = romanNumeral1 + romanNumeral2;

	//std::cout << romanNumeral1 << " + " << romanNumeral2
	//	<< " = " << romanNumeralResult;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
