#pragma once

#include <iostream>
#include "MPIManager.h"
#include <ctime>

using namespace std;

const string output_file = "result.txt";
#ifdef _WIN32
const string db_path = "Resources\direcnet.sqlite";
const string boundaries_path = "Resources\bounds.ini";
#else
const string db_path = "Resources/direcnet.sqlite";
const string boundaries_path = "Resources/bounds.ini";
#endif

bool ParseArgs(int argc, char *argv[]);	// Parses the command line parameters
void PrintUsage();	// Prints introduction information of the application