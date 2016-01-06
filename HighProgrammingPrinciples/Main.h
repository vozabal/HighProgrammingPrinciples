#pragma once

#include <iostream>
#include "MPIManager.h"
#include <mpi.h>

using namespace std;

void PrintUsage();
bool ParseArgs(int argc, char *argv[]);