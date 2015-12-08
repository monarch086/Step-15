/*
Написать программу - переводчик. Перевод должен осуществлятся с русского на английский 
и с английского на русский. Для каждого слова может быть несколько вариантов перевода. 
Все слова хранятся в файле. Файл с словарем прилагаю.
*/

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 50 //начальный размер массива words

#include <iostream>
#include <io.h>
#include <conio.h>
#include <string.h>
//#include <Windows.h>

using namespace std;

struct Word
{
	char word[64];
	int quantity = 0;
	Word **ptrans; //динамический массив указателей на соответствующие слова другого языка
};

struct Language
{
	Word *words;
	int quantity; //общий размер массива слов
	int used = 0; //кол-во занятых ячеек массива
	Language *oppositeLang; //указатель на другой язык
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
void increasePtrArray(Word *w);

void translate(Dictionary &dictionary, char *word, char &tr);
void prepareString(Language &lang, int index, char &tr);

void main()
{
	setlocale(LC_ALL, "Rus");
	//SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	//SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	Dictionary Voc = {};
	initDictionary(Voc);
	loadWords(Voc, "1.txt");
	
	char word[64];
	char trans[256];
	int a = 0;

	while(a != 27)
	{
		cout << "Введите слово: ";
		fgets(word, sizeof(word), stdin);
		
		int length = strlen(word);
		word[length - 1] = '\0'; //стираем последний символ \n
		
		/*
		cout << "TEST: " << word << endl;
			
		cout << Voc.English.words[150].word << endl;
		cout << Voc.English.words[151].word << endl;
		cout << Voc.English.words[152].word << endl;

		cout << Voc.russian.words[150].word << endl;
		cout << Voc.russian.words[151].word << endl;
		cout << Voc.russian.words[152].word << endl;

		cout << Voc.English.words[150].ptrans[0]->word << endl;
		cout << Voc.English.words[151].ptrans[0]->word << endl;
		cout << Voc.English.words[152].ptrans[0]->word << endl;

		cout << Voc.russian.words[150].ptrans[0]->word << endl;
		cout << Voc.russian.words[151].ptrans[0]->word << endl;
		cout << Voc.russian.words[152].ptrans[0]->word << endl;
		*/

		translate(Voc, word, *trans);
		cout << "\nTranslation: " << trans << endl << endl;
		
		cout << "Enter Esc to quit or anykey to proceed" << endl << endl;
		a = _getch();
	}
	
	removeDictionary(Voc);
}

void initDictionary(Dictionary &dictionary)
{
	dictionary.English.words = new Word[SIZE];
	dictionary.English.quantity = SIZE;
	dictionary.English.oppositeLang = &dictionary.russian;

	dictionary.russian.words = new Word[SIZE];
	dictionary.russian.quantity = SIZE;
	dictionary.russian.oppositeLang = &dictionary.English;
}

void removeDictionary(Dictionary &dictionary)
{
	if (dictionary.English.used > 0)
		for (int i = 0; i < dictionary.English.used; i++)
			delete[] dictionary.English.words[i].ptrans;
	if (dictionary.russian.used > 0)
		for (int i = 0; i < dictionary.russian.used; i++)
			delete[] dictionary.russian.words[i].ptrans;
	delete[] dictionary.English.words;
	delete[] dictionary.russian.words;
	cout << "The dictionary is deleted" << endl;
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
	{
		strcpy(lang.words[i].word, oldWords[i].word);
		lang.words[i].quantity = oldWords[i].quantity;
		lang.words[i].ptrans = oldWords[i].ptrans;
	}

	delete[] oldWords;

	for (int i = 0; i < lang.oppositeLang->used - 1; i++) //удаляем в противоположном языке все указатели на стар. перевод
	{
		delete[] lang.oppositeLang->words[i].ptrans;
		lang.oppositeLang->words[i].quantity = 0;
	}

	for (int i = 0; i < lang.used; i++) //записываем в противоположный язык новые адреса
		for (int j = 0; j < lang.words[i].quantity; j++)
		{
			/*
			if (i == lang.used - 2) 
			{
				cout << "TEST - 2; i = " << i << endl;
				cout << lang.words[i].word << endl;
			}
			if (i == lang.used - 1)
			{
				cout << "TEST - 1; i = " << i << endl;
				cout << lang.words[i].word << endl;
			}
			*/
			increasePtrArray(lang.words[i].ptrans[j]);
			Word *w = lang.words[i].ptrans[j];
			(*w).ptrans[(*w).quantity - 1] = &lang.words[i];
		}

		cout << "The Language is increased" << endl;
		for (int s = 0; s < lang.used; s++)
		{
			cout << s + 1 << ") " << lang.words[s].word << ": ";
			for (int t = 0; t < lang.words[s].quantity; t++)
			{
				cout << lang.words[s].ptrans[t]->word << ", ";
			}
			cout << endl;
		}
		int l;
		cin >> l;
}

void loadWords(Dictionary &dictionary, char *path)
{
	int res = _access(path, 0);
	if (res == 0)
	{
		FILE *pf = fopen(path, "r");
		char buffer[128];
		char Eng[64];
		char rus[64];
		while (!feof(pf))
		{
			fgets(buffer, 64, pf);
						
			char *space = strchr(buffer, ' ');//находим указатель на пробел между словами
			
			int size = space - &buffer[0];
			strncpy(Eng, buffer, size);
			Eng[size] = '\0';
			
			size = strlen(buffer) - size - 2;
			space++;//пропускаем пробел
			strncpy(rus, space, size);
			rus[size] = '\0';
			
			addPairOfWords(dictionary, Eng, rus);
		}

		cout << "The dictionary was loaded successfully" << endl;
		printf("It contains %d English words and %d russian words\n", dictionary.English.used, dictionary.russian.used);
		
	}
	else cout << "Unable to load dictionary!" << endl;
}

//основная функция добавления связки слов в словарь
void addPairOfWords(Dictionary &dictionary, char *Eng, char *rus)
{
	int En = addWordToLang(dictionary.English, Eng);
	int ru = addWordToLang(dictionary.russian, rus);
	setRelations(dictionary, En, ru);
}

//добавление слова, возвращается его порядковый номер
int addWordToLang(Language &lang, char *word)
{
	int current = findWord(lang, word);
	if (current >= 0)
		return current;
	else
	{
		if (lang.quantity == lang.used)
			increaseWordsArray(lang);
		strcpy(lang.words[lang.used++].word, word);
		current = lang.used - 1;
		return current;
	}
}

//установка взаимосвязи между двумя словами
void setRelations(Dictionary &dictionary, int En, int ru)
{
	increasePtrArray(dictionary.English, En);
	increasePtrArray(dictionary.russian, ru);
	
	Word *wEn = &dictionary.English.words[En];
	Word *wRu = &dictionary.russian.words[ru];
	
	(*wEn).ptrans[(*wEn).quantity - 1] = wRu;
	(*wRu).ptrans[(*wRu).quantity - 1] = wEn;
}

//создание/увеличение массива указателей на перевод
void increasePtrArray(Language &lang, int index)
{
	int &quantity = lang.words[index].quantity;
	
	if (quantity == 0)
		lang.words[index].ptrans = new Word*[++quantity];
	else
	{
		Word **old = lang.words[index].ptrans;
		lang.words[index].ptrans = new Word*[++quantity];
		for (int i = 0; i < quantity - 1; i++)
			lang.words[index].ptrans[i] = old[i];
		delete[] old;
	}
}

void increasePtrArray(Word *w)
{
	if ((*w).quantity == 0)
		(*w).ptrans = new Word*[++((*w).quantity)];
	else
	{
		Word **old = (*w).ptrans;
		(*w).ptrans = new Word*[++((*w).quantity)];
		for (int i = 0; i < (*w).quantity - 1; i++)
			(*w).ptrans[i] = old[i];
		delete[] old;
	}
}

void translate(Dictionary &dictionary, char *word, char &trans)
{
	int result = findWord(dictionary.English, word);
	if (result >= 0)
		prepareString(dictionary.English, result, trans);
	else
	{
		result = findWord(dictionary.russian, word);
		if (result >= 0)
			prepareString(dictionary.russian, result, trans);
		else
			strcpy(&trans, "translation was not found");
	}
}

void prepareString(Language &lang, int index, char &trans)
{
	char translation[256];
	strcpy(translation, lang.words[index].ptrans[0]->word);
	
	if (lang.words[index].quantity > 1)
	{
		int position = strlen(translation);
		translation[position++] = ' ';
		translation[position++] = '(';
		
		for (int i = 1; i < lang.words[index].quantity; i++)
		{
			Word w = *lang.words[index].ptrans[i];
			strcpy(&translation[position], w.word);
			position += strlen(w.word);
			
			if (i != lang.words[index].quantity - 1)
			{
				translation[position++] = ',';
				translation[position++] = ' ';
			}
			else
			{
				translation[position++] = ')';
				translation[position] = '\0';
			}
		}
	}
	strcpy(&trans, translation);
}











