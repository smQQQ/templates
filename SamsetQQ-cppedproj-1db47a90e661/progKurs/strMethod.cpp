#include "strList.h"

strList::~strList()
{
	cout << "strList деструктор";
}

void strList::sort()
{
	if (size == 0)
		return;
	int usflPtr = (node::ptrcount - 1);
	
	for (int lnIdx = 0; lnIdx < size*usflPtr; lnIdx++)
	{
		for (int lnIdx_S = lnIdx + 1; lnIdx_S < usflPtr*size; lnIdx_S++)
			if ((*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr] != NULL &&
				(*this)[lnIdx / usflPtr][lnIdx%usflPtr] != NULL && 
				compare(*(*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr], *(*this)[lnIdx / usflPtr][lnIdx%usflPtr]))
			{
				char** tmp = (*this)[lnIdx / usflPtr][lnIdx%usflPtr];
				(*this)[lnIdx / usflPtr][lnIdx%usflPtr] = (*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr];
				(*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr] = tmp;
			}
	}
}

void strList::savestr(char *path)
{
	int collcount = node::ptrcount-1;
	ofstream out(path, ios::trunc | ios::binary);
	if (out.is_open())
	{
		out.write((char*)&size, sizeof(int));   // Запись размера списка
		for (int i = 0; i < size; i++)
		{
			int pcount = (*this)[i].getnum();
			if (pcount != 0)
			{
				out.write((char*)&pcount, sizeof(int));   // Запись размера элемента списка
				for (int j = 0; j < collcount; j++)
				{
					if ((*this)[i][j] != nullptr)
					{
						out.write((char*)&j, sizeof(int));     // Запись индекса строки в элементе
						out.write(*(*this)[i][j], sizeof(char)*strlen(*(*this)[i][j]) + 1);  // Запись строки
					}
				}
			}
		}
		out.close();
	}
	else
		cout << "ошибка сохранения файла" << endl;
}

void strList::loadstr(char* path)
{
	if (size != 0)
		(*this).cls_list();

	ifstream in(path, ios::binary);
	if (in.is_open())
	{
		int r;
		in.read((char*)&r, sizeof(int));
		size = r;
		end = begin = new node;
		for (int i = 0; i < r-1; i++)
			end = end->next = new node;

		for (int i = 0; i < r; i++)
		{
			int size;
			in.read((char*)&size, sizeof(int));
			for (int j = 0; j < size; j++)
			{

				int pos;
				in.read((char*)&pos, sizeof(int));

				int str_beg = in.tellg();
				char p = 1;
				while (p != '\0')
					in.read((char*)&p, sizeof(char));

				int strl = (int)in.tellg() - str_beg; // расчет длины строки
				char* buff = new char[strl];
				char** str_ptr = new char*;
				*str_ptr = buff;
				in.seekg(str_beg, ios::beg);
				in.read(buff, sizeof(char)*strl);

				if (pos >= (*this)[0].ptrcount)   // если индекс элемента в файле больше, чем максимальный размер списка
				{
					if (&(*this)[r] == nullptr)
						end = end->next = new node;
					if (end->getnum() == node::ptrcount - 1)
						end = end->next = new node;
					push_back(*str_ptr);
				}
				else
					(*this)[i][pos] = str_ptr;
			}
		}

	}
	else
		cout << "file reading error" << endl;
}

bool strList::compare(char* a, char* b)
{
	//if a<b => return true
	int a_size = 0;
	while (a[a_size++] != '\0');

	int b_size = 0;
	while (b[b_size++] != '\0');
	int minl = b_size;

	if (a_size < b_size)
		minl = a_size;

	for (int h = 0; h < minl - 1; h++)
	{
		if (a[h] < b[h])
			return true;
		else if (a[h] > b[h])
			return false;
	}
	
	if (a_size < b_size)
		return true;

	return false;
}



