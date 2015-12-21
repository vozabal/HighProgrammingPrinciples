#pragma once
#include <string>
#include <vector>
#include "IntervalLoader.h"

using namespace std;

// Generates a matrix of random parameters determined by boundaries parameters of intervalLoader
class RandomVectorGenerator
{
public:
	RandomVectorGenerator();
	~RandomVectorGenerator();
	vector<vector<double>> GenarateMatrix(); // returns a matrix of generated parameters

private:
	const int ROWS = 6;		//count of the rows - dimension
	const int COLUMNS = 7;	//count of the columns - number of peaks

	IntervalLoader intervalLoader;	//loads the boundaries of new generated parameters

	double FRand(double fMin, double fMax);	// returns generated value in the interval.

};
