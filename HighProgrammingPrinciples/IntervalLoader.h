#pragma once
#include <string>
#include "Parameters.h"
#include <stdio.h>
#include <string>

using namespace std;

class IntervalLoader
{
public:
	IntervalLoader();
	~IntervalLoader();
	Parameters parameters;
	
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

	void AssignValues(string entry);
	Parameters loadValues();
};

