#include "Main.h"

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	if (ParseArgs(argc, argv) == false)
	{
		MPI_Finalize();
		return -1;		
	}
	else
	{
		int rank;
		clock_t begin = clock();
		if (argc == 3)
		{
			MPIManager manager(argv[1], argv[2], "");
			rank = manager.rank;
		}
		else
		{
			MPIManager manager(argv[1], argv[2], argv[3]);
			rank = manager.rank;
		}
	
		MPI_Finalize();
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Processs: " << rank << " Elapsed time: " << elapsed_secs << endl;

		return 0;
	}
}

bool ParseArgs(int argc, char *argv[])
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	// prirazeno vlastni identifikacni cislo
	if (argc == 1)
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "There are no parameters! Run the application with parameters [==ERROR==]" << endl;
		}
		return false;
	}
	else if (argc == 2)
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "The second parameter is missing! Run the application with both parameters [==ERROR==]" << endl;
		}
		return false;
	}
	else if (argc == 3) 
	{
		if (rank == 0)
		{
			PrintUsage();
		}
		return true;
	}
	else if (argc == 4)
	{
		if (rank == 0)
		{
			PrintUsage();
		}
		return true;
	}
	else
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "There are too many parameters! Run the application with 2 parameters [==ERROR==]" << endl;
		}
		return false;
	}
}

void PrintUsage()
{
	cout
		<< "Usage: lls-solver <sql_database> <boundaries_file> [-o <outfile>] [-p]\n"
		<< "       lls-solver -i <infile> [-p]\n\n"
		<< "This program calculates parameters of a model given by extended matrix using the Least Linear Squares method.\n"
		<< "The result (i.e. the vector of calculated parameters' values) is printed to an output file named \"result.txt\".\n\n"
		<< "OPTIONS:\n"
		<< "    -o <outfile>   Saves generated coeficients into a text file <outfile>.\n"
		<< "    -p             Prints result to the terminal as well as to the output file.\n\n"
		<< "AUTHOR:  Miroslav Vozabal, University of West Bohemia, 2015/2016" 
		<< endl 
		<< endl;
}
