/*
Подготовка к экзамену
Создать программу для работы с базой данных книжного магазина
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <io.h>
#include <string.h>

using namespace std;

struct Book
{
	char title[64];
	int quantity;
	int year;
	char genre[20];
};

struct Author
{
	char FIO[32];
	Book *books;
	int quantity;
};

struct Store
{
	Author *authors;
	int quantity;
};

void initStore(Store &store);
void removeStore(Store &store);
void showAll(Store &store);
void showAuthors(Store &store);
void showAuthorBooks(Author &author);
void addAuthor(Store &store, char *FIO);
void addBook(Author &author, char *title, int quantity, int year, char *genre);
void addBook(Author &author, char *title);
void removeBook();
void removeAuthor();





void main()
{
	setlocale(LC_ALL, "Ukr");

	Store AzBooka = {};
	initStore(AzBooka);

	int a = 0;
	while (a != 27)
	{
		cout << "Выберите действие:" << endl;
		cout << "q - показать все книги" << endl;
		cout << "w - показать перечень авторов" << endl;
		cout << "a - добавить автора" << endl;
		cout << "s - добавить книгу" << endl;
		cout << "z - удалить автора" << endl;
		cout << "x - удалить книгу" << endl;

		char symb;
		cin >> symb;

		switch (symb)
		{
		case 'q':
		{
			cout << "~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~" << endl;
			cout << "Все книги:" << endl;
			showAll(AzBooka);
			break;
		}
		case 'w':
		{
			cout << "~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~" << endl;
			cout << "Перечень авторов:" << endl;
			showAuthors(AzBooka);
			break;
		}
		case 'a':
		{
			cout << "~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~" << endl;
			cout << "Добавить автора:" << endl;
			cout << "Введите ФИО:" << endl;
			char FIO[64];
			cin >> FIO;
			addAuthor(AzBooka, FIO);
			showAuthors(AzBooka);
		}
		case 's':
		{
			cout << "~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~" << endl;
			cout << "Добавить книгу:" << endl;
		}
		case 'z':
		{

		}
		case 'x':
		{

		}
		case 'j':
		{

		}

		}
	}

	removeStore(AzBooka);
}

void initStore(Store &store)
{
	store.authors = NULL;
	store.quantity = 0;
}

void removeStore(Store &store)
{
	if (store.quantity != 0)
	{
		for (int i = 0; i < store.quantity; i++)
			delete[] store.authors[i].books;
		delete[] store.authors;
	}
}

void showAll(Store &store)
{
	cout << "Все книги: " << endl;
	for (int i = 0; i < store.quantity; i++)
	{
		cout << store.authors[i].FIO << endl;
		for (int j = 0; j < store.authors[i].quantity; i++)
			cout << store.authors[i].books[j].title << endl;
	}
}

void showAuthors(Store &store)
{
	cout << "Автора: " << endl;
	for (int i = 0; i < store.quantity; i++)
		cout << store.authors[i].FIO << endl;
}

void showAuthorBooks(Author &author)
{

}

void addAuthor(Store &store, char *FIO)
{
	/*
	if (store.quantity == 0)
	{
		store.authors = new Author[1];
		store.quantity++;

		store.authors[0].books = NULL;
		store.authors[0].quantity = 0;
		strcpy(store.authors[0].FIO, FIO);
	}

	else
	{
	*/
		Author *old = store.authors;
		store.quantity++;
		store.authors = new Author[store.quantity];

		for (int i = 0; i < store.quantity - 1; i++)
			store.authors[i] = old[i];
		delete[] old;

		store.authors[store.quantity - 1].books = NULL;
		store.authors[store.quantity - 1].quantity = 0;
		strcpy(store.authors[store.quantity - 1].FIO, FIO);
	//}
}

void addBook(Author &author, char *title, int quantity, int year, char *genre)
{
	Book *old = author.books;
	author.quantity++;
	author.books = new Book[author.quantity];

	for (int i = 0; i < author.quantity - 1; i++)
		author.books[i] = old[i];
	delete[] old;

	author.books[author.quantity - 1].quantity = quantity;
	author.books[author.quantity - 1].year = year;
	strcpy(author.books[author.quantity - 1].title, title);
	strcpy(author.books[author.quantity - 1].genre, genre);
}

void addBook(Author &author, char *title)
{
	addBook(author, title, 1, 0, "Not available");
}