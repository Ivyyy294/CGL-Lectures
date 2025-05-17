#pragma once
#include "Monster.h"
#include <string>
#include <vector>

class MonsterManager
{
public:
	void PrintInstruction() const;
	void AddMonsterFront(Monster* monster, bool silent = true);
	void AddMonsterEnd(Monster* monster, bool silent = true);
	void ProcessInstruction ();
	void DeleteMonsterList();
	void Import (const std::string& filePath);
	void SaveFile ();

private:
	Monster* m_current = nullptr;
	std::string m_filePath;
	std::vector <Monster*> m_filterList;

	void Next();
	void Back();
	void GoToIndex();
	void Print() const;
	void PrintAll() const;
	void FindMonster ();
	void AddMonster();
	void RemoveMonster();
	bool SaveFileIntern();
	void Export();

	//Help methods
	void AddAtIndex(int index, Monster* monster);
	void GetSearchPara (std::string& name, int& index) const;
};

