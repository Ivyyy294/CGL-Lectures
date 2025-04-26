#include "Monster.h"
#include <iostream>

Monster::Monster(const std::string& name, const std::string& type, int hp)
	: m_name (name)
	, m_hp (hp)
	, m_type (type)
{
}

void Monster::Print()
{
	std::cout << m_name << " [" << m_type << "] [" << m_hp << "]" << std::endl;
}

void Monster::PrintAll()
{
	Print();

	if (m_next != nullptr)
		m_next->PrintAll();
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
		if (i->Compare (val))
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

bool Monster::Compare(const std::string& val)
{
	return ToUpper(m_name).find(val) != std::string::npos
		|| ToUpper(m_type).find(val) != std::string::npos;
}

void Monster::Delete(Monster* monster)
{
	if (monster->m_prev != nullptr)
		monster->m_prev->m_next = monster->m_next;

	if (monster->m_next != nullptr)
		monster->m_next->m_prev = monster->m_prev;

	delete (monster);
}

std::string Monster::ToUpper(const std::string& val) const
{
	std::string result;

	for (size_t i = 0; i < val.length(); ++i)
		result += std::toupper(val[i]);

	return result;
}

