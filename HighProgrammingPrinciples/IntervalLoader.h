/*
============================================================================
Name        : IntervalLoader.h
Author      : Miroslav Vozabal
Description : Provides a loader of the algorithm initalization. Gets the boundaries of the algorithm parameters.
============================================================================
*/
#pragma once
#include <string>
#include <stdio.h>
#include <stdexcept>
#include "Parameters.h"

using namespace std;

class IntervalLoader
{
public:
	IntervalLoader(string file);
	~IntervalLoader();

	Parameters LoadValues();	// Reads the file and saves the data into the Parameter property.

private:
	// Patterns of finding values
	const string P_MIN = "pmin=";
	const string P_MAX = "pmax=";
	const string CG_MIN = "cgmin=";
	const string CG_MAX = "cgmax=";
	const string C_MIN = "cmin=";
	const string C_MAX = "cmax=";
	const string DT_MIN = "dtmin=";
	const string DT_MAX = "dtmax=";
	const string H_MIN = "hmin=";
	const string H_MAX = "hmax=";
	const string K_MIN = "kmin=";
	const string K_MAX = "kmax=";

	Parameters parameters;
	string file;	// The path and the name of the file.

	// Assigns values found in the string into the parameters property.
	void AssignValues(string entry);
};

