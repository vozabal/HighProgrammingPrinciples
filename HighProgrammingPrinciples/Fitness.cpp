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
	double standard_deviation_averrage = 0;
	double relative_errors_averrage = 0;
	double result = 0;
	double theory_blood = 0;

	relativeErrors.clear(); // Erases the previous vector of relative errors
	functions.SetUpAttributes(segment, coefficients);	// Sets up a new segment and coefficients for Functions

	// Computation of relative errors
	for (size_t i = 0; i < segment->measuredValues.size(); i++)
	{
		if (segment->measuredValues[i]->blood != 0)
		{
			theory_blood = functions.Blood(segment->measuredValues[i]->measuredate);
			if (theory_blood != DBL_MAX)
			{
				theory_blood = functions.Blood(segment->measuredValues[i]->measuredate);	// Computing the equation
				relative_error = (std::abs(segment->measuredValues[i]->blood - theory_blood)) / segment->measuredValues[i]->blood;
				relativeErrors.push_back(relative_error);
			}
		}
	}

	if (relativeErrors.size() > 1)	// If there is not just one relative error in the set.
	{
		// Computation of ther relative errors average
		for (size_t i = 0; i < relativeErrors.size(); i++)
		{
			relative_errors_averrage += relativeErrors[i];
		}
		relative_errors_averrage /= relativeErrors.size();

		// Computation of the standard deviation
		for (size_t i = 0; i < relativeErrors.size(); i++)
		{
			standard_deviation_averrage += (relativeErrors[i] - relative_errors_averrage) * (relativeErrors[i] - relative_errors_averrage);
		}
		standard_deviation = sqrt(standard_deviation_averrage / relativeErrors.size());//odstr

		result = relative_errors_averrage + standard_deviation;
	}
	else
	{
		result = DBL_MAX;
	}

	return result;
}
