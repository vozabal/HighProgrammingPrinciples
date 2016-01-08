#pragma once

#include <iostream>
#include "MPIManager.h"
#include <ctime>

using namespace std;

bool ParseArgs(int argc, char *argv[]);	// Parses the command line parameters
void PrintUsage();	// Prints introduction information of the application