#pragma once
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

template<class H>
class list
{

public:

	class node
	{
		friend list;

	public:

		node();
		~node();

		static const int ptrcount = 5;    // Количество указателей в элементе списка

		node *next;

		H*& operator[](int);


		void cls();
		int getnum();
	private:
		H* ObjPtrs[ptrcount] = { NULL };
	
	};
	list(char*);
	list();
	~list();
	
	friend ostream& operator<< <>(ostream&,list<H>&);

	unsigned int getSize();
	void add(H&);
	void add(int, H&);
	void add(int,int, H&);
	void push_back(H&);

	void replace(int, int, H&);

	void cls_ptr(int,int);
	void cls_node(int);
	void cls_list();
	
	void rem_list();
	void rem_node(int);
	
	virtual void sort();
	virtual void balance();
    virtual void savestr(char*)=0;
	virtual void loadstr(char*)=0;
	node& operator[](int);
protected:


	int size = 0;   // Размер списка
	node* begin;
	node* end;
	void overload(node*);
	
};


template<class H>
list<H>::node::node()
{
	next = nullptr;
	for (int i = 0; i<node::ptrcount; i++)
	ObjPtrs[i] = nullptr;
}

template<class H>
list<H>::node::~node()
{
	cout << "Вызов деструктора элемента списка" << endl;
}

template<class H>
void  list<H>::overload(node* ovnode)
{
	node* Temp = ovnode->next;
	ovnode->next = new node;
	ovnode->next->next = Temp;
	unsigned int half = (node::ptrcount - 1) / 2;
	memcpy(ovnode->next->ObjPtrs, ovnode->ObjPtrs + half, sizeof(H*)*half);
	if (ovnode == end)
		end = ovnode->next;
}

template<class H>
H*& list<H>::node::operator[](int i)
{
	if (i >= ptrcount-1 || i < 0)
		throw std::out_of_range("out of range");

	return (this->ObjPtrs[i]);
}


template<class H>
int list<H>::node::getnum()
{
	int r=0;
	for (int i = 0; i < this->ptrcount - 1; i++)
	{
		if (this->ObjPtrs[i] != NULL)
			r++;
	}
	return r;
}



template<class H>
list<H>::list()
{
	begin = nullptr;
	end = begin;
}

template<class H>
list<H>::list(char* h)
{
	begin = nullptr;
	end = begin;
	loadstr(h);
}

template<class H>
list<H>::~list()
{
	node* p = begin;
	node* temp;
	for (int i = 0; p != nullptr; i++)
	{
			temp = p;
			p = p->next;
			delete temp;
	}
}

template<class H>
void list<H>::add(H& a)
{
	if (size == 0)
	{
		begin = new node;
		end = begin;
		size++;
	}
	
	for (int i = 0; i < size; i++)  // инициализация первого попавшегося NULL указателя
	{
		for (int j = 0; j < node::ptrcount-1; j++)
		{
			if ((*this)[i][j] == nullptr)
			{
				(*this)[i][j] = &a;
				cout << *a << end;
				cout << (*this)[i][j] << end;
				return;
			}
		}
	}
	overload(end);						// элемент списка переполнен
	*(*end)[(node::ptrcount-1)/2]=a;
	size++;
}

template<class H>
void list<H>::add(int i, H& a)
{
	node* node = &((*this)[i]);
	for (int i = 0; i < node::ptrcount - 1; i++)
	{
		if (node->ObjPtrs[i] == nullptr)
		{
			node->ObjPtrs[i] = &a;
			return;
		}
	}
	overload(node);
	add(i+1,a);
	size++;
}

template<class H>
void list<H>::add(int i, int j, H& a)
{
	node* node = &((*this)[i]);
	if (node->ObjPtrs[j] == nullptr)
		node->ObjPtrs[j] = &a;
	else
	{
		int k = j + 1;
		for (; k < (node::ptrcount - 1) && node->ObjPtrs[k] != NULL; k++);

		if (k != node::ptrcount - 1)                                          // свободное место в текущем элементе
		{
			memmove(node->ObjPtrs + j + 1, node->ObjPtrs + j, sizeof(H*)*(k - j));
			node->ObjPtrs[j] = &a;
		}
		else                                                            // элемент переполнен
		{
			overload(node);
			node->ObjPtrs[j] = &a;
			size++;
		}
	}
}

template<class H>
void list<H>::push_back(H& a)
{
	for (int i = 0; i < node::ptrcount - 1; i++)
	{
		if (end->ObjPtrs[i] == nullptr)
		{
			end->ObjPtrs[i] = &a;
			return;
		}
	}
	overload(end);
	add(size, a);
	size++;
}

template<class H>
void list<H>::replace(int i, int j, H& a)
{
	(*this)[i][j] = &a;
}

template<class H>
typename list<H>::node& list<H>::operator[](int i)
{
	if (i >= size || i < 0)
		throw std::out_of_range("out of range");

	node* p = begin;
	for (int j = 0; j < i; j++)
		p = p->next;
	return *p;
}
template<class H>
ostream& operator<< <>(ostream& o,list<H>& l)
{
	o << "-----------------------------" << endl;
	for (int i = 0; i < l.getnum(); i++)
	{
		for (int j = 0, count = l[i].getnum(); j < count; j++)
		{
			
			o << *(l[i][j]) << endl;
		}
		o << "-----------------------------" << endl;
	}
	return o;
}

template<class H>
void list<H>::rem_node(int i)
{
	if (i == 0)
	{
		node* t = begin;
		begin = begin->next;
		delete t;
		return;
	}
	if (i == size - 1)
	{
		end = &(*this)[size - 2];
		delete end->next;
		end->next = nullptr;
		return;
	}
	node* pr = &(*this)[i - 1];
	node* t = &(*this)[i];
	pr->next = pr->next->next;
	delete t;
	size--;
}

template<class H>
void list<H>::rem_list()
{
	while (begin != NULL)
	{
		node* t;
		t = begin;
		begin = begin->next;
		delete t;
	}
	begin = nullptr;
	end = begin;
	size = 0;
}

template<class H>
void list<H>::cls_ptr(int i,int j)
{
	(*this)[i][j] = NULL;
}

template<class H>
void list<H>::cls_node(int i)
{
	(*this)[i].cls();
}

template<class H>
void list<H>::cls_list()
{
	for (int i = 0; i < size; i++)
		(*this)[i].cls();
}



template<class H>
void list<H>::node::cls()
{
	for (int i = 0; i < node::ptrcount-1; i++)
		(*this)[i] = NULL;
}


template<class H>
void list<H>::sort()     // сортировка в общем виде (предполагается, что оперетор "<" переопределен)
{
	if (size == 0)
		return;
	int usflPtr = (node::ptrcount - 1);

	for (int lnIdx = 0; lnIdx < size*usflPtr; lnIdx++)
	{
		for (int lnIdx_S = lnIdx + 1; lnIdx_S < usflPtr*size; lnIdx_S++)
			if (*(*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr] < *(*this)[lnIdx / usflPtr][lnIdx%usflPtr])
			{
				char** tmp = (*this)[lnIdx / usflPtr][lnIdx%usflPtr];
				(*this)[lnIdx / usflPtr][lnIdx%usflPtr] = (*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr];
				(*this)[lnIdx_S / usflPtr][lnIdx_S%usflPtr] = tmp;
			}
	}
}

template<class H>
void list<H>::balance()
{
	if (size == 0)
		return;
	int count = 0;
	node* p=begin;

	H** pull = NULL;
	while (p != NULL)
	{
		for (int i = 0; i < node::ptrcount - 1; i++)   // накапливание адресов объектов
		{
			if ((*p)[i] != NULL)
			{
				H** tmp = new H*[count+1];
				memcpy(tmp,pull,sizeof(H*)*count);
				delete[] pull;
				pull = tmp;
				pull[count++] = (*p)[i];
			}
		}
		p->cls();								// очистка элемента списка
		p = p->next;
	}

	int av = count/size;      // среднее количество не NULL элементов в элементе списка

	p = begin;
	int pull_pos=0;
	while (p != NULL)
	{
		for (int i = 0; i < av && pull_pos < count; i++, pull_pos++)    // перераспределение адресов объектов между элементами списка
			(*p)[i] = pull[pull_pos];
		p = p->next;
	}
	p = begin;
	if(pull_pos != count)												// распределение оставшихся адресов
		for (int i = 0; i < count - pull_pos; i++,pull_pos++)
		{
			(*p)[av]=pull[pull_pos];
			p = p->next;
		}
	
}

template<class H>
unsigned int list<H>::getSize()
{
	return size;
}