#include "Main.h"

int main(int argc, char *argv[])
{
	PrintUsage();	// Prints the introduction information
	if (ParseArgs(argc, argv) == false)
	{
		return -1;
	}
	else
	{
		if (argc == 1)
		{
			Manager manager(db_path, boundaries_path, output_file);	// DEFAULT VALUES when there are no parameters		
		}
		else if (argc == 3)
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
		cout << "There are no parameters! The application will start with the default parameters: [==MESSAGE==]\n"
			<< "Database: " << db_path << endl
			<< "Configuration file: " << boundaries_path << endl
			<< "Outputfile: " << output_file << endl
			<< endl;
		return true;
	}
	if (argc == 2)
	{
		cout << "The second parameter is missing! Run the application with both parameters: [==ERROR==]" << endl
			<< "Database: " << db_path << endl
			<< "Configuration file: " << "none" << endl
			<< "Outputfile: " << "none" << endl
			<< endl;
		return false;
	}
	else if (argc == 3)
	{
		cout << "Configuration:\n"
			<< "Database: " << argv[1] << endl
			<< "Configuration file: " << argv[2] << endl
			<< "Outputfile: " << "none" << endl
			<< endl;
		return true;
	}
	else if (argc == 4)
	{
		cout << "Configuration:\n"
			<< "Database: " << argv[1] << endl
			<< "Configuration file: " << argv[2] << endl
			<< "Outputfile: " << argv[3] << endl
			<< endl;
		return true;
	}
	else
	{
		cout << "There are too many parameters! Run the application with 0 (default), 2 or 3 parameters [==ERROR==]" << endl;
		return false;
	}
}

void PrintUsage()
{
	cout
		<< "Usage: lls-solver <sql_database> <boundaries_file> <output_file>\n"
		<< "       lls-solver <sql_database> <boundaries_file>\n"
		<< "This program calculates parameters of a glucose transport model by using medical measured database data\n"
		<< "and Simplex Optimization Algorithm created by Nelder and Mead.\n"
		<< "The result (i.e. a table of calculated parameters and their fitnesses' values for particular segments)\n"
		<< "is printed to the OS console and to an output file named \"result.txt\".\n\n"
		<< "AUTHOR:  Miroslav Vozabal, University of West Bohemia, 2015/2016\n"
		<< "---------------------------------------------------------------------------------------------------------"
		<< endl
		<< endl;
}