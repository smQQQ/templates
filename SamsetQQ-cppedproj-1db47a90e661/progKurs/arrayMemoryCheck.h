#pragma once
#include <stdio.h>

class memcheck
{
private:
	int bytecount=0;   // ���������� ����, ���������� �� ������
	int strcount=0;    // ���������� �����, �������� � ����������
	char*** allStr=NULL; 
public:
	
	~memcheck();

	friend std::ostream& operator<<(std::ostream& o, memcheck& l);

	void del();
	void watch(char* &a);  
};