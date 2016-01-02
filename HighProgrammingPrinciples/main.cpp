#include <QtCore/QCoreApplication>
#include <vld.h>
#include <iostream>
#include "Manager.h"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Manager manager(argv[1], argv[2]);

	//pokus
	return a.exec();
}
