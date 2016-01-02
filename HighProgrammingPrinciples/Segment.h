/*
============================================================================
Name        : Segment.h
Author      : Miroslav Vozabal
Description : Represents a segment which collects all its measuredvalues from the database.
============================================================================
*/
#pragma once

#include <vector>
#include "MeasuredValue.h"

using namespace std;

class Segment
{
public:
	Segment(int segmentNumber);
	~Segment();

	int segmentNumber;
	vector<MeasuredValue*> measuredValues;
};


