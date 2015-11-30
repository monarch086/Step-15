/*
Написать программу - переводчик. Перевод должен осуществлятся с русского на английский 
и с английского на русский. Для каждого слова может быть несколько вариантов перевода. 
Все слова хранятся в файле. Файл с словарем прилагаю.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <io.h>
#include <string.h>

using namespace std;

struct Word
{
	char word[32];
	int quantity = 0;
	Word **ptrans; //каждое слово хранит массив указателей на соответствующие слова другого языка
};

struct Language
{
	Word *words;
	int quantity;
	int used = 0;
};

struct Dictionary
{
	Language russian;
	Language English;
};

void initDictionary(Dictionary &dictionary);
void removeDictionary(Dictionary &dictionary);
void loadWords(Dictionary &dictionary, char *path);
int findWord(Language &lang, char *word);
void increaseLanguage(Language &lang);



void main()
{

}

void initDictionary(Dictionary &dictionary)
{
	dictionary.English.words = new Word[100];
	dictionary.English.quantity = 100;

	dictionary.russian.words = new Word[100];
	dictionary.russian.quantity = 100;
}

int findWord(Language &lang, char *word)
{
	for (int i = 0; i < lang.used; i++)
	{
		if (strcmp(lang.words[i].word, word) == 0)
			return i;
	}
	return -1;
}

void increaseLanguage(Language &lang)
{

}