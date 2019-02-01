#pragma once
#define DEBUG
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "stdio.h"
#include "conio.h"
#include "arrayMemoryCheck.h"
#include "strList.h"
using namespace std;

class menu
{
	friend class addCommand;
	friend class replaceCommand;
	friend class deleteCommand;
	friend class saveCommand;
	friend class loadCommand;
	friend class balanceCommand;
	friend class sortCommand;
	friend class printCommand;
	friend class clsCommand;
private:
	const static int title_c = 10;
	char* titles[title_c]= {
	"���������� �� �������",
	"������",
	"��������",
	"�������",
	"���������� ������",
	"�������� ������ �� �����",
	"������������",
	"����������",
	"�������� ������",
	"�����" };


	memcheck programStr;
	strList List;
	char* readline();
	vector<int>* arg_extractor(char*, int, bool);
	vector<int>* argExtractionLoop(int,bool);
	void keywait();
public:
	class Item
	{
	public:
		virtual bool perform(menu& m) =0;
	};

	void menuloop();
	void printTitles();
};





