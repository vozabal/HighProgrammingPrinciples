/*
============================================================================
Name        : Paremeters.h
Author      : Miroslav Vozabal
Description : Represents a class which preserves the boundaries of the alogorithm loaded from a text file.
============================================================================
*/

#pragma once

class Parameters
{
public:
	Parameters();
	~Parameters();

	double p_min;
	double p_max;
	double cg_min;
	double cg_max;
	double c_min;
	double c_max;
	double dt_min;
	double dt_max;
	double h_min;
	double h_max;
	double k_min;
	double k_max;

private:

};

