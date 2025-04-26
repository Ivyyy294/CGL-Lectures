#pragma once
#include "Monster.h"
#include <string>

class MonsterManager
{
public:
	void PrintInstruction() const;

	void AddMonsterFront(Monster* monster, bool silent = true);
	void AddMonsterEnd(Monster* monster, bool silent = true);

	void ProcessInstruction ();

	void DeleteMonsterList();
private:
	Monster* m_root = nullptr;

	void Print() const;
	void PrintAll() const;
	void FindMonster () const;
	void AddMonster();
	void RemoveMonster();

	//Help methods
	void AddAtIndex(int index, Monster* monster);
	std::string ToUpper (const std::string& source) const;
	void GetSearchPara (std::string& name, int& index) const;
};

