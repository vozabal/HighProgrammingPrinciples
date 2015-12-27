#pragma once

#include <QtCore/QCoreApplication>
#include <QDateTime>
#include <vector>
#include "Fitness.h"
#include "Segment.h"
#include "Database.h"
#include "IntervalLoader.h"
#include "RandomVectorGenerator.h"

using namespace std;

class Simplex
{
public:
	Simplex();
	~Simplex();

	void Compute();
protected:
private:
	const double A = 1.0, B = 1.0, G = 0.5, H = 0.5; // Koeficienty Simplex algoritmu
	const int ITERATION_NUMBER = 10000;				// Iterace po ktere algoritmus skonci

	//indexes of compared coefficients
	int MAX_FITNESS_INDEX;
	int MAX2_FITNESS_INDEX;
	int MIN_FITNESS_INDEX;

	Database db;
	RandomVectorGenerator randVectGener;
	vector<vector<double>> coefficients;
	vector<Segment*> segments;
	Fitness fitness;
	
	vector<double> fitnesses;
	vector<double> relfection;
	vector<double> centroid;

	void GetComparismIndexes(vector<double> fitnesses);

	vector<double> GetCentroid(int max_position);
	vector<double> GetReflection(vector<double> xg, int max_position);
	vector<double> GetContraction(vector<double> xg, int max_position);
	vector<double> GetExpansion(vector<double> xg, vector<double> xr);

};