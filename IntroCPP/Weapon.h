#pragma once
#include "InventoryItem.h"

class Weapon :
    public InventoryItem
{
public:
	Weapon (const std::string& name, const int value, const int damage, const int stackSize = 1);

	//virtual const std::string& GetDescription() const override;
	virtual void DisplayStats() override;

protected:
	int m_damage;
};

