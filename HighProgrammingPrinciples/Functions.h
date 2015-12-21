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

	void FillAtributes(vector<double> coefficients, double t);

private:
	Interpolation interpolation;

	double p, cg, c, dt, h, k; // Coefficients
	double t;

	double Phi(double t);
	double I(double argument);
	double Alfa();
	double Beta();
	double Gama();
	double Discriminant();
	double B(double t);
};

