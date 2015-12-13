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
	
private:
	
};


