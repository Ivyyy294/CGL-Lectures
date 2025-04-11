#pragma once
#include "InventoryItem.h"
#include <map>

class Inventory
{
public:
	void Populate();
	void OpenInventory();

	void AddItem (InventoryItem* item);
	//void AddItem (InventoryItem* item, int anz);
	//std::string GetDisplayText();

private:
	InventoryItem::Vec m_itemList;

	//std::string GetDescriptionForItem (InventoryItem* item, int anz);
};

