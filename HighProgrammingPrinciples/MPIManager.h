#pragma once

#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include "Simplex.h"
#include "IntervalLoader.h"
#include "Database.h"
#include "Segment.h"
#include "Parameters.h"
#include "Difuse2Param.h"
#include "OutputTable.h"
#include <vector>
#include <string>
#include "SegmentResult.h"

using namespace std;

class MPIManager {

private:
	IntervalLoader *intervalLoader;
	Database *db;
	Parameters *boundaries;
	vector<Segment*> segments;
	Simplex *simplex;
	vector<Difuse2Param*> difuse2params;
	OutputTable *outTable;
	
	int nproc;	// pocet procesu pouzivajicich MPI
	unsigned int segmentIndex;
	unsigned int countOfReceived;
		
	MPI_Datatype result_type;	// Loaded frome createdatatype
	SegmentResult *results;	// 

public:
	int rank;	// identifikacni cislo
	MPIManager(string db_path, string boundaries_path);
	~MPIManager();
	void farmerManager();
	void workerManager();
	void createDatatype();
	void farmerSend(MPI_Status st);
	void farmerReceiveResults(MPI_Status st, SegmentResult *segmentResult);
	void PrintResults();
	vector<Difuse2Param*> ChangeResultFormat();
};