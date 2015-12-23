#pragma once
#include <vector>
#include <math.h>
#include "Interpolation.h"

using namespace std;

class Functions
{
public:
	Functions();
	~Functions();

	void SetUpAttributes(Segment *segment ,vector<double> coefficients);
	double Blood(double t);

private:
	Interpolation interpolation;
	Segment *segment;

	double p, cg, c, dt, h, k; // Coefficients
	double t;

	double Phi(double t);
	double I(double argument);
	double Alfa();
	double Beta();
	double Gama();
	double Discriminant();
};

