#pragma once
#include <string>

class Monster
{
	public:
		Monster (const std::string& name, int hp);
		~Monster(){};

		void Print();

		void AddMonster (Monster* next);
		
	private:
		std::string m_name;
		int m_hp;
		Monster* m_next;
};

