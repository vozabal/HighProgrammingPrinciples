#include "Segment.h"

Segment::Segment(int segmentNumber)
{
	this->segmentNumber = segmentNumber;
}

Segment::~Segment()
{
	for each (MeasuredValue *item in measuredValues)
	{
		delete(item);
	}
}