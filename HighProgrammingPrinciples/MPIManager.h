#pragma once

#include <mpi.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include "tbb/tbb.h"
#include "Simplex.h"
#include "IntervalLoader.h"
#include "Database.h"
#include "Segment.h"
#include "Parameters.h"
#include "Difuse2Param.h"
#include "OutputTable.h"
#include "SegmentResult.h"

using namespace std;

class MPIManager {
public:
	int rank;	// The identification number of a process
	MPIManager(string db_path, string boundaries_path, string output_file);
	~MPIManager();

private:
	vector<Segment*> segments;	// Entry data
	Simplex *simplex;	// Computes the algorithm
	OutputTable *outTable;	// Ouput in the result form of a table 
	SegmentResult *results;		// A pointer to the array of results
	string output_file;	// A name of the output file if it's entered	
	int nproc;	// pocet procesu pouzivajicich MPI
	unsigned int segmentIndex;	// The already processed index of the segments vector
	unsigned int countOfReceived;	// The count of already received results		
	MPI_Datatype result_type;	// Loaded frome createdatatype

	void FarmerManager();	// The farmer code
	void WorkerManager();	// The workers' code
	void CreateDatatype();	// Creates a data type for the MPI communication
	void PrintResults();	// Prints a short version the results
	void FarmerSend(MPI_Status st);	// Sends to a worker another task
	void FarmerReceiveResults(MPI_Status st, SegmentResult *segmentResult);	// Saves a worker result to the results array



};