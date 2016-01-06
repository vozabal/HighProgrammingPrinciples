#include "Main.h"

int main(int argc, char *argv[])
{
	/*
	if (ParseArgs(argc, argv) == false)
	{
		return -1;
	}
	else
	{
		PrintUsage();
		Manager manager(argv[1], argv[2]);

		return 0;
	}
	*/

	MPI_Init(&argc, &argv);
	//PrintUsage();
	MPIManager manager(argv[1], argv[2]);
	//int rank = manager.rank;
	MPI_Finalize();
	//printf("Run process no. %i\n", rank);

	return 0;
	
}

bool ParseArgs(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "There are no parameters! Run the application with parameters" << endl;
		return false;
	}
	else if (argc == 2)
	{
		cout << "The second parameter is missing! Run the application with both parameters" << endl;
		return false;
	}
	else if (argc == 3) 
	{
		return true;
	}
	else
	{
		cout << "There are too many parameters! Run the application with 2 parameters" << endl;
		return false;
	}
}

void PrintUsage()
{
	cout << "Usage: lls-solver <sql_database> <boundaries_file> [-o <outfile>] [-p]\n"
		<< "       lls-solver -i <infile> [-p]\n\n"
		<< "This program calculates parameters of a model given by extended matrix using the Least Linear Squares method.\n"
		<< "The result (i.e. the vector of calculated parameters' values) is printed to an output file named \"result.txt\".\n\n"
		<< "OPTIONS:\n"
		<< "    -o <outfile>   Saves generated coeficients into a text file <outfile>.\n"
		<< "    -p             Prints result to the terminal as well as to the output file.\n\n"
		<< "AUTHOR:  Miroslav Vozabal, University of West Bohemia, 2015/2016" << std::endl << std::endl;
}
