#pragma once
#include "ListTemplate.h"
class strList : public list<char*>
{
	friend list<char*>;
private:
	bool compare(char*, char*);
public:
	virtual ~strList();
	friend ostream& operator<< (ostream& o, strList& l)
	{
		cout << "Количество элементов " << l.size << endl;
		for (int i = 0; i < l.size; i++)
		{
			o << "-----------------------------" << endl;
			int count = l[i].getnum();
			if (count == 0)
			{
				cout << "[EMPTY]\n";
				continue;
			}
			for (int j = 0; j < strList::node::ptrcount-1; j++)
			{
				if (l[i][j] != nullptr)
					o << *(l[i][j]) << endl;
				else
					cout << "<empty>\n";
			}
			o << "-----------------------------" << endl;
		}
		return o;
	}
	virtual void sort();
	virtual void savestr(char*);
	virtual void loadstr(char*);
};

