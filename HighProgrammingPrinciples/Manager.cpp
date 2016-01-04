#include "Manager.h"
#include "OutputTable.h"

Manager::Manager(string db_path, string boundaries_path)
{
#ifdef _WIN32
	db_path = "Resources/direcnet.sqlite";
	boundaries_path = "Resources/bounds.ini";
#else
	db_path = "Resources\direcnet.sqlite";
	boundaries_path = "Resources\bounds.ini";
#endif

	IntervalLoader intervalLoader(boundaries_path);	// Initializes the intervalLoader
	Database db(db_path);	// Creates the db layer

	Parameters boundaries = intervalLoader.LoadValues();	//	Loads the algorithm boundaries
	vector<Segment*> segments = db.GetSegments();	// Loads the segments
	Simplex simplex(segments, boundaries);	// Initializates the simplex
	vector<Difuse2Param*> difuse2params = simplex.Compute();	// Computes the coefficients
	OutputTable outTable(difuse2params);

	outTable.ConsolePrint();	// Prints the results to the console
	outTable.FilePrint("out.txt");	// Prints the results to the file
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