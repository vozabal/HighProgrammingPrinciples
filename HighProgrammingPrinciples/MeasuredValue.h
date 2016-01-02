/*
============================================================================
Name        : MeasuredValue.h
Author      : Miroslav Vozabal
Description : Represents a row of measuredvalue from the database.
============================================================================
*/

#pragma once
#include <string>

using namespace std;

class MeasuredValue
{
public:
	MeasuredValue();
	~MeasuredValue();

	int id;
	double measuredate;
	double blood;
	double ist;
};

