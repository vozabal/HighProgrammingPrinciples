/*
============================================================================
Name        : Difuse2Param.h
Author      : Miroslav Vozabal
Description : Represents an object which preserves results parameters which are put into the database apart from fitness attribute.
============================================================================
*/
#pragma once

#include <vector>

using namespace std;

class Difuse2Param
{
public:
	Difuse2Param();
	~Difuse2Param();

	vector<double> coefficients;
	double s = 1;
	int segment_id;
	double fitness;
};

