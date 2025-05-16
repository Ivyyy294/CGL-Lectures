#include <iostream>
#include <cstring>
#include <fstream>
#include "MonsterManager.h"
#include "Utils.h"

void MonsterManager::Next()
{
	if (m_current == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else if (m_current->Next() == nullptr)
		std::cout << "Reached end of list!" << std::endl;
	else
	{
		m_current = m_current->Next();
		m_current->Print();
	}
}

void MonsterManager::Back()
{
	if (m_current == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else if (m_current->Previous() == nullptr)
		std::cout << "Reached head of list!" << std::endl;
	else
	{
		m_current = m_current->Previous();
		m_current->Print();
	}
}

void MonsterManager::GoToIndex()
{
	int index;

	std::cin>>index;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::string input;
		std::cin >> input;
		std::cout << "ERROR: Invalid index: " << input;
	}
	else 	if (m_current == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else if (Monster* newMonster = m_current->Find(index))
	{
		m_current = newMonster;
		m_current->Print();
	}
	else
		std::cout << "ERROR: Invalid index: " << index;
}

void MonsterManager::Print() const
{
	if (m_current == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else
		m_current->Print();
}
void MonsterManager::PrintAll() const
{
	if (m_current == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else
		m_current->Front()->PrintAll();
}
void MonsterManager::PrintInstruction() const
{
	std::cout << "Welcome to the Ivyyy Monster Manager (c)" << std::endl << std::endl;
	std::cout << "Instructions:" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "view" << std::endl;
	std::cout << "viewall" << std::endl;
	std::cout << "find name" << std::endl;
	std::cout << "find index" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "next" << std::endl;
	std::cout << "back" << std::endl;
	std::cout << "go index" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "add front name hp" << std::endl;
	std::cout << "add end name hp" << std::endl;
	std::cout << "add index name hp" << std::endl;
	std::cout << "delete index" << std::endl;
	std::cout << "delete name" << std::endl;
	std::cout << "delete all name" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "help" << std::endl;
	std::cout << "exit" << std::endl;
}
void MonsterManager::AddMonster()
{
	std::string pos, name, type;
	int iPos = -1, hp = 0;

	std::cin >> iPos;

	if (std::cin.fail())
	{
		iPos = -1;
		std::cin.clear();
		std::cin >> pos >> name >> type >> hp;
	}
	else
		std::cin >> name >> type >> hp;

	if (!std::cin.fail() && Utils::StrToUpper (pos) == "FRONT")
		AddMonsterFront (new Monster {name, type, hp}, false);
	else if (!std::cin.fail() && Utils::StrToUpper(pos) == "END")
		AddMonsterEnd(new Monster{ name, type, hp }, false);
	else if (!std::cin.fail() && iPos != -1)
		AddAtIndex(iPos, new Monster{ name, type, hp });
	else
	{
		std::cin.clear();
		std::cout << "ERROR: Invalid input: " << pos << " " << name << " " << type << " " << hp << std::endl;
	}
}

void MonsterManager::RemoveMonster()
{
	int index;
	std::string name;

	GetSearchPara (name, index);

	if (m_current == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	Monster* monster = nullptr;

	if (Utils::StrToUpper(name) == "ALL")
	{
		if (Utils::StrToUpper(name) == "ALL")
			std::cin >> name;

		name = Utils::StrToUpper(name);

		while (monster = m_current->Find (name))
		{
			if (monster == m_current)
				m_current = monster->Next();

			std::cout << "Deleting " << monster->Name() << "..." << std::endl;
			Monster::Delete (monster);
		}
	}
	else
	{
		if (index != -1)
			monster = m_current->Find(index);
		else
			monster = m_current->Find(name);

		if (monster != nullptr)
		{
			if (monster == m_current)
				m_current = monster->Next();

			Monster::Delete (monster);
			std::cout << "Monster deleted!" << std::endl;
		}
		else
			std::cout << "ERROR: Invalid monster!" << std::endl;
	}
}

void MonsterManager::AddAtIndex(int index, Monster* monster)
{
	bool ok = false;

	if (m_current != nullptr)
		ok = m_current->AddAtIndex(index, monster);

	if (ok)
	{
		std::cout << "Added at index: " << index << " ";
		monster->Print();
	}
	else
		std::cout << "ERROR: Invalid index: " << index;
}

void MonsterManager::AddMonsterFront(Monster* monster, bool silent)
{
	if (m_current == nullptr)
		m_current = monster;
	else
		m_current->AddFront (monster);

	if (!silent)
	{
		std::cout << "Added to front: ";
		monster->Print();
	}
}

void MonsterManager::AddMonsterEnd(Monster* monster, bool silent)
{
	if (m_current == nullptr)
		m_current = monster;
	else
		m_current->AddEnd(monster);

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
		input = Utils::StrToUpper (input);

		if (input == "EXIT")
			return;
		else if (input == "HELP")
			PrintInstruction();
		else if (input == "VIEW")
			Print();
		else if (input == "VIEWALL")
			PrintAll();
		else if (input == "ADD")
			AddMonster();
		else if (input == "FIND")
			FindMonster();
		else if (input == "DELETE")
			RemoveMonster();
		else if (input == "NEXT")
			Next();
		else if (input == "BACK")
			Back();
		else if (input == "GO")
			GoToIndex();
		else
		{
			std::cin.clear();
			std::cout << std::endl << "ERROR: Invalid instrcution " << input << "!";
		}
	}
}

void MonsterManager::FindMonster() const
{
	int index;
	std::string name;

	GetSearchPara(name, index);

	if (m_current == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	std::cout << "FIND result:" << std::endl;

	if (index != -1)
	{
		Monster* monster = m_current->Find (index);

		if (monster !=nullptr)
			monster->Print();
	}
	else
	{
		for (Monster* i = m_current->Front(); i != nullptr; i = i->Next())
		{
			if (i->Compare (name))
				i->Print();
		}
	}
}

void MonsterManager::DeleteMonsterList()
{
	Monster* current = m_current;

	while (current != nullptr)
	{
		Monster* next = current->Next();
		delete current;
		current = next;
	}
}

void MonsterManager::Import(const std::string& filePath)
{
	std::ifstream file {filePath};

	if (!file)
	{
		std::cout << "ERROR: Unable to open file: " << filePath;
		return;
	}

	std::string data;


	while (!file.eof())
	{
		std::getline (file, data);

		Monster* monster = Monster::Import(data);

		if (monster != nullptr)
			AddMonsterEnd (monster);
	}
}

void MonsterManager::GetSearchPara(std::string& name, int& index) const
{
	std::cin >> index;

	if (std::cin.fail())
	{
		index = -1;
		std::cin.clear();
		std::cin >> name;

		name = Utils::StrToUpper(name);
	}
}
