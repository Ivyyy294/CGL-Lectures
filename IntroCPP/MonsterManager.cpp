#include "MonsterManager.h"
#include <iostream>
#include <cstring>

void MonsterManager::Print() const
{
	if (m_root == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else
		m_root->Print();
}
void MonsterManager::PrintAll() const
{
	if (m_root == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else
		m_root->Front()->PrintAll();
}
void MonsterManager::PrintInstruction() const
{
	std::cout << "Welcome to the Ivyyy Monster Manager (c)" << std::endl << std::endl;
	std::cout << "Instructions:" << std::endl;
	std::cout << "exit" << std::endl;
	std::cout << "print" << std::endl;
	std::cout << "printall" << std::endl;
	std::cout << "add front name hp" << std::endl;
	std::cout << "add end name hp" << std::endl;
	std::cout << "add index name hp" << std::endl;
	std::cout << "delete index" << std::endl;
	std::cout << "delete name" << std::endl;
	std::cout << "find name" << std::endl;
	std::cout << "find index" << std::endl;
}
void MonsterManager::AddMonster()
{
	std::string pos, name;
	int iPos = -1, hp = 0;

	std::cin >> iPos;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin >> pos >> name >> hp;
	}
	else
		std::cin >> name >> hp;

	if (!std::cin.fail() && ToUpper (pos) == "FRONT")
		AddMonsterFront (new Monster {name, hp}, false);
	else if (!std::cin.fail() && ToUpper(pos) == "END")
		AddMonsterEnd(new Monster{ name, hp }, false);
	else if (!std::cin.fail() && iPos != -1)
		AddAtIndex(iPos, new Monster{ name, hp });
	else
	{
		std::cin.clear();
		std::cout << "ERROR: Invalid input: " << pos << " " << name << " " << hp << std::endl;
	}
}

void MonsterManager::RemoveMonster()
{
	int index;
	std::string name;

	GetSearchPara (name, index);

	if (m_root == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	Monster* monster = nullptr;

	if (index != -1)
		monster = m_root->Find(index);
	else
		monster = m_root->Find (name);

	if (monster != nullptr)
	{
		if (monster == m_root)
			m_root = monster->Next();

		Monster::Delete (monster);
	}
}

void MonsterManager::AddAtIndex(int index, Monster* monster)
{
	if (m_root == nullptr)
		m_root = monster;
	else
		m_root->AddAtIndex(index, monster);

	std::cout << "Added at index: " << index << " ";
	monster->Print();
}

void MonsterManager::AddMonsterFront(Monster* monster, bool silent)
{
	if (m_root == nullptr)
		m_root = monster;
	else
		m_root->AddFront (monster);

	if (!silent)
	{
		std::cout << "Added to front: ";
		monster->Print();
	}
}

void MonsterManager::AddMonsterEnd(Monster* monster, bool silent)
{
	if (m_root == nullptr)
		m_root = monster;
	else
		m_root->AddEnd(monster);

	if (!silent)
	{
		std::cout << "Added to end: ";
		monster->Print();
	}
}

void MonsterManager::ProcessInstruction()
{
	std::string input;

	while (true)
	{
		std::cout << std::endl << std::endl << "Waiting for instruction..." << std::endl << ">";

		std::cin >> input;
		input = ToUpper (input);

		if (input == "EXIT")
			return;
		else if (input == "PRINT")
			Print();
		else if (input == "PRINTALL")
			PrintAll();
		else if (input == "ADD")
			AddMonster();
		else if (input == "FIND")
			FindMonster();
		else if (input == "DEL")
			RemoveMonster();
		else
			std::cout << std::endl << "ERROR: Invalid instrcution " << input << "!";
	}
}

void MonsterManager::FindMonster() const
{
	int index;
	std::string name;

	GetSearchPara(name, index);

	if (m_root == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	std::cout << "FIND result:" << std::endl;

	if (index != -1)
	{
		Monster* monster = m_root->Find (index);

		if (monster !=nullptr)
			monster->Print();
	}
	else
	{
		for (Monster* i = m_root->Front(); i != nullptr; i = i->Next())
		{
			if (ToUpper (i->Name()) == name)
				i->Print();
		}
	}
}

void MonsterManager::DeleteMonsterList()
{
	Monster* current = m_root;

	while (current != nullptr)
	{
		Monster* next = current->Next();
		delete current;
		current = next;
	}
}

std::string MonsterManager::ToUpper(const std::string& source) const
{
	std::string val;
	
	for (size_t i = 0; i < source.length(); ++i)
		val += std::toupper(source[i]);

	return val;
}

void MonsterManager::GetSearchPara(std::string& name, int& index) const
{
	std::cin >> index;

	if (std::cin.fail())
	{
		index = -1;
		std::cin.clear();
		std::cin >> name;

		name = ToUpper(name);
	}
}
