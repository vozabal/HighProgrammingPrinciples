/*
============================================================================
Name        : Manager.h
Author      : Miroslav Vozabal
Description : Provides the logic of the application. Prepares preconditions for the algoritm, lanuches it and realeases the alocated memory.
============================================================================
*/

#pragma once
#include "tbb/tbb.h"
#include "Simplex.h"
#include "IntervalLoader.h"
#include "Database.h"
#include "Segment.h"
#include "Parameters.h"
#include "Difuse2Param.h"
#include "OutputTable.h"

class Manager
{
public:
	Manager(string db_path, string boundaries_path);	// Passes the arguments from the command line
	~Manager();

private:
	void FreeAllocatedMemory(vector<Segment*> segments, vector<Difuse2Param*> difuse2params);	//	Releases the allocated memory of the application
};

