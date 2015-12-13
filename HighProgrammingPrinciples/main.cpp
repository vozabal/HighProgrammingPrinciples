#include <QtCore/QCoreApplication>
#include "sqlite3.h"
#include <iostream>
#include "Database.h"
#include "Interpolation.cpp"
#include "Simplex.cpp"
#include "RandomVectorGenerator.cpp"
#include "Segment.h"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	char *test;
	//RandomVectorGenerator randVectGener;

	//randVectGener.genarateMatrix(4, 2);

	Database db;

	vector<Segment*> segments = db.GetSegments();
	cout << "the end" << endl;
	//TODO: vycistit komentare, bordel, zaintegrovat a davat pozor na pamet

	//*test = '\0';
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

	/*
	Interpolation db;
	double date1 = db.GetTimeFromDB("2010-01-20T20:03:00+03:00");
	double date2 = db.GetTimeFromDB("2000-01-01T20:00:00+02:00");
	cout << date1 << endl;
	cout << date2 << endl;
	*/
	//cout << db.interpolate_point(0.0, 2.0, 0.0, 2.0);
	//db.Open_database();
	//db.SetUpStatement();
	//db.Close_database();
	return a.exec();
}
