#include "InventoryItem.h"

InventoryItem::InventoryItem(const std::string& name, const int value, const int stackSize)
	:	m_name (name)
	, m_value (value)
	, m_stackSize (stackSize)
{
}
