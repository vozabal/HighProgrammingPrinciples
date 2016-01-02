/*
============================================================================
Name        : Fitness.h
Author      : Miroslav Vozabal
Description : Counts a fitness which is used like the exit criteria of the algorithm.
============================================================================
*/
#pragma once

#include "Functions.h"
#include "Segment.h"

class Fitness
{
public:
	Fitness();
	~Fitness();
	// It counts fitness of one segment for one coefficients vecrotr. The parameters is the segment which are values computed in and the vector of coefficients. If there is not a valid result. The method returns MAX DOUBLE value.
	double GetFitness(Segment *segment, vector<double> coefficients);

private:
	Functions functions;	// Function which are computed fitnesses from.
	vector<double> coefficients;
	vector<double> relativeErrors;
};

