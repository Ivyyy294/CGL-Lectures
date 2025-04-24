#include "Monster.h"
#include <iostream>

Monster::Monster(const std::string& name, int hp)
	: m_name (name)
	, m_hp (hp)
	, m_next (nullptr)
{
}

void Monster::Print()
{
	std::cout << m_name << " [" << m_hp << "]" << std::endl;

	if (m_next != nullptr)
		m_next->Print();
}

void Monster::AddMonster(Monster* next)
{
	if (m_next != nullptr)
		m_next->AddMonster (next);
	else
		m_next = next;
}
