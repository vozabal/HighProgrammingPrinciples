/*
============================================================================
Name        : Database.h
Author      : Miroslav Vozabal
Description : Provides the computation of Simplex Optimization Algorithm (Nelder and Mead). The entry data are segments and boundaries for the generation of coefficients.
============================================================================
*/
#pragma once

#include <vector>
#include "Fitness.h"
#include "Segment.h"
#include "RandomVectorGenerator.h"
#include "Difuse2Param.h"

using namespace std;

class Simplex
{
public:
	Simplex(vector<Segment*> segments, Parameters boundaries);	// Passes the segments and the boundaries for generated coefficients of the algormithm
	~Simplex();
	vector<Difuse2Param*> Compute();

private:
	const double A = 1.0, B = 1.0, G = 0.5, H = 0.5;	// Constants for the operations of the algorithm
	const unsigned int ITERATION_NUMBER = 10;	// The maximum algorithm iterations count
	const unsigned int GENERATION_VECTOR_COUNT = 10; // Start generation attempts of coefficients which don't have a valid fitness.

	// Indexes of compared coefficients
	unsigned int MAX_FITNESS_INDEX;
	unsigned int MAX2_FITNESS_INDEX;
	unsigned int MIN_FITNESS_INDEX;

	RandomVectorGenerator randVectGener;
	vector<vector<double>> coefficients;
	vector<Segment*> segments;
	Fitness fitness;
	vector<Difuse2Param*> difuse2params;

	// Vectors for the operations
	vector<double> fitnesses;
	vector<double> relfection;
	vector<double> centroid;

	// The operations which return results in vectors
	vector<double> GetCentroid(unsigned int max_position);
	vector<double> GetReflection(vector<double> xg, int max_position);
	vector<double> GetContraction(vector<double> xg, int max_position);
	vector<double> GetExpansion(vector<double> xg, vector<double> xr);

	void GetComparismIndexes(vector<double> fitnesses);	// Founds the max, max2 and min fitness indexes int a vector of fitnesses	
	bool ValidFitnessesCount(vector<double> fitnesses);	// Checks if there are at least 2 values in the vector of fitnesses	
	vector<double> GetAllPointsCentroid();	// Counts and returns the centroid of every coefficients vectors - THE ALGORITHM EXIT CRITERIA 
};