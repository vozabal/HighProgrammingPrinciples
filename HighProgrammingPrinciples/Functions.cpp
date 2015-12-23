#include "Functions.h"
#include <float.h>


Functions::Functions()
{

}
Functions::~Functions()
{

}


void Functions::SetUpAttributes(Segment *segment,vector<double> coefficients)
{
	this->p = coefficients[0];
	this->cg = coefficients[1];
	this->c = coefficients[2];
	this->dt = coefficients[3];
	this->h = coefficients[4];
	this->k = coefficients[5];
	this->segment = segment;
}
double Functions::Phi(double t)
{
	double result = t + dt + k * (I(t) - I(t - h)) / h;

	return result;
}

double Functions::I(double argument)//TODO: predavani se zhora, komunikace s db
{
	double result = interpolation.getInterpolatedValue(segment, argument);
	
	return result;
}

double Functions::Alfa()
{
	return cg;
}

double Functions::Beta()
{
	double result = p - cg * I(t);

	return result;
}

double Functions::Gama()
{
	double result = c - I(Phi(t));

	return result;
}

double Functions::Discriminant()
{
	double result = pow(Beta(), 2) - 4 * Alfa() * Gama();

	return result;
}

double Functions::Blood(double t)
{
	this->t = t;
	double result;
	double discriminant = Discriminant();
	if (discriminant < 0)
		result = DBL_MAX;
	else
	{
		result = (-Beta() + sqrt(discriminant)) / 2 * Alfa();
	}

	return result;
}



