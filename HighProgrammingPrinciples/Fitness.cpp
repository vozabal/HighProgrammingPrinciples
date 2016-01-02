#include "Fitness.h"


Fitness::Fitness()
{

}


Fitness::~Fitness()
{

}

double Fitness::GetFitness(Segment *segment, vector<double> coefficients)
{
	double relative_error = 0;
	double standard_deviation = 0;
	double relative_errors_averrage = 0;
	double result = 0;
	double theory_blood = 0;

	relativeErrors.clear(); // Erases the previous vector of relative errors
	functions.SetUpAttributes(segment, coefficients);	// Sets up a new segment and coefficients for Functions

	// Computation of relative errors
	for each (MeasuredValue *item in segment->measuredValues)
	{
		if (item->blood != 0)
		{
			theory_blood = functions.Blood(item->measuredate);
			if (theory_blood != DBL_MAX)
			{
				theory_blood = functions.Blood(item->measuredate);	// Computing the equation
				relative_error = abs(item->blood - theory_blood) / item->blood;
				relativeErrors.push_back(relative_error);
			}
		}
	}

	if (relativeErrors.size() > 1)	// If there is not just one relative error in the set.
	{
		// Computation of ther relative errors average
		for each (double item in relativeErrors)
		{
			relative_errors_averrage += item;
		}
		relative_errors_averrage /= relativeErrors.size();

		// Computation of the standard deviation
		for each (double item in relativeErrors)
		{
			standard_deviation += pow(item - relative_errors_averrage, 2);
		}
		standard_deviation = sqrt(standard_deviation / (relativeErrors.size() - 1));

		result = relative_errors_averrage + standard_deviation;
	}
	else
	{
		result = DBL_MAX;
	}

	return result;
}
