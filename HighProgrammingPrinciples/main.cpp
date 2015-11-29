#include <QtCore/QCoreApplication>
#include "sqlite3.h"
#include <iostream>
#include "Database.cpp"
#include "Interpolation.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	char *test;
	*test = '\0';
	/*
	if (*test == '\0')
	{
		cout << "It works";
	}
	else
	{
		cout << "It doesn't work";
	}
	*/


	Interpolation db;
	db.Open_database();
	db.SetUpStatement();
	db.Close_database();
	return a.exec();
}
