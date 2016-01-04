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

using namespace std;

class OutputTable
{
public:
	OutputTable(vector<Difuse2Param*> params);
	~OutputTable();	
	void ConsolePrint();	// Prints the table to the console
	void FilePrint(string file);	// Prints the table into the file.

private:
	const unsigned int COLUMNS = 9;	// The number of the standard columns
	const unsigned int COLUMN_WIDTH = 12;	// The width of the standard columns
	const unsigned int FIRST_COLUMN = 7;	// The width of the first column
	const unsigned int LAST_COLUMN = 4;	// The width of the last column

	void PrintHead();	//	Prints the table head
	void PrintBorder();	//	Prints horizontal borders of cells
	void PrintRows(int row);	// Prints rows
	vector<Difuse2Param*> params;	// The input of the table
};

