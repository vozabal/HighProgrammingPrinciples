#pragma once
#include "Functions.h"
#include "Segment.h"

class Fitness
{
public:
	Fitness(Segment *segment, vector<double> coefficients);
	~Fitness();

	double GetFitness();

private:
	Functions functions;
	Segment *segment;
	vector<double> coefficients;
};

