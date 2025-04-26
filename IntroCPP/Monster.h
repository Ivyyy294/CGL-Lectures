#pragma once
#include <string>

class Monster
{
	public:
		Monster (const std::string& name, const std::string& type, int hp);
		~Monster(){};

		void Print();
		void PrintAll();

		void AddFront (Monster* monster);
		void AddEnd (Monster* monster);
		bool AddAtIndex (int index, Monster* monster);

		inline Monster* Previous() const {return m_prev;};
		inline Monster* Next() const {return m_next;};

		Monster* Front() const;
		Monster* End() const;

		Monster* Find(const std::string& val) const;
		Monster* Find(int index) const;

		bool Compare (const std::string& val);

		inline const std::string& Name() const {return m_name;}
		std::string ToUpper(const std::string& val) const;
		
		static void Delete (Monster* monster);

	private:
		std::string m_name;
		std::string m_type;
		int m_hp;

		Monster* m_next {nullptr};
		Monster* m_prev {nullptr};

};

