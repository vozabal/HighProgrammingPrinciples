#include <QtCore/QCoreApplication>
#include <iostream>
#include "Simplex.h"
#include "IntervalLoader.h"
#include "Manager.h"
#include <vld.h>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	//string db_path = argv[1];
	//string boundaries_path = argv[2];

	Manager manager(argv[1], argv[2]);
	//LDEnable();
	/*
	IntervalLoader intervalLoader(boundaries_path);
	Database db(db_path);
	

	//vector<Segment*> segments = db.GetSegments();
	Simplex simplex(db.GetSegments(), intervalLoader.LoadValues());
	db.PushResults(simplex.Compute());
	*/

	return a.exec();
}
