#include <iostream>
#include <string>
#include "Utils.h"
#include "Monster.h"
#include <sstream>

Monster::Monster(const std::string& name, const std::string& type, int hp)
	: m_name (name)
	, m_hp (hp)
	, m_type (type)
{
}

void Monster::AddFront(Monster* monster)
{
	Monster* head = Front();
	head->m_prev = monster;
	monster->m_next = head;
}

void Monster::AddEnd(Monster* monster)
{
	Monster* end = End();
	end->m_next = monster;
	monster->m_prev = end;
}

bool Monster::AddAtIndex(int index, Monster* monster)
{
	//Early exit if index below zero
	if (index < 0)
		return false;

	Monster* current = Find (index);

	if (current != nullptr)
	{
		if (current->m_prev)
			current->m_prev->m_next = monster;

		monster->m_prev = current->m_prev;
		monster->m_next = current;
		current->m_prev = monster;
		return true;
	}

	return false;
}

Monster* Monster::Front() const
{
	if (m_prev == nullptr)
		return (Monster*) this;
	else
		return m_prev->Front();
}

Monster* Monster::End() const
{
	if (m_next == nullptr)
		return (Monster*) this;
	else
		return m_next->End();
}

Monster* Monster::Find(const std::string& val) const
{
	for (Monster* i = Front(); i != nullptr; i = i->Next())
	{
		if (i->Filter (val))
			return i;
	}

	return nullptr;
}

Monster* Monster::Find(int index) const
{
	Monster* current = Front();

	for (int i = 0; i <= index && current != nullptr; ++i)
	{
		if (i == index)
			return current;

		current = current->Next();
	}

	return nullptr;
}

bool Monster::Filter(const std::string& val) const
{
	std::vector <std::string> commandList = Utils::StrSplit (Utils::StrToUpper(val), " OR ");

	for (size_t i = 0; i < commandList.size(); ++i)
	{
		std::vector <std::string> promptList = Utils::StrSplit(commandList[i], " AND ");

		bool ok = true;

		for (int j = 0; j < promptList.size(); ++j)
			ok &= CheckPrompt (promptList[j]);
		
		if (ok)
			return true;
	}

	return false;
}

void Monster::Delete(Monster* monster)
{
	if (monster->m_prev != nullptr)
		monster->m_prev->m_next = monster->m_next;

	if (monster->m_next != nullptr)
		monster->m_next->m_prev = monster->m_prev;

	delete (monster);
}

Monster* Monster::Import(const std::string& data)
{
	std::vector <std::string> dataVec = Utils::StrSplit (data, m_seperator);

	//Invalid argument count!
	if (dataVec.size() < 9)
		return nullptr;

	Monster* newMonster = new Monster();

	newMonster->m_name = dataVec[0];
	newMonster->m_cr = dataVec [1];
	newMonster->m_type = dataVec [2];
	newMonster->m_subType = dataVec [3];
	newMonster->m_size = dataVec [4];

	std::stringstream stringStream;
	stringStream << dataVec[5] << " " << dataVec[6];

	stringStream >> newMonster->m_ac;
	stringStream >> newMonster->m_hp;
	
	newMonster->m_movement = dataVec [7];
	newMonster->m_alignment = dataVec [8];

	newMonster->m_legendary = dataVec.size() > 9;

	return newMonster;
}

std::string Monster::GetPrintString() const
{
	return m_name + " [" + m_type + "] [" + std::to_string (m_hp) + "]";
}

std::string Monster::GetRawDataString() const
{
	std::string data = m_name + m_seperator
		+ m_cr + m_seperator
		+ m_type + m_seperator
		+ m_subType + m_seperator
		+ m_size + m_seperator
		+ std::to_string(m_ac) + m_seperator
		+ std::to_string(m_hp) + m_seperator
		+ m_movement + m_seperator
		+ m_alignment + m_seperator
		+ (m_legendary ? "Legendary" : "");

	return data;
}

std::string Monster::GetFormatedDataString() const
{
	std::string data;
	const size_t lineLength = 48;
	char lineBuffer[lineLength];

	//Init fixed lines
	std::string borderHorizontal;
	borderHorizontal.resize (lineLength, '-');
	borderHorizontal[0] = '+';
	borderHorizontal[lineLength-1] = '+';

	std::string contentSeperator;
	contentSeperator.resize (lineLength, '=');
	contentSeperator[0] = '|';
	contentSeperator[1] = ' ';
	contentSeperator[lineLength-2] = ' ';
	contentSeperator[lineLength-1] = '|';

	const std::string fillerLine = GetFormatedContentLine("", lineLength);

	data = borderHorizontal + '\n'
	 + fillerLine + '\n'
	 + GetFormatedContentLine(m_name, lineLength) + '\n'
	 + GetFormatedContentLine(m_type + std::string (m_subType.empty() ? "" : " (" + m_subType + ")"), lineLength) + '\n'
	 + GetFormatedContentLine(m_alignment, lineLength) + '\n'
	 + fillerLine + '\n'
	 + contentSeperator + '\n'
	 + fillerLine + '\n'
	 + GetFormatedContentLine("AC        :" + std::to_string(m_ac), lineLength) + '\n'
	 + GetFormatedContentLine("HP        :" + std::to_string(m_hp), lineLength) + '\n'
	 + fillerLine + '\n'
	 + GetFormatedContentLine("Size      :" + m_size, lineLength) + '\n'
	 + GetFormatedContentLine("Movement  :" + m_movement, lineLength) + '\n'
	 + fillerLine + '\n'
	 + GetFormatedContentLine("Challenge :" + m_cr, lineLength) + '\n'
	 + GetFormatedContentLine("Legend.   :" + std::string(m_legendary ? "Yes" : "No"), lineLength) + '\n'
	 + fillerLine + '\n'
	 + borderHorizontal + '\n';

	return data;
}

std::string Monster::GetFormatedContentLine(const std::string& rawData, size_t lineLength) const
{
	std::string data;
	data.resize (lineLength, ' ');
	data[0] = '|';
	data[lineLength-1] = '|';
	data.replace (2, std::min(lineLength - 5, rawData.size()), rawData.c_str());

	return data;
}

bool Monster::CheckPrompt(const std::string& val) const
{
	if (val == "LEGENDARY")
		return m_legendary;

	size_t index = val.find_first_of('=');

	//early acces, invalid prompt
	if (index == std::string::npos)
		return false;
	
	//Set category string
	std::string category = val.substr (0, index);
	category = Utils::StrRemove (category, " ");

	//Set value string
	index = val.find_first_of ('"');
	size_t index2 = val.find_last_of ('"');

	std::string value = "";

	if (index != std::string::npos || index2 != std::string::npos)
		value = val.substr (index + 1, index2 - index - 1);

	if (category == "NAME")
		return Utils::StrToUpper (m_name).find (value) != std::string::npos;
	if (category == "CR")
		return Utils::StrToUpper(m_cr).find(value) != std::string::npos;
	if (category == "TYPE")
		return Utils::StrToUpper(m_type).find(value) != std::string::npos;
	if (category == "SUBTYPE")
		return Utils::StrToUpper(m_subType).find(value) != std::string::npos;
	if (category == "AC")
		return std::to_string (m_ac) == value;
	if (category == "HP")
		return std::to_string(m_hp) == value;
	if (category == "MOVEMENT")
		return Utils::StrToUpper(m_movement).find(value) != std::string::npos;
	if (category == "ALIGNMENT")
		return Utils::StrToUpper(m_alignment).find(value) != std::string::npos;
	if (category == "SIZE")
		return Utils::StrToUpper(m_size).find(value) != std::string::npos;

	return false;
}


