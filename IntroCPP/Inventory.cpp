#include "Inventory.h"
#include "Weapon.h"
#include <iostream>

void Inventory::Populate()
{
	m_itemList.push_back (new Weapon ("Sword", 12, 4));
	m_itemList.push_back (new Weapon ("Axe", 4, 8));
	m_itemList.push_back (new Weapon ("Bow", 20, 6));
}

void Inventory::OpenInventory()
{
	std::cout << "INVENTORY:" << std::endl;

	for (size_t i = 0; i < m_itemList.size(); ++i)
		m_itemList[i]->DisplayStats();
}

void Inventory::AddItem(InventoryItem* item)
{
	m_itemList.push_back (item);
}

//void Inventory::AddItem(InventoryItem* item, int anz)
//{
//	for (int i = 0)
//}
