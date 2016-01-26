#include "MPIManager.h"

MPIManager::MPIManager(string db_path, string boundaries_path, string output_file)
{
	//db_path = "Resources//direcnet.sqlite";
	//boundaries_path = "Resources//bounds.ini";
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);	// An identification number is assigned.
		MPI_Comm_size(MPI_COMM_WORLD, &nproc);	// The processes count is assigned.
	try
	{
		double begin = MPI_Wtime(); 	// The start computation time
		IntervalLoader intervalLoader(boundaries_path);	// Initializes the intervalLoader
		Database db(db_path);	// Creates the db layer		
		Parameters boundaries = intervalLoader.LoadValues();	//	Loads the algorithm boundaries
		vector<Segment*> segments = db.GetSegments();	// Loads the segments
		Simplex simplex(segments, boundaries);	// Initializates the simplex
		OutputTable outTable;	// Initializates the table
	
		this->segments = segments;
		this->simplex = &simplex;
		this->outTable = &outTable;
		this->output_file = output_file;
	
		segmentIndex = 0;	// The initialization of the already processed index of the segments vector
		countOfReceived = 0;	// The initialization of already computed received results of segments
		CreateDatatype();	// Creates MPI datatype

		if (rank == 0)	// The farmer branch
		{
			cout << "The computation has started. Please wait until it's finished..." << endl;
			FarmerManager();
			cout << "The computation succesfully finished." << endl;
		}
		else	// The workers' branch
		{
			WorkerManager();
		}
		MPI_Finalize();
		double end = MPI_Wtime();
		double elapsed_secs = end - begin;
		if (rank == 0 ) cout << "Elapsed time: " << elapsed_secs << endl;
	}
	catch (runtime_error e)	// A case of an error
	{
		if (rank == 0) cerr << e.what();	// Prints the message when an error occurs
		MPI_Finalize();

		return;
	}
}

MPIManager::~MPIManager() 
{
	for (size_t i = 0; i < segments.size(); i++)
	{
		delete(segments[i]);
	}
}

void MPIManager::FarmerManager() 
{
	results = new SegmentResult[segments.size()];	// The result array
	SegmentResult *farmerRes = new SegmentResult(); // The temporary buffer
	while (true) 
	{
		MPI_Status st;
		MPI_Recv(farmerRes, 1, result_type, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &st);

		if (farmerRes->segmentid == -1) 
		{
			FarmerSend(st);
		}
		else {
			FarmerReceiveResults(st, farmerRes);

			if (segmentIndex < segments.size()) 
			{
				FarmerSend(st);
			}
		}
		if (countOfReceived >= segments.size()) // The end of the computation
		{
			int end_command = -1;

			for (int k = 1; k < nproc; k++) 
			{
				MPI_Send(&end_command, 1, MPI_INT, k, 0, MPI_COMM_WORLD);	// Message to end the activity is sent
			}
			break;
		}
	}
	outTable->Inicializate(results, segmentIndex);
	outTable->ConsolePrint();	// Prints the results
	if (!output_file.empty())
	{
		outTable->FilePrint(output_file);	// Prints the results
	}
	delete[] results;
	delete farmerRes;
}


void MPIManager::PrintResults()
{
	for (size_t i = 0; i < segments.size(); i++)
	{
		cout << "Fitness: " << results[i].fitness << " ID segment: " << results[i].segmentid << endl;
	}
}

void MPIManager::FarmerSend(MPI_Status st)
{
	int id = segmentIndex;
	MPI_Send(&id, 1, MPI_INT, st.MPI_SOURCE, 0, MPI_COMM_WORLD);
	segmentIndex++;
}

void MPIManager::FarmerReceiveResults(MPI_Status st, SegmentResult *segmentResult)
{
	results[countOfReceived] = *segmentResult;
	countOfReceived++;
}

void MPIManager::WorkerManager() 
{
	SegmentResult woker_result;
	woker_result.segmentid = -1;
	int message = -1;
	while (1) 
	{
		MPI_Status st;
		MPI_Send(&woker_result, 1, result_type, 0, 0, MPI_COMM_WORLD);
		MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
		if (message == -1) 
		{
			break;
		}
		else
		{
			Difuse2Param *difuse2param = simplex->ComputeSegment(message);	// An allocation of difuse2params in ComputeSegemnt
			woker_result.segmentid = difuse2param->segment_id;
			woker_result.s = difuse2param->s;
			woker_result.fitness = difuse2param->fitness;
			woker_result.p = difuse2param->coefficients[0];
			woker_result.cg = difuse2param->coefficients[1];
			woker_result.c = difuse2param->coefficients[2];
			woker_result.dt = difuse2param->coefficients[3];
			woker_result.h = difuse2param->coefficients[4];
			woker_result.k = difuse2param->coefficients[5];
			delete difuse2param;	// THe delete of difuse2params in ComputeSegemnt
		}		
	}
}

void MPIManager::CreateDatatype() 
{
	// Initialization
	MPI_Datatype oldtypes[2];
	int blockcounts[2];
	MPI_Aint offsets[2], extent;

	// Setting up of the types
	offsets[0] = 0;
	oldtypes[0] = MPI_INT;
	blockcounts[0] = 2;
	MPI_Type_extent(MPI_INT, &extent);
	oldtypes[1] = MPI_DOUBLE;
	offsets[1] = 2 * extent;
	blockcounts[1] = 7;

	// Create struct
	MPI_Type_create_struct(2, blockcounts, offsets, oldtypes, &result_type);
	MPI_Type_commit(&result_type);
}




