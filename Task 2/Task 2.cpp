/*
С помощью функций printf и scanf считать массив студентов с файла и вывести в консоль
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <io.h>

using namespace std;

struct Student
{
	char name[32];
	char surname[32];
	char sname[32];
};

void main()
{
	setlocale(LC_ALL, "Ukr");

	char *path = "student.txt";
	int res = _access(path, 0); //проверка на существование: 0 - да, 1 - нет
	if (res == 0)
	{
		FILE *pf = fopen(path, "r");
		int quantity = 0;
		fscanf(pf, "%d\n", &quantity);
		int x;
		Student *array = new Student[quantity];
		for (int i = 0; i < quantity; i++)
		{
			fscanf(pf, "%d. %s %s %s;\n", &x, array[i].name, array[i].surname, array[i].sname);
		}

		for (int i = 0; i < quantity; i++)
		{
			printf("%d. %s %s %s;\n", i + 1, array[i].name, array[i].surname, array[i].sname);
		}

		delete[] array;
		fclose(pf);
	}	
}