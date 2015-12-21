#pragma once

#include <iostream>
#include "Segment.h"

using namespace std;

class Interpolation
{
public:
	Interpolation();
	~Interpolation();

	double getInterpolatedValue(Segment *segment, double time);


private:
	double InterpolatePoint(double point1_y, double point2_y, double point1_x, double point2_x, double x);
};