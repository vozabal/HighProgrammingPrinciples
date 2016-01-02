/*
============================================================================
Name        : Functions.h
Author      : Miroslav Vozabal
Description : Represents the equations system to count the fitness of the algorithm.
============================================================================
*/
#pragma once

#include <vector>
#include <math.h>
#include <float.h>
#include "Interpolation.h"

using namespace std;

class Functions
{
public:
	Functions();
	~Functions();

	void SetUpAttributes(Segment *segment, vector<double> coefficients);	// Sets up the segmen and the vector of coefficienst to comupute with. If attempts for computing the system fail. The method returns Max Double value.
	double Blood(double t);	// The computation of the equiation system

private:
	Interpolation interpolation;	// To interpolate missing data the segment.
	Segment *segment;	// The segment where is the system computed in.

	double p, cg, c, dt, h, k; // Coefficients
	double t;

	// The equations system
	double Phi(double t);
	double I(double argument);
	double Alfa();
	double Beta();
	double Gama();
	double Discriminant();
};

