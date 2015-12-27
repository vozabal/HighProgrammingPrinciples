#pragma once
#include "Functions.h"
#include "Segment.h"

class Fitness
{
public:
	Fitness();
	~Fitness();

	double GetFitness(Segment *segment, vector<double> coefficients);

private:
	Functions functions;
	vector<double> coefficients;
	vector<double> relativeErrors;
};

