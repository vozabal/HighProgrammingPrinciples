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
	for (size_t i = 0; i < segments.size(); i++)
	{
		delete(segments[i]);
	}
	
	for (size_t i = 0; i < difuse2params.size(); i++)
	{
		delete(difuse2params[i]);
	}
}