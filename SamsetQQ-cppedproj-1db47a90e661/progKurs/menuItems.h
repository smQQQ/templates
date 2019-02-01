#pragma once
#include "strList.h"
#include "arrayMemoryCheck.h"
#include "menu.h"
#include <vector>


class addCommand : public menu::Item   // ���������� �� �������
{
public:

	bool perform(menu& m)
	{
		cout << "ESC - ��������� �����\n������� ������\n";
		char** line = new char*;
		*line = m.readline();
		if (*line == NULL)
			return false;
		m.programStr.watch(*line);

		cout << "������� ������ �������� ������ � ������ ������� ����������\n";
		vector<int>* args;
		if ((args=m.argExtractionLoop(2, true)) == NULL)
			return false;

#ifdef DEBUG
		cout << "Extracted " << args->size();
#endif // DEBUG
		try {
			switch (args->size())
			{
			case 0:	m.List.add(*line);
				break;
			case 1: m.List.add((*args)[0], *line);
				break;
			case 2: m.List.add((*args)[0], (*args)[1], *line);
			}
		}
		catch (std::out_of_range)
		{
			cout << "out of range";
		}
		return true;
	}
};

class replaceCommand : public menu::Item  // ������ �������� ������
{
public:
	bool perform(menu& m)
	{
		cout << "ESC - ��������� �����\n������� ������\n";
		char** line = new char*;
		*line = m.readline();
		if (*line == NULL)
			return false;
		m.programStr.watch(*line);
		
		cout << "������� ������ �������� ������ � ������ ������� ����������\n";
		vector<int>* args;
		if ((args = m.argExtractionLoop(2, true)) == NULL)
			return false;
		m.List.replace((*args)[0], (*args)[1], *line);
		return true;
	}
};

class deleteCommand : public menu::Item  // �������� �� ������
{
public:
	bool perform(menu& m)
	{
		cout << "ESC - ��������� �����\n������� ������ �������� ������ � ������ ������� ����������\n";
		vector<int>* args;
		if ((args = m.argExtractionLoop(2, true)) == NULL)
			return false;
		switch (args->size())
		{
		case 0:	m.List.rem_list();
				break;
		case 1: m.List.rem_node((*args)[0]);
				break;
		}
		return true;
	}
};

class clsCommand : public menu::Item  // �������� �� ������
{
public:
	bool perform(menu& m)
	{
		cout << "ESC - ��������� �����\n������� ������ �������� ������ � ������ ������� ����������\n";
		vector<int>* args;
		if ((args = m.argExtractionLoop(2, true)) == NULL)
			return false;
		switch (args->size())
		{
		case 0:	m.List.cls_list();
			break;
		case 1: m.List.cls_node((*args)[0]);
			break;
		case 2: m.List.cls_ptr((*args)[0], (*args)[1]);
		}
		return true;
	}
};


class saveCommand : public menu::Item
{
public:
	bool perform(menu& m)
	{
		cout << "ESC - ��������� �����\n������� ���� ��� ���������� �����\n";
		char* path = m.readline();
		if (path == NULL)
			return false;
		m.List.savestr(path);
		delete[] path;
		cout << "������ ������� ���������\n";
		return true;
	}
};

class loadCommand : public menu::Item
{
public:
	bool perform(menu& m)
	{
		cout << "ESC - ��������� �����\n������� ����� ����� ��� ��������\n";
		char* path = m.readline();
		if (path == NULL)
			return false;
		m.List.loadstr(path);
		delete[] path;
		for (int i = 0; i < m.List.getSize(); i++)
		{
			for (int j = 0; j < strList::node::ptrcount-1; j++)
				m.programStr.watch(*m.List[i][j]);
		}
		
		cout << "������ ������� ��������� � ���������\n";
		return true;
	}
};

class balanceCommand : public menu::Item  // ������������ ���������� ���������� �� ���� ��������� ������ � �������� ��������
{
public:
	bool perform(menu& m)
	{
		m.List.balance();
		cout << "��������� ��������������\n";
		return true;
	}
};

class sortCommand : public menu::Item
{
public:
	bool perform(menu& m)
	{
		m.List.sort();
		cout << "��������� �������������\n";
		return true;
	}
};

class printCommand : public menu::Item
{
public:
	bool perform(menu& m)
	{
		cout << m.List;
		return true;
	}
};




