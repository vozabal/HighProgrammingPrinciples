#include "Segment.h"

Segment::Segment(int segmentNumber)
{
	this->segmentNumber = segmentNumber;
}

Segment::~Segment()
{
	for (size_t i = 0; i < measuredValues.size(); i++)
	{
		delete(measuredValues[i]);
	}
}