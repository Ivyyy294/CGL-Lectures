#include "Weapon.h"
#include <iostream>

Weapon::Weapon(const std::string& name, const int value, const int damage, const int stackSize)
: InventoryItem (name, value, stackSize)
, m_damage (damage)
{
}

void Weapon::DisplayStats()
{
	std::cout << m_name << "\t" << m_value << " G \t" << m_damage << " damage." << std::endl;
}
