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
		if (argc == 1)
		{
			MPIManager manager(db_path, boundaries_path, output_file);	// DEFAULT VALUES when there are no parameters		
		}
		else if (argc == 3) // If there are two parameters
		{
			MPIManager manager(argv[1], argv[2], "");
		}		
		else  // If there is the third parameter - an output file for the result
		{
			MPIManager manager(argv[1], argv[2], argv[3]);
		}
		return 0;
	}
}

bool ParseArgs(int argc, char *argv[])
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	// An identification number is assigned
	if (argc == 1)
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "There are no parameters! The application will start with the default parameters: [==MESSAGE==]\n"
				<< "Database: " << db_path << endl
				<< "Configuration file: " << boundaries_path << endl
				<< "Outputfile: " << output_file << endl
				<< endl;
		}
		return true;
	}
	else if (argc == 2)
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "The second parameter is missing! Run the application with both parameters: [==ERROR==]" << endl
				<< "Database: " << db_path << endl
				<< "Configuration file: " << "none" << endl
				<< "Outputfile: " << "none" << endl
				<< endl;
		}
		return false;
	}
	else if (argc == 3) 
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "Configuration:\n"
				<< "Database: " << argv[1] << endl
				<< "Configuration file: " << argv[2] << endl
				<< "Outputfile: " << "none" << endl
				<< endl;
		}
		return true;
	}
	else if (argc == 4)
	{
		if (rank == 0)
		{
			PrintUsage();
			cout << "Configuration:\n"
				<< "Database: " << argv[1] << endl
				<< "Configuration file: " << argv[2] << endl
				<< "Outputfile: " << argv[3] << endl
				<< endl;
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
		<< "Usage: Vozabal_PPR_Sem\n"
		<< "       Vozabal_PPR_Sem <sql_database> <boundaries_file>\n"
		<< "       Vozabal_PPR_Sem <sql_database> <boundaries_file> <output_file>\n"
		<< "This program calculates parameters of a glucose transport model by using medical measured database data\n"
		<< "and Simplex Optimization Algorithm created by Nelder and Mead.\n"
		<< "The result (i.e. a table of calculated parameters and their fitnesses values for particular segments)\n"
		<< "is printed to the OS console and possibly to an output file named \"result.txt\". If it is launched\n"
		<< "without set up parameters the default values will be used.\n\n"
		<< "AUTHOR:  Miroslav Vozabal, University of West Bohemia, 2015/2016\n"
		<< "---------------------------------------------------------------------------------------------------------"
		<< endl
		<< endl;
}
