#pragma once
#include <string>

class Monster
{
	public:
		Monster(){};
		Monster (const std::string& name, const std::string& type, int hp);
		~Monster(){};

		void AddFront (Monster* monster);
		void AddEnd (Monster* monster);
		bool AddAtIndex (int index, Monster* monster);

		inline Monster* Previous() const {return m_prev;};
		inline Monster* Next() const {return m_next;};

		Monster* Front() const;
		Monster* End() const;

		Monster* Find(const std::string& val) const;
		Monster* Find(int index) const;

		bool Filter (const std::string& val)const;

		static void Delete (Monster* monster);
		static Monster* Import (const std::string& data);

		std::string GetPrintString() const;
		std::string GetRawDataString () const;
		std::string GetFormatedDataString () const;

	private:
		static const char m_seperator {';'};

		std::string m_name;
		std::string m_cr;
		std::string m_type;
		std::string m_subType;
		std::string m_size;
		size_t m_ac {0};
		size_t m_hp {0};
		std::string m_movement;
		std::string m_alignment;
		bool m_legendary {false};

		Monster* m_next {nullptr};
		Monster* m_prev {nullptr};

		std::string GetFormatedContentLine (const std::string& rawData, size_t lineLength) const;
		bool CheckPrompt (const std::string& val) const;
};

