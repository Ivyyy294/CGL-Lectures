#pragma once
#include <string>
#include <vector>
#include <typeinfo>

class InventoryItem
{
public:
	typedef std::vector <InventoryItem*> Vec;

	inline const std::string& GetName() const {return m_name;};
	//virtual std::string GetDescription() const = 0;
	inline int GetValue() const { return m_value;}
	inline int GetStackSize() const { return m_stackSize; }

protected:
	const std::string m_name;
	const int m_value;
	const int m_stackSize;

	InventoryItem (const std::string& name, const int value = 0, const int stackSize = 1);
	//image
};

