#include "OutputTable.h"


OutputTable::OutputTable(vector<Difuse2Param*> params)
{
	this->params = params;
}


OutputTable::~OutputTable()
{
}


void OutputTable::PrintBorder()
{
	cout << setfill('-') << setw(1) << "+";	//	Prints the start of the border
	for (size_t i = 0; i < COLUMNS; i++)
	{
		if (i == 0)
		{
			cout << setw(FIRST_COLUMN) << "-" << setw(1) << "+";	// The Different width of the first column
		}
		else if (i == COLUMNS - 1)
		{
			cout << setw(LAST_COLUMN) << "-" << setw(1) << "+";		// The different width of the last column
		}
		else
		{
			cout << setw(COLUMN_WIDTH) << "-" << setw(1) << "+";	// The standard width of the other columns
		}
	}
	cout << endl;	// Prints a new line
}

void OutputTable::PrintRows(int row)
{
	cout << setfill(' ') << setw(1) << "|";//	Prints the left border of the row	
	cout << setw(FIRST_COLUMN) << right << params[row]->segment_id << setw(1) << "|";

	if (params[row]->fitness != DBL_MAX)	// Checking if there is DBL_MAX -> the fitness wasn't found -> The computation failed
	{
		cout << setw(COLUMN_WIDTH) << right << params[row]->fitness << setw(1) << "|";	//	Prints the fitness
	}
	else
	{
		cout << setw(COLUMN_WIDTH) << right << "FAILED" << setw(1) << "|";
	}
	for (size_t i = 0; i < params[row]->coefficients.size(); i++)	// Prints found coefficients
	{
		cout << setw(COLUMN_WIDTH) << right << params[row]->coefficients[i] << setw(1) << "|";	//	The computation failed
	}

	cout << setw(LAST_COLUMN) << right << params[row]->s << setw(1) << "|";	// Prints the default s coefficient
	cout << endl;	// Prints a new line
}

void OutputTable::ConsolePrint()
{
	PrintBorder();
	PrintHead();
	PrintBorder();
	for (size_t i = 0; i < params.size(); i++)
	{
		PrintRows(i);
		PrintBorder();
	}
}

void OutputTable::FilePrint(string file)
{
	std::ofstream out(file);	//	Opens the file
	std::streambuf *coutbuf = std::cout.rdbuf(); //	Saves the old buf
	std::cout.rdbuf(out.rdbuf());	//	Redirects std::cout to file

	ConsolePrint();

	std::cout.rdbuf(coutbuf);	//	Resets to standard output again
}

void OutputTable::PrintHead()
{
	cout << setfill(' ') << setw(1) << "|";
	cout << setw(FIRST_COLUMN) << left << "Segment" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "Fitness" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "p" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "cg" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "c" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "dt" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "h" << setw(1) << "|";
	cout << setw(COLUMN_WIDTH) << left << "k" << setw(1) << "|";
	cout << setw(LAST_COLUMN) << left << "s" << setw(1) << "|";
	cout << endl;
}