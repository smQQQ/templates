#include "menu.h"
#include "menuItems.h"
#include <conio.h>

//"\nМеню:\n--------------------\n1. Добавление со сдвигом\n2. Замена\n3. Удаление элемента списка\n4. Сохранение списка\n5. Загрузка списка из файла\n6. Балансировка\n7. Сортировка\n8. Показать список\n9. Выход\n--------------------\n";

void menu::menuloop()
{
	int itemId = 0;
	while (itemId != title_c)
	{
		printTitles();
		
		cin >> itemId;
		system("cls");
		menu::Item* it;

		switch (itemId)
		{
		case 1:it = new addCommand;
			break;
		case 2:it = new replaceCommand;
			break;
		case 3:it = new deleteCommand;
			break;
		case 4:it = new clsCommand;
			break;
		case 5:it = new saveCommand;
			break;
		case 6:it = new loadCommand;
			break;
		case 7:it = new balanceCommand;
			break;
		case 8:it = new sortCommand;
			break;
		case 9:it = new printCommand;
			break;
		case 10:continue;
		default: continue;
		}
		if(it->perform(*this))
			keywait();
		system("cls");
	}
	this->programStr.del();
	keywait();
}

void menu::printTitles()
{
	cout << "Меню:" << endl;
	for (int i = 0; i < title_c; i++)
		cout << i + 1 << '.' << titles[i] << endl;
}

 char * menu::readline()
 {
	char* line = NULL;
	int size = 0;
	do
	{
		char* buff = new char[size + 1];
		memcpy(buff, line, size * sizeof(char));
		delete[] line;
		line = buff;
		if((line[size]=getch()) != 8) // 8 - backspace ascii code
			cout << line[size++];
		if (line[size] == 8)
		{
			cout << "\b \b";
			if (size)
				size--;
		}
	} while (line[size - 1] != '\r' && line[size - 1] != '\n' && line[size - 1] != 27);  // 27 - esc ascii code
	cout << endl;

	if (line[size - 1] == 27)
	{
		delete[] line;
		return NULL;
	}
	else
		line[size - 1] = '\0';

	#ifdef DEBUG
	cout << line << endl;
	#endif
	
	return line;
}

 vector<int>* menu::arg_extractor(char* examLine,int mx_rec_args, bool up_to)
{
	 if (examLine[0] == '\n')
	 {
#ifdef DEBUG
		 cout << "Extracted " << 0 << endl;
#endif // DEBUG
		 return new vector<int>;
	 }

	int argcount = 0;
	bool isWord = false;
	for (int i = 0; examLine[i] != '\0'; i++)
	{
		if (examLine[i] != ' ' && isWord == false)
		{
			if (examLine[i] < '0' || examLine[i] > '9')
			{
				cout << "Неверный формат одного или нескольких аргументов\n";
#ifdef DEBUG
				cout << "error"<< endl;
#endif // DEBUG

				return NULL;
			}
			isWord = true;
			argcount++;
		}
		else
			isWord = false;
	}

	if (argcount > mx_rec_args)
	{
		cout << "неверное количество аргументов\n";
		return NULL;
	}

	if (!up_to && argcount < mx_rec_args)
	{
#ifdef DEBUG
		cout << "not enough" << endl;
#endif // DEBUG

		return NULL;
	}
	

	char** subLines = new char*[argcount];

	int ii = 0;
	char* exptr = strtok(examLine, " ");
	while (exptr != NULL)
	{
		subLines[ii] = new char[strlen(exptr) + 1];
		strcpy(subLines[ii++], exptr);
		exptr = strtok(NULL, " ");
	}

	vector<int>* output=new vector<int>;
	for (int j = 0; j < argcount; j++)
	{
		output->push_back(atoi(subLines[j]));
		cout << j << endl;
	}

	return output;
}

 vector<int>* menu::argExtractionLoop(int argcount,bool up_to)
 {
	 vector<int>* args=NULL;
	 while (args == NULL)
	 {
		 char* line = readline();
		 if (line == NULL)
			 return NULL;

		 args = arg_extractor(line, argcount, up_to);
	 }
	 return args;
 }

 void menu::keywait()
{
	cout << "Для продолжения нажмите любую клавишу. . .\n";
	while (!kbhit());
	getch();
}
