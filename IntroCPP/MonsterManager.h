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
	void Import (const std::string& filePath);

private:
	Monster* m_current = nullptr;

	void Next();
	void Back();
	void GoToIndex();
	void Print() const;
	void PrintAll() const;
	void FindMonster () const;
	void AddMonster();
	void RemoveMonster();

	//Help methods
	void AddAtIndex(int index, Monster* monster);
	void GetSearchPara (std::string& name, int& index) const;
};

