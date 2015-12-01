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
	Word **ptrans; //динамический массив указателей на соответствующие слова другого языка
};

struct Language
{
	Word *words;
	int quantity; //общий размер массива слов
	int used = 0; //кол-во занятых ячеек массива
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
void loadWords(Dictionary &dictionary, char *path);

void addPairOfWords(Dictionary &dictionary, char *Eng, char *rus);
int addWordToLang(Language &lang, char *word);
void setRelations(Dictionary &dictionary, int En, int ru);
void increasePtrArray(Language &lang, int index);

void main()
{
	setlocale(LC_ALL, "Ukr");
	Dictionary Voc;
	initDictionary(Voc);
	loadWords(Voc, "1.txt");
	
	cout << "Введите слово: ";
	char word[64];
	gets(word);
	
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
	if (dictionary.English.used > 0)
		for (int i = 0; i < dictionary.English.used; i++)
			delete[] dictionary.English.words[i].(*ptrans);
	if (dictionary.russian.used > 0)
		for (int i = 0; i < dictionary.russian.used; i++)
			delete[] dictionary.russian.words[i].(*ptrans);
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

void loadWords(Dictionary &dictionary, char *path)
{
	int res = _access(path, 0);
	if (res == 0)
	{
		FILE *pf = fopen(path, "r");
		char buffer[64];
		char Eng[32];
		char rus[32];
		while (!feof(pf))
		{
			fgets(buffer, 64, pf);
			//cout << buffer << endl;
			
			char *space = strchr(buffer, ' ');//находим указатель на пробел между словами
			
			int size = space - &buffer;
			strncpy(Eng, buffer, size);
			Eng[size] = '\0';
			
			size = strlen(buffer) - size - 1;
			strncpy(rus, *space, size);
			rus[size] = '\0';
			
			addPairOfWords(dictionary, Eng, rus);
		}

		cout << "The dictionary was loaded successfully" << endl;
		printf("It contains %d pairs of words\n", dictionary.English.used);
		
	}
	else cout << "Unable to load dictionary!" << endl;
}

void addPairOfWords(Dictionary &dictionary, char *Eng, char *rus)
{
	int En = addWordToLang(dictionary.English, Eng);
	int ru = addWordToLang(dictionary.russian, rus);
	setRelations(dictionary, En, ru);
}

int addWordToLang(Language &lang, char *word)
{
	int current = findWord(lang, word);
	if (current >= 0)
		return current;
	else
	{
		if (lang.quantity == lang.used)
			increaseWordsArray(lang);
		strcpy(lang.words[lang.used++], word);
		current = lang.used - 1;
		return current;
	}
}

void setRelations(Dictionary &dictionary, int En, int ru)
{
	increasePtrArray(dictionary.English, En);
	increasePtrArray(dictionary.russian, ru);
	
	Word &wEn = dictionary.English.words[En];
	Word &wRu = dictionary.russian.words[ru];
	
	wEn.*ptrans[wEn.quantity - 1] = &wRu;
	wRu.*ptrans[wRu.quantity - 1] = &wEn;
}

void increasePtrArray(Language &lang, int index)
{
	int &quantity = lang.words[index].quantity;
	
	if (quantity == 0)
		lang.words[index].(*ptrans) = new Word*[++quantity];
	else
	{
		Word **old = lang.words[index].(*ptrans);
		lang.words[index].(*ptrans) = new Word*[++quantity];
		for (int i = 0; i < quantity - 1; i++)
			lang.words[index].(*ptrans)[i] = *old[i];
		delete[] *old;
	}
}















