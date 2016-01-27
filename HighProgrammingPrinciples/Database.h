/*
============================================================================
Name        : Database.h
Author      : Miroslav Vozabal
Description : Provides a connection to the database. Provides to get data from it and to push results into.
============================================================================
*/
#pragma once

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "SegmentResult.h"
#include "Segment.h"
#include "Difuse2Param.h"

using namespace std;

class Database
{
public:
	Database(string file);	// arg - path to the sql-lite database
	~Database();
	vector<Segment*> GetSegments(); // Vector with loaded segments
	void PushResults(vector<Difuse2Param*> difuse2Params);	//Pushes all results into the database
	void PushResults(SegmentResult *segmentResults, unsigned int segmentResultsSize);	//Pushes all results into the database

private:
	// Prepare statement
	sqlite3 *db;	/* Database handle */
	const char *query;	/* SQL statement, UTF-8 encoded */
	int nByte;	/* Maximum length of zSql in bytes. */
	sqlite3_stmt *stmt;	/* OUT: Statement handle */
	const char *pzTail;	/* OUT: Pointer to unused portion of zSql */

	void PushCoefficients(vector<double> coefficients, double s, int segment_id);		// Pushes one result into the database
	void PushCoefficients(SegmentResult segmentResult);		// Pushes one result into the database
	void Open_database();	//	Opens the database
	void Close_database();	// Closes the database
	string file;	// Name of the file and its path
};

