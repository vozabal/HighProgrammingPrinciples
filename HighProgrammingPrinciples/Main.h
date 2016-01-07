/*
============================================================================
Name        : Main.h
Author      : Miroslav Vozabal
Description : Represent the entry point of the application. Manages the validation of the command line parameters
============================================================================
*/

#pragma once

#include <iostream>
#include "Manager.h"

using namespace std;

void PrintUsage();	// Prints introduction information of the application to the console
bool ParseArgs(int argc, char *argv[]);	// Parses the command line arguments