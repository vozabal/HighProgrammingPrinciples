/*
============================================================================
Name        : OutputTable.h
Author      : Miroslav Vozabal
Description : Provides the logic of the application. Prepares preconditions for the algoritm, lanuches it and realeases the alocated memory.
============================================================================
*/
#pragma once

struct SegmentResult {
	int segmentid, s;
	double fitness, p, cg, c, dt, h, k;
};