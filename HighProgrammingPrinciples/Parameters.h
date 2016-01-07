/*
============================================================================
Name        : Paremeters.h
Author      : Miroslav Vozabal
Description : Represents a class which preserves the boundaries of the alogorithm loaded from a text file.
============================================================================
*/

#pragma once

#include <cfloat>

class Parameters
{
public:
	Parameters();
	~Parameters();

	// The constants initialization - useful for checking errors
	double p_min = DBL_MAX;
	double p_max = DBL_MAX;
	double cg_min = DBL_MAX;
	double cg_max = DBL_MAX;
	double c_min = DBL_MAX;
	double c_max = DBL_MAX;
	double dt_min = DBL_MAX;
	double dt_max = DBL_MAX;
	double h_min = DBL_MAX;
	double h_max = DBL_MAX;
	double k_min = DBL_MAX;
	double k_max = DBL_MAX;
};

