#include "Manager.h"

Manager::Manager(string db_path, string boundaries_path)
{
	IntervalLoader intervalLoader(boundaries_path);	// Initializes the intervalLoader
	Database db(db_path);	// Creates the db layer

	Parameters boundaries = intervalLoader.LoadValues();	//	Loads the algorithm boundaries
	vector<Segment*> segments = db.GetSegments();	// Loads the segments
	Simplex simplex(segments, boundaries);	// Initializates the simplex
	vector<Difuse2Param*> difuse2params = simplex.Compute();	// Computes the coefficients

	db.PushResults(difuse2params);	// Pushes the resulsts into the database

	FreeAllocatedMemory(segments, difuse2params);	// Releases the allocated memory
}

Manager::~Manager()
{
}

void Manager::FreeAllocatedMemory(vector<Segment*> segments, vector<Difuse2Param*> difuse2params)
{
	for each (Segment *item in segments)
	{
		delete(item);
	}

	for each (Difuse2Param *item in difuse2params)
	{
		delete(item);
	}
}