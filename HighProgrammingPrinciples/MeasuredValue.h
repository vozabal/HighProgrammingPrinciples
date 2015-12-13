#pragma once
#include <string>

using namespace std;

class MeasuredValue
{
public:
	MeasuredValue();
	~MeasuredValue();

	int id;
	string measuredate;
	double blood;
	double ist;

private:
	
};

