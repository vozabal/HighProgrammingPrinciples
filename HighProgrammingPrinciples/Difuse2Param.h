/*
============================================================================
Name        : Difuse2Param.h
Author      : Miroslav Vozabal
Description : Represents an object which preserves parameters which are put into the database.
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
	int segment_id;
};

