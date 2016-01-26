/*
============================================================================
Name        : RandomVectorGenerator.h
Author      : Miroslav Vozabal
Description : Generates random values of every vector which range is determined by the boudaries provides by the IntervalLoader
============================================================================
*/
#pragma once

#include <string>
#include <vector>
#include "IntervalLoader.h"

using namespace std;

class RandomVectorGenerator
{
public:
	RandomVectorGenerator();
	~RandomVectorGenerator();

	vector<vector<double>> GenarateMatrix(); // Returns a matrix of generated coefficients
	vector<double> GenerateVector();	// Returns a vector of generated coefficients
	void Initializate(Parameters boundaries);	// Initializates the boudaries of generated numbers
	void WatchBoundaries(vector<double>* coefficients);	// If the coefficients are out of boundaries the are set up to the closest border

private:
	const int SEED = 1;
	const int ROWS = 6;		// Count of the rows - dimension
	const int COLUMNS = 7;	// Count of the columns - number of peaks
	Parameters boundaries;	// Boundaries of generated numbers

	double FRand(double fMin, double fMax);	// Returns a generated value in the interval.

};
