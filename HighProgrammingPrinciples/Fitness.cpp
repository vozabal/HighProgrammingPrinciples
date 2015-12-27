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
	double theory_blood;

	relativeErrors.clear(); // Erases the previous vector of relative errors
	functions.SetUpAttributes(segment ,coefficients);	// Sets up a new segment and coefficients for Functions

	for each (MeasuredValue *item in segment->measuredValues)
	{
		if (item->blood != 0)
		{
			theory_blood = functions.Blood(item->measuredate);
			if (theory_blood != DBL_MAX)
			{
				relative_error = abs(item->blood - theory_blood) / item->blood;
				relativeErrors.push_back(relative_error);
			}			
		}
	}

	for each (double item in relativeErrors)
	{
		relative_errors_averrage += item; //Definovat na nulu
	}	
	relative_errors_averrage /= relativeErrors.size();

	for each (double item in relativeErrors)
	{
		standard_deviation += pow(relative_errors_averrage - item, 2);
	}
	standard_deviation = sqrt (standard_deviation / relativeErrors.size());

	result = relative_errors_averrage + standard_deviation;

	return result;
}
