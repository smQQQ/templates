#pragma once
#include <stdio.h>

class memcheck
{
private:
	int bytecount=0;   // количество байт, выделенных на строки
	int strcount=0;    // количество строк, введеных с клавиатуры
	char*** allStr=NULL; 
public:
	
	~memcheck();

	friend std::ostream& operator<<(std::ostream& o, memcheck& l);

	void del();
	void watch(char* &a);  
};