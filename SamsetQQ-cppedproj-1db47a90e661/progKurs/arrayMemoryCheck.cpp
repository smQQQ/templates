#pragma once
#include <iostream>
#include "arrayMemoryCheck.h"

 memcheck::~memcheck()
{
	for (int i = 0; i < strcount; i++)
		delete allStr[i];

	delete[] allStr;
}

 void memcheck::del()
{
	std::cout << "Удалено строк - "<< strcount << " | " << bytecount << " байт\n";
	for (int i = 0; i < strcount; i++)
	{
		delete[] *(allStr[i]);
		delete allStr[i];
	}

	delete[] allStr;

	strcount = 0;
	allStr = NULL;
}

 void memcheck::watch(char* &a)
{
	bytecount += (sizeof(char*)+strlen(a)*sizeof(char));
	char*** strBuff = new char**[strcount + 1];
	for (int i = 0; i < strcount; i++)
		strBuff[i] = allStr[i];

	strBuff[strcount++] = &a;
	delete allStr;

	allStr = strBuff;
}

std::ostream & operator<<(std::ostream & o, memcheck & l)
{
	o << "В программе было динамически создано " << l.strcount << " строк\n";
	return o;
}


