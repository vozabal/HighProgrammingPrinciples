#include "Manager.h"


Manager::Manager(string db_path, string boundaries_path, string output_file)
{

	try
	{
		clock_t begin = clock();	// The start computation time
		IntervalLoader intervalLoader(boundaries_path);	// Initializes the intervalLoader
		Database db(db_path);	// Creates the db layer
		Parameters boundaries = intervalLoader.LoadValues();	//	Loads the algorithm boundaries
		segments = db.GetSegments();	// Loads the segments
		Simplex simplex(segments, boundaries);	// Initializates the simplex
		cout << "The computation has started. Please wait until it's finished..." << endl;
		difuse2params = simplex.Compute();	// Computes the coefficients
		OutputTable outTable(difuse2params);	// Initializates the table
		outTable.ConsolePrint();	// Prints the results to the console
		if (!output_file.empty()) outTable.FilePrint(output_file);	// Prints the results to the file
		db.PushResults(difuse2params);	// Pushes the resulsts into the database	

		clock_t end = clock();	// The end computation time
		double elapsed_secs = difftime(end, begin) / CLOCKS_PER_SEC;	// The computation time
		cout << "The computation succesfully finished." << endl;
		cout << "Elapsed time: " << elapsed_secs << endl;
	}
	catch (runtime_error e)
	{
		cerr << e.what();	// Prints the message when an error occurs
		return;
	}
}

Manager::~Manager()
{
	// Releases the allocated memory
	for (size_t i = 0; i < segments.size(); i++)
	{
		delete(segments[i]);
	}

	for (size_t i = 0; i < difuse2params.size(); i++)
	{
		delete(difuse2params[i]);
	}
}
