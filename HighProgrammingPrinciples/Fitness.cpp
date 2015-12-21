#include "Fitness.h"


Fitness::Fitness(Segment *segment, vector<double> coefficients)
{
	this->segment = segment;
	this->coefficients = coefficients;
}


Fitness::~Fitness()
{

}

double Fitness::GetFitness()
{
	for each (MeasuredValue *item in segment->measuredValues)
	{
		if (item->blood != 0)
		{
			functions.FillAtributes(coefficients, item->blood);
		}
	}

	return 2.1;
}
