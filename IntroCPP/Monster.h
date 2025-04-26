#pragma once
#include <string>

class Monster
{
	public:
		Monster (const std::string& name, int hp);
		~Monster(){};

		void Print();
		void PrintAll();

		void AddFront (Monster* monster);
		void AddEnd (Monster* monster);
		void AddAtIndex (int index, Monster* monster);

		inline Monster* Previous() const {return m_prev;};
		inline Monster* Next() const {return m_next;};

		Monster* Front() const;
		Monster* End() const;

		Monster* Find(const std::string& name) const;
		Monster* Find(int index) const;

		inline const std::string& Name() const {return m_name;}
		
		static void Delete (Monster* monster);

	private:
		std::string m_name;
		int m_hp;

		Monster* m_next {nullptr};
		Monster* m_prev {nullptr};
};

