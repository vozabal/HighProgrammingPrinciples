#include "Fitness.h"


Fitness::Fitness()
{

}


Fitness::~Fitness()
{

}
//Vypocita fitnes jednoho segmentu pro jeden vektor parametru. Nejprve je nutne nastavit atributy (vektor a segment).
double Fitness::GetFitness(Segment *segment, vector<double> coefficients) //nejspis odstinit parametry ze tridy segment + coefficients
{	
	double relative_error = 0;
	double standard_deviation = 0;
	double relative_errors_averrage = 0;
	double result = 0;
	double theory_blood = 0;

	relativeErrors.clear(); // Erases the previous vector of relative errors
	functions.SetUpAttributes(segment ,coefficients);	// Sets up a new segment and coefficients for Functions

	for each (MeasuredValue *item in segment->measuredValues)
	{
		if (item->blood != 0)
		{
			theory_blood = functions.Blood(item->measuredate);
			if (theory_blood != DBL_MAX)
			{
				theory_blood = functions.Blood(item->measuredate);
				relative_error = abs(item->blood - theory_blood) / item->blood;
				relativeErrors.push_back(relative_error);
			}			
		}
	}

	if (relativeErrors.size() != 0)
	{
		for each (double item in relativeErrors)
		{
			relative_errors_averrage += item; //Definovat na nulu
		}	
		relative_errors_averrage /= relativeErrors.size();

		for each (double item in relativeErrors)
		{
			standard_deviation += pow(relative_errors_averrage - item, 2);
		}
		standard_deviation = sqrt(standard_deviation / relativeErrors.size());

		result = relative_errors_averrage + standard_deviation;
	}
	else
	{
		result = DBL_MAX;
	}

	return result;
}
