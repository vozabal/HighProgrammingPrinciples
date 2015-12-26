#include "Interpolation.h"

	
Interpolation::Interpolation()
{
}

Interpolation::~Interpolation()
{
}
// Retruns -1 when the start point of segment doesn't have the value.
double Interpolation::getInterpolatedValue(Segment *segment, double time)
{
	double START_TIME = segment->measuredValues.front()->measuredate;
	double END_TIME = segment->measuredValues.back()->measuredate;

	MeasuredValue *previous = NULL;
	MeasuredValue *actual = NULL;
	

	double result_ist;
	

	if (time < START_TIME)	DBL_MAX;	//SPECIAl
	else if (time > END_TIME) DBL_MAX; //SPECIAl
	else
	{
		for (int i = 0; i < segment->measuredValues.size(); i++)
		{
			actual = segment->measuredValues[i];
			// if the actual time is bigger than the output time
			if (actual->measuredate == time && actual->ist != 0)
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
					/*
					if (time == 36526.750000 && actual->id == 840 && previous->id == 838)
					{
						test = test + 1;
						if (test == 33)
						{
							int cus;
							cus = 2;

						}
					}					
					cout << "===========================" << fixed;
					cout << "Previous id = "  << previous->id << endl;
					cout << "time = " << previous->measuredate << endl;
					cout << "Actual id = " << actual->id << endl;
					cout << "time = " << actual->measuredate << endl;
					cout << "Output time" << time;
					*/

					if (previous == NULL)
					{
						return DBL_MAX;
					}
					else
					{
						if (actual->id == 9437)
						{
							double ahoj;
							ahoj = 1;
						}
						/*if (segment->segmentNumber == 10)
						{
							cout << "===========================" << fixed << endl;
							cout << "Previous id = " << previous->id << endl;
							cout << "time = " << previous->measuredate << endl;
							cout << "Actual id = " << actual->id << endl;
							cout << "time = " << actual->measuredate << endl;
							cout << "Output time" << time;
						}
						*/
						return InterpolatePoint(previous->ist, actual->ist, previous->measuredate, actual->measuredate, time);
					}						
				}					
			}
		}			
	}
	return DBL_MAX;
}


double Interpolation::InterpolatePoint(double point1_y, double point2_y, double point1_x, double point2_x, double x)
{
	double result = point1_y + (x - point1_x) * (point2_y - point1_y) / (point2_x - point1_x);

	return result;
}

