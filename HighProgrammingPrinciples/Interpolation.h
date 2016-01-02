/*
============================================================================
Name        : Interpolation.h
Author      : Miroslav Vozabal
Description : Provides the lienar interpolation for data which is missing.
============================================================================
*/

#pragma once

#include <iostream>
#include "Segment.h"

using namespace std;

class Interpolation
{
public:
	Interpolation();
	~Interpolation();

	// Computes a missing value in the segment. If it isn't possible returns MAX DOUBLE
	double getInterpolatedValue(Segment *segment, double time);

private:
	// The method of Linear Interpolation
	double InterpolatePoint(double point1_y, double point2_y, double point1_x, double point2_x, double x);
};