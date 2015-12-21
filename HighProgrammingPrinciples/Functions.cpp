#include "Functions.h"


Functions::Functions()
{

}
Functions::~Functions()
{

}


void Functions::FillAtributes(vector<double> coefficients, double t)
{
	this->p = coefficients[0];
	this->cg = coefficients[1];
	this->c = coefficients[2];
	this->dt = coefficients[3];
	this->h = coefficients[4];
	this->k = coefficients[5];
	this->t = t;
}
double Functions::Phi(double t)
{
	double result = t + dt + k * (I(t) - I(t - h)) / h;

	return result;
}

double Functions::I(double argument)//TODO: predavani se zhora, komunikace s db
{
	double result = 0;
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

double Functions::B(double t)
{
	double result = (-Beta() + sqrt(Discriminant())) / 2 * Alfa();

	return result;
}



