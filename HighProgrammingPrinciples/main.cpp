#include <QtCore/QCoreApplication>
#include "sqlite3.h"
#include <iostream>
#include "Database.h"
#include "Interpolation.h"
#include "Simplex.h"
#include "RandomVectorGenerator.h"
#include "Segment.h"
#include "IntervalLoader.h"
#include "Fitness.h"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	/*char *test;
	RandomVectorGenerator randVectGener;
	Database db;

	vector<vector<double>> coefficients = randVectGener.GenarateMatrix();
	vector<Segment*> segments = db.GetSegments();
	Fitness fitness;
	fitness.GetFitness(segments.front(), coefficients.front());
	*/

	Simplex simplex;
	simplex.Compute();


	

	//vector<Segment*> segments = db.GetSegments();
	/*
	vector<Segment*> segments = db.GetSegments();

	IntervalLoader intrLoader;

	vector<double> vct;
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	vct.push_back(2.0);
	//intrLoader.AssignValues("pmin=1");
	intrLoader.loadValues();
	cout << "the end" << endl;
	db.PushCoefficients(vct);
	*/

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
	Interpolation inter;
	cout << inter.InterpolatePoint(0.0, 2.0, 0.0, 2.0, 0.5) << endl;

	cout << inter.getInterpolatedValue(db.GetSegments().front(), 36526.9);

	*/
	/*
	double date1 = db.GetTimeFromDB("2010-01-20T20:03:00+03:00");
	double date2 = db.GetTimeFromDB("2000-01-01T20:00:00+02:00");
	cout << date1 << endl;
	cout << date2 << endl;
	*/
	//db.Open_database();
	//db.SetUpStatement();
	//db.Close_database();
	return a.exec();
}
