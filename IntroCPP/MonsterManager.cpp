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
		std::cout << m_current->GetFormatedDataString() << std::endl;
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
		std::cout << m_current->GetFormatedDataString() << std::endl;
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
		std::cout << m_current->GetFormatedDataString() << std::endl;
	}
	else
		std::cout << "ERROR: Invalid index: " << index;
}

void MonsterManager::List() const
{
	std::string command;
	std::cin >> command;
	command = Utils::StrToUpper (command);

	if (command == "CURRENT")
		std::cout << m_current->GetFormatedDataString() << std::endl;
	else if (command == "FILTER")
		ListFilter();
	else if (command == "ALL")
		ListAll();
}
void MonsterManager::ListAll() const
{
	if (m_current == nullptr)
		std::cout << "ERROR: Monster list is empty!" << std::endl;
	else
	{
		Monster* current = m_current->Front();
		while (current != nullptr)
		{
			std::cout << current->GetPrintString() << std::endl;
			current = current->Next();
		}
	}
}

void MonsterManager::ListFilter() const
{
	for (size_t i = 0; i < m_filterList.size(); ++i)
		std::cout << m_filterList[i]->GetPrintString() << std::endl;
}

void MonsterManager::PrintInstruction() const
{
	std::cout << "Welcome to the Ivyyy Monster Manager (c)" << std::endl << std::endl;
	std::cout << "Instructions:" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "list current" << std::endl;
	std::cout << "list filter" << std::endl;
	std::cout << "list all" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "next" << std::endl;
	std::cout << "back" << std::endl;
	std::cout << "go index" << std::endl;
	std::cout << "find valuename=\"value\" AND valuename=\"value\" OR valuename=\"value\"" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "add front" << std::endl;
	std::cout << "add end" << std::endl;
	std::cout << "add index" << std::endl;
	std::cout << "delete index" << std::endl;
	std::cout << "delete valuename=\"value\" AND valuename=\"value\" OR valuename=\"value\"" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "save" << std::endl;
	std::cout << "export filename" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "help" << std::endl;
	std::cout << "exit" << std::endl;
}
void MonsterManager::AddMonster()
{
	std::string pos, buffer, values;
	int iPos = -1;

	std::cin >> iPos;

	if (std::cin.fail())
	{
		iPos = -1;
		std::cin.clear();
		std::cin >> pos;
		std::cin.clear();
	}
	
	std::cout << "Enter values: Name;CR;Type;Subtype;Size;AC;HP;SpecialMovementType;Alignment;Legendary" << std::endl;

	std::cin>>buffer;
	std::getline (std::cin, values);

	values = buffer + values;

	Monster* monster = Monster::Import(values);

	if (monster == nullptr)
	{
		std::cout << "ERROR: Invalid input: " << values << std::endl;
		return;
	}
	else if ( Utils::StrToUpper (pos) == "FRONT")
		AddMonsterFront (monster, false);
	else if (Utils::StrToUpper(pos) == "END")
		AddMonsterEnd(monster, false);
	else if (iPos != -1)
		AddAtIndex(iPos, monster);
	else
		std::cout << "ERROR: Invalid input: " << pos << std::endl;
}

void MonsterManager::RemoveMonster()
{
	if (m_current == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	int index = -1;
	std::string prompt;

	std::cin >> index;

	if (std::cin.fail())
	{
		index = -1;
		std::cin.clear();
		std::getline (std::cin, prompt);
	}

	if (m_current == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	std::vector <Monster*> deleteList;
	Monster* monster = nullptr;

	//Delete at index
	if (index >= 0)
	{
		monster = m_current->Find(index);

		if (monster != nullptr)
			deleteList.push_back (monster);
		else
			std::cout << "ERROR: Invalid monster!" << std::endl;
	}
	else
	{
		Monster* monster = m_current->Front();

		while (monster != nullptr)
		{
			if (monster->Filter (prompt))
				deleteList.push_back (monster);

			monster = monster->Next();
		}
	}

	for (size_t i = 0; i < deleteList.size(); ++i)
	{
		Monster* monster = deleteList[i];

		if (monster == m_current)
			m_current = monster->Next();

		Monster::Delete(monster);
	}
}

bool MonsterManager::SaveFileIntern()
{
	std::ofstream file{ m_filePath };

	if (!file)
		return false;

	std::string data;

	for (Monster* i = m_current->Front(); i != nullptr; i = i->Next())
		data += i->GetRawDataString() + "\n";

	file.clear();
	file << data;

	return file.good();
}

void MonsterManager::Export()
{
	std::string filename;
	std::cin >> filename;

	if (std::cin.good())
	{
		if (std:: ofstream file {filename})
		{
			if (m_filterList.size() > 0)
			{
				for (size_t i = 0; i < m_filterList.size(); ++i)
					file << m_filterList[i]->GetFormatedDataString() << std::endl;
			}
			else
				file << m_current->GetFormatedDataString();
		}
	}
}

void MonsterManager::SaveFile()
{
	if (m_current == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	if (SaveFileIntern())
		std::cout << "Saving successful: " << m_filePath << std::endl;
	else
		std::cout << "ERROR: Unable to save file: " << m_filePath << std::endl;
}

void MonsterManager::AddAtIndex(int index, Monster* monster)
{
	bool ok = false;

	if (m_current != nullptr)
		ok = m_current->AddAtIndex(index, monster);

	if (ok)
	{
		std::cout << std::endl << monster->GetFormatedDataString() << std::endl;
		SaveFileIntern();
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
		std::cout << std::endl << monster->GetFormatedDataString() << std::endl;

	SaveFileIntern();
}

void MonsterManager::AddMonsterEnd(Monster* monster, bool silent)
{
	if (m_current == nullptr)
		m_current = monster;
	else
		m_current->AddEnd(monster);

	if (!silent)
		std::cout << std::endl << monster->GetFormatedDataString() << std::endl;

	SaveFileIntern();
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
		else if (input == "LIST")
			List();
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
		else if (input == "SAVE")
			SaveFile();
		else if (input == "EXPORT")
			Export();
		else
		{
			//clear cin
			std::getline (std::cin, input);
			std::cout << std::endl << "ERROR: Invalid instrcution!";
		}
	}
}

void MonsterManager::FindMonster()
{
	std::string prompt;
	std::getline (std::cin, prompt);

	if (m_current == nullptr)
	{
		std::cout << "ERROR: Monster list is empty!" << std::endl;
		return;
	}

	m_filterList.clear();

	for (Monster* i = m_current->Front(); i != nullptr; i = i->Next())
	{
		if (i->Filter (prompt))
			m_filterList.push_back(i);
	}

	ListFilter();
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

	m_filePath = filePath;
	std::string data;

	while (!file.eof())
	{
		std::getline (file, data);

		Monster* monster = Monster::Import(data);

		if (monster != nullptr)
		{
			if (m_current == nullptr)
				m_current = monster;
			else
				m_current->AddEnd(monster);
		}
	}
}

