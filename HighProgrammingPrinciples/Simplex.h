

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

private:
	const double A = 1.0, B = 1.0, G = 0.5, H = 0.5;	// Constants for the operations of the algorithm
	const int ITERATION_NUMBER = 10000;	// The maximum algorithm iterations count
	const int GENERATION_VECTOR_COUNT = 1000; // Start generation attempts of coefficients which don't have a valid fitness.

	// Indexes of compared coefficients
	int MAX_FITNESS_INDEX;
	int MAX2_FITNESS_INDEX;
	int MIN_FITNESS_INDEX;

	Database db;
	RandomVectorGenerator randVectGener;
	vector<vector<double>> coefficients;
	vector<Segment*> segments;
	Fitness fitness;
	
	// Vectors for the operations
	vector<double> fitnesses;
	vector<double> relfection;
	vector<double> centroid;
	
	// The operations which return results in vectors
	vector<double> GetCentroid(int max_position);
	vector<double> GetReflection(vector<double> xg, int max_position);
	vector<double> GetContraction(vector<double> xg, int max_position);
	vector<double> GetExpansion(vector<double> xg, vector<double> xr);

	// Founds the max, max2 and min fitness indexes int a vector of fitnesses
	void GetComparismIndexes(vector<double> fitnesses);

	// Checks if there are at least 2 values in the vector of fitnesses
	bool ValidFitnessesCount(vector<double> fitnesses);

	// Counts and returns the centroid of every coefficients vectors - THE ALGORITHM EXIT CRITERIA 
	vector<double> GetAllPointsCentroid();

};