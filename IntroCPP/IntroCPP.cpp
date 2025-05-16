// IntroCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MonsterManager.h"

int main()
{
	MonsterManager monsterManager;

	monsterManager.Import ("monsters_data.txt");

	monsterManager.PrintInstruction();
	monsterManager.ProcessInstruction();
	monsterManager.DeleteMonsterList();
}
