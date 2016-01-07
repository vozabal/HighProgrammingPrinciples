#include "Manager.h"


Manager::Manager(string db_path, string boundaries_path)
{
#ifdef _WIN32
	db_path = "Resources\\direcnet.sqlite";
	boundaries_path = "Resources\\bounds.ini";
#else
	db_path = "Resources//direcnet.sqlite";
	boundaries_path = "Resources//bounds.ini";
#endif
	try
	{
		clock_t begin = clock();	// The start computation time

		IntervalLoader intervalLoader(boundaries_path);	// Initializes the intervalLoader
		Database db(db_path);	// Creates the db layer
		Parameters boundaries = intervalLoader.LoadValues();	//	Loads the algorithm boundaries
		vector<Segment*> segments = db.GetSegments();	// Loads the segments
		Simplex simplex(segments, boundaries);	// Initializates the simplex
		vector<Difuse2Param*> difuse2params = simplex.Compute();	// Computes the coefficients
		OutputTable outTable(difuse2params);	// Initializates the table
		outTable.ConsolePrint();	// Prints the results to the console
		outTable.FilePrint("out.txt");	// Prints the results to the file
		db.PushResults(difuse2params);	// Pushes the resulsts into the database
		FreeAllocatedMemory(segments, difuse2params);	// Releases the allocated memory

		clock_t end = clock();	// The end computation time
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;	// The computation time
		cout << "Elapsed time: " << elapsed_secs << endl;
	}
	catch (exception e)
	{
		cout << e.what();	// Prints the message when an error occurs
		return;
	}
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