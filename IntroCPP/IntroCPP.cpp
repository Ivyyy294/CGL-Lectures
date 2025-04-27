// IntroCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MonsterManager.h"

int main()
{
	MonsterManager monsterManager;

	monsterManager.AddMonsterEnd (new Monster {"Goblin", "Humanoid", 7});
	monsterManager.AddMonsterEnd (new Monster {"Adult Red Dragon", "Dragon", 256});
	monsterManager.AddMonsterEnd (new Monster {"Barlgura", "Fiend", 68});
	monsterManager.AddMonsterEnd (new Monster {"Goblin", "Humanoid", 7});
	monsterManager.AddMonsterEnd (new Monster {"Ettercap", "Monstrosity", 44});
	monsterManager.AddMonsterEnd (new Monster {"Flameskull", "Undead", 40});
	monsterManager.AddMonsterEnd (new Monster {"Goblin", "Humanoid", 7});
	monsterManager.AddMonsterEnd (new Monster {"Flameskull", "Undead", 40});
	monsterManager.AddMonsterEnd (new Monster {"Frost Salamander", "Elemental", 168});
	monsterManager.AddMonsterEnd (new Monster {"Poltergeist", "Undead", 22});
	monsterManager.AddMonsterEnd (new Monster {"Star Spawn Hulk", "Aberration", 136});
	monsterManager.AddMonsterEnd (new Monster {"Poltergeist", "Undead", 22});
	monsterManager.AddMonsterEnd (new Monster {"Gorgon", "Monstrosity", 114});
	monsterManager.AddMonsterEnd (new Monster {"Yuan-ti Malison", "Monstrosity", 66});

	monsterManager.PrintInstruction();
	monsterManager.ProcessInstruction();
	monsterManager.DeleteMonsterList();
}
