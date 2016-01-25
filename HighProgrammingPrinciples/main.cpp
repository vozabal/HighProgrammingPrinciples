#include "Main.h"

int main(int argc, char *argv[])
{
	
	if (ParseArgs(argc, argv) == false)
	{
		return -1;
	}
	else
	{
		PrintUsage();	// Prints the introduction information
		if (argc == 3)
		{
			Manager manager(argv[1], argv[2], "");	// When there are 2 arguments
		}
		else
		{
			Manager manager(argv[1], argv[2], argv[3]);	// When there are 3 arguments
		}		
	}
	return 0;	
}

bool ParseArgs(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "There are no parameters! Run the application with parameters [==ERROR==]" << endl;
		return false;
	}
	else if (argc == 2)
	{
		cout << "The second parameter is missing! Run the application with both parameters [==ERROR==]" << endl;
		return false;
	}
	else if (argc == 3) 
	{
		return true;
	}
	else if (argc == 4)
	{
		return true;
	}
	else
	{
		cout << "There are too many parameters! Run the application with 2 parameters [==ERROR==]" << endl;
		return false;
	}
}

void PrintUsage()
{
	cout
		<< "Usage: lls-solver <sql_database> <boundaries_file> <output_file>\n"
		<< "       lls-solver <sql_database> <boundaries_file>\n"
		<< "This program calculates parameters of a glucose transport model by using medical measured database data and Simplex Optimization Algorithm created by Nelder and Mead.\n"
		<< "The result (i.e. a table of calculated parameters and their fitnesses' values for particular segments) is printed to the OS console and to an output file named \"result.txt\".\n\n"
		<< "AUTHOR:  Miroslav Vozabal, University of West Bohemia, 2015/2016"
		<< endl
		<< endl;
}