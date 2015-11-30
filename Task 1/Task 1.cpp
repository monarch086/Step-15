/*
С помощью функций printf и scanf считать массив студентов с консоли и записать в файл
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

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
	FILE *pf = fopen(path, "w");
	int quantity = 0;
	printf("Введите колличество студентов: ");
	scanf("%d", &quantity);
	
	Student *array = new Student[quantity];

	for (int i = 0; i < quantity; i++)
	{
		printf("\nВведите имя студента: ");
		scanf("%s", array[i].name);
		printf("\nВведите фамилию студента: ");
		scanf("%s", array[i].surname);
		printf("\nВведите отчество студента: ");
		scanf("%s", array[i].sname);
	}

	fprintf(pf, "%d\n", quantity);

	for (int i = 0; i < quantity; i++)
	{
		fprintf(pf, "%d. %s %s %s;\n", i + 1, array[i].name, array[i].surname, array[i].sname);
	}

	printf("\n\nФайл успешно записан!\n");

	delete[] array;
	fclose(pf);
}