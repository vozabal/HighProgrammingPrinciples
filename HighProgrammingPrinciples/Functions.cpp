#include "Functions.h"

Functions::Functions()
{

}
Functions::~Functions()
{

}


void Functions::SetUpAttributes(Segment *segment, vector<double> coefficients)
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
	double result;
	double it = I(t);
	double ith = I(t - h);

	if (it == DBL_MAX || ith == DBL_MAX)
	{
		result = DBL_MAX;
	}
	else
	{
		if (h == 0)
		{
			result = DBL_MAX;
		}
		else
		{
			result = t + dt + k * ((it - ith) / h);
		}
	}

	return result;
}

double Functions::I(double argument)
{
	double result = interpolation.getInterpolatedValue(segment, argument);

	return result;
}

double Functions::Alfa()
{
	if (cg == 0)
	{
		return DBL_MAX;
	}
	else
	{
		return cg;
	}
}

double Functions::Beta()
{
	double result;
	double i = I(t);

	if (i == DBL_MAX)
	{
		result = DBL_MAX;
	}
	else
	{
		result = p - cg * i;
	}

	return result;
}

double Functions::Gama()
{
	double result;
	double phi = Phi(t);


	if (phi == DBL_MAX)
	{
		result = DBL_MAX;
	}
	else
	{
		double i = I(phi);

		if (i == DBL_MAX)
		{
			result = DBL_MAX;
		}
		else
		{
			result = c - i;
		}
	}

	return result;
}

double Functions::Discriminant()
{
	double result;
	double beta = Beta();
	double gama = Gama();
	double alfa = Alfa();

	if (beta == DBL_MAX || gama == DBL_MAX || alfa == DBL_MAX) 
	{
		result = DBL_MAX;
	}
	else
	{
		result = beta * beta - 4 * alfa * gama;
		if (result < 0)
		{
			result = 0;
		}
	}

	return result;
}

double Functions::Blood(double t)
{
	this->t = t;	// setting of the time to the Functions property.
	double result;
	double discriminant = Discriminant();
	double beta = Beta();
	double alfa = Alfa();

	if (discriminant == DBL_MAX || beta == DBL_MAX || alfa == DBL_MAX)
	{
		result = DBL_MAX;
	}
	else
	{
		result = (-beta + sqrt(discriminant)) / (2 * alfa);
	}

	return result;
}



