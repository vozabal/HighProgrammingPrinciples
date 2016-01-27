#include "Main.h"

int main(int argc, char *argv[])
{
	PrintUsage();
	if (ParseArgs(argc, argv) == false)
	{
		return -1;
	}
	else
	{
		if (argc == 1)
		{
			Manager manager(db_path, boundaries_path, 0, output_file);	// DEFAULT VALUES when there are no parameters		
		}
		else if (argc == 3)
		{
			Manager manager(argv[1], argv[2], 0, "");	// When there are 2 arguments
		}
		else if (argc == 4)
		{
			Manager manager(argv[1], argv[2], atoi(argv[3]), "");	// When there are 2 arguments
		}
		else
		{
			Manager manager(argv[1], argv[2], atoi(argv[3]), argv[4]);	// When there are 3 arguments
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
			<< "Processes count: " << "automatic" << endl
			<< "Outputfile: " << output_file << endl
			<< endl;
		return true;
	}
	if (argc == 2)
	{
		cout << "The second parameter is missing! Run the application with both parameters: [==ERROR==]" << endl
			<< "Database: " << db_path << endl
			<< "Configuration file: " << "none" << endl
			<< "Processes count: " << "automatic" << endl
			<< "Outputfile: " << "none" << endl
			<< endl;
		return false;
	}
	else if (argc == 3)
	{
		cout << "Configuration:\n"
			<< "Database: " << argv[1] << endl
			<< "Configuration file: " << argv[2] << endl
			<< "Processes count: " << "automatic" << endl
			<< "Outputfile: " << "none" << endl
			<< endl;
		return true;
	}
	else if (argc == 4)
	{
		cout << "Configuration:\n"
			<< "Database: " << argv[1] << endl
			<< "Configuration file: " << argv[2] << endl
			<< "Processes count: " << argv[3] << endl
			<< "Outputfile: " << "none" << endl
			<< endl;
		return true;
	}
	else if (argc == 5)
	{
		cout << "Configuration:\n"
			<< "Database: " << argv[1] << endl
			<< "Configuration file: " << argv[2] << endl
			<< "Processes count: " << argv[3] << endl
			<< "Outputfile: " << argv[4] << endl
			<< endl;
		return true;
	}
	else
	{
		cout << "There are too many parameters! Run the application with 0 (default), 3 or 4 parameters [==ERROR==]" << endl;
		return false;
	}
}

void PrintUsage()
{
	cout
		<< "Usage: Vozabal_PPR_Sem\n"
		<< "       Vozabal_PPR_Sem <sql_database> <boundaries_file>\n"
		<< "       Vozabal_PPR_Sem <sql_database> <boundaries_file> <processes_count>\n"
		<< "       Vozabal_PPR_Sem <sql_database> <boundaries_file> <processes_count> <output_file>\n"
		<< "This program calculates parameters of a glucose transport model by using medical measured database data\n"
		<< "and Simplex Optimization Algorithm created by Nelder and Mead.\n"
		<< "The result (i.e. a table of calculated parameters and their fitnesses values for particular segments)\n"
		<< "is printed to the OS console and possibly to an output file named \"result.txt\". If it is launched\n"
		<< "without set up parameters the default will be used. For the tbb default number of processes use zero value.\n\n"
		<< "AUTHOR:  Miroslav Vozabal, University of West Bohemia, 2015/2016\n"
		<< "-----------------------------------------------------------------------------------------------------------"
		<< endl
		<< endl;
}