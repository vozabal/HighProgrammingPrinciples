/*
============================================================================
Name        : OutputTable.h
Author      : Miroslav Vozabal
Description : Provides the logic of the application. Prepares preconditions for the algoritm, lanuches it and realeases the alocated memory.
============================================================================
*/
#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <cfloat>
#include "Difuse2Param.h"
#include "SegmentResult.h"

using namespace std;

class OutputTable
{
public:
	OutputTable();
	~OutputTable();	
	void ConsolePrint();	// Prints the table to the console
	void FilePrint(string file);	// Prints the table into the file.
	void Inicializate(SegmentResult *segmentResults, unsigned int segmentResultsSize);

private:
	const unsigned int COLUMNS = 9;	// The number of the standard columns
	const unsigned int COLUMN_WIDTH = 12;	// The width of the standard columns
	const unsigned int FIRST_COLUMN = 7;	// The width of the first column
	const unsigned int LAST_COLUMN = 4;	// The width of the last column

	void PrintHead();	//	Prints the table head
	void PrintBorder();	//	Prints horizontal borders of cells
	void PrintRows(int row);	// Prints rows
	SegmentResult *segmentResults;	// The input of the table
	unsigned int segmentResultsSize;	// Size of the results
};

