#include "Interpolation.h"

	
Interpolation::Interpolation()
{
}

Interpolation::~Interpolation()
{
}

double Interpolation::getInterpolatedValue(Segment *segment, double time)
{
	double START_TIME = segment->measuredValues.front()->measuredate;
	double END_TIME = segment->measuredValues.back()->measuredate;

	MeasuredValue *previous;
	MeasuredValue *actual;

	double result_ist;

	if (time < START_TIME)	return -1;	//SPECIAl
	else if (time > END_TIME) return -1; //SPECIAl
	else
	{
		for (int i = 0; i < segment->measuredValues.size(); i++)
		{
			actual = segment->measuredValues[i];
			if (actual->measuredate == time)
			{
				result_ist = segment->measuredValues[i]->ist;
				return result_ist;
			}
			if (time > actual->measuredate)
			{
				if (actual->ist != 0)
				{
					previous = actual;
				}
			}
			else
			{
				/*int j = i;
				while (segment.measuredValues[j] == 0 )
				{
					j++;
				}
				*/
				if (actual->ist != 0)
				{
					return InterpolatePoint(previous->ist, actual->ist, previous->measuredate, actual->measuredate, time);
						
				}					
			}
		}			
	}
	return -1;
}


double Interpolation::InterpolatePoint(double point1_y, double point2_y, double point1_x, double point2_x, double x)
{
	double result = point1_y + (x - point1_x) * (point2_y - point1_y) / (point2_x - point1_x);

	return result;
}

