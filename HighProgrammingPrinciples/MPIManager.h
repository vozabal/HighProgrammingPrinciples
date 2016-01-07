#pragma once

#include <mpi.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
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

private:
	vector<Segment*> segments;
	Simplex *simplex;
	OutputTable *outTable;
	SegmentResult *results;	
	int nproc;	// pocet procesu pouzivajicich MPI
	unsigned int segmentIndex;
	unsigned int countOfReceived;		
	MPI_Datatype result_type;	// Loaded frome createdatatype

	string output_file;

public:
	int rank;	// identifikacni cislo
	MPIManager(string db_path, string boundaries_path, string output_file);
	~MPIManager();
	void farmerManager();
	void workerManager();
	void createDatatype();
	void farmerSend(MPI_Status st);
	void farmerReceiveResults(MPI_Status st, SegmentResult *segmentResult);
	void PrintResults();
	vector<Difuse2Param*> ChangeResultFormat();
};