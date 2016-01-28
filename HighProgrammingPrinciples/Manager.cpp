#include "Manager.h"


Manager::Manager(string db_path, string boundaries_path, string output_file)
{
	try
	{
		tbb::tick_count  begin = tbb::tick_count::now();	// The start computation time
		IntervalLoader intervalLoader(boundaries_path);	// Initializes the intervalLoader
		Database db(db_path);	// Creates the db layer
		Parameters boundaries = intervalLoader.LoadValues();	//	Loads the algorithm boundaries
		RandomVectorGenerator randomVectorGenerator;
		randomVectorGenerator.Initializate(boundaries);
		segments = db.GetSegments();	// Loads the segments
		Simplex simplex(segments, boundaries);	// Initializates the simplex
		cout << "The computation has started. Please wait until it's finished..." << endl;
		difuse2params = simplex.Compute();	// Computes the coefficients
		OutputTable outTable(difuse2params);	// Initializates the table
		db.PushResults(difuse2params);	// Pushes the resulsts into the database	
		outTable.ConsolePrint();	// Prints the results to the console
		if (!output_file.empty()) outTable.FilePrint(output_file);	// Prints the results to the file

		tbb::tick_count end = tbb::tick_count::now();// The end computation time		
		double elapsed_secs = ((end - begin).seconds());	// The computation time
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
