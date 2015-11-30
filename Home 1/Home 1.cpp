/*
Написать программу - переводчик. Перевод должен осуществлятся с русского на английский 
и с английского на русский. Для каждого слова может быть несколько вариантов перевода. 
Все слова хранятся в файле. Файл с словарем прилагаю.
*/

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100

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
	Language English;
	Language russian;
};

void initDictionary(Dictionary &dictionary);
void removeDictionary(Dictionary &dictionary);
int findWord(Language &lang, char *word);
void increaseWordsArray(Language &lang);
void addPairOfWords(Language &lang, char *Eng, char *rus);
void loadWords(Dictionary &dictionary, char *path);


void main()
{
	setlocale(LC_ALL, "Ukr");
	Dictionary Voc;
	initDictionary(Voc);
	loadWords(Voc, "1.txt");

	removeDictionary(Voc);
}

void initDictionary(Dictionary &dictionary)
{
	dictionary.English.words = new Word[SIZE];
	dictionary.English.quantity = SIZE;

	dictionary.russian.words = new Word[SIZE];
	dictionary.russian.quantity = SIZE;
}

void removeDictionary(Dictionary &dictionary)
{
	delete[] dictionary.English.words;
	delete[] dictionary.russian.words;
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

void increaseWordsArray(Language &lang)
{
	Word *oldWords = lang.words;
	lang.quantity += SIZE;
	lang.words = new Word[lang.quantity];

	for (int i = 0; i < lang.used; i++)
		lang.words[i] = oldWords[i];

	delete[] oldWords;
}

void addPairOfWords(Language &lang, char *Eng, char *rus)
{

}

void loadWords(Dictionary &dictionary, char *path)
{
	int res = _access(path, 0);
	if (res == 0)
	{
		FILE *pf = fopen(path, "r");
		char buffer[64];
		while (!feof(pf))
		{
			fgets(buffer, 64, pf);
			cout << buffer << endl;
		}




	}
	else cout << "Unable to load dictionary!";
}