#include <QtCore/QCoreApplication>
#include "sqlite3.h"
#include <iostream>
#include "Database.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Database db;
	db.Open_database();
	db.Close_database();
	return a.exec();
}
