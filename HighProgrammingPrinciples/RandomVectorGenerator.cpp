//Vygeneruje nahodne hodnoty kazdemu z vektoru na zaklade intervalu, ktere jsou poskytnuty tridou IntervalLoader.

#include "RandomVectorGenerator.h"


RandomVectorGenerator::RandomVectorGenerator()
{
	
}

RandomVectorGenerator::~RandomVectorGenerator()
{

}

void RandomVectorGenerator::Initializate(Parameters boundaries)
{
	this->boundaries = boundaries;
}

vector<vector<double>> RandomVectorGenerator::GenarateMatrix()
{
	vector<vector<double>> matrix(COLUMNS, vector<double>(ROWS));

	for (int i = 0; i < COLUMNS; i++)
	{
		matrix[i][0] = FRand(boundaries.p_min, boundaries.p_max);
		matrix[i][1] = FRand(boundaries.cg_min, boundaries.cg_max);
		matrix[i][2] = FRand(boundaries.c_min, boundaries.c_max);;
		matrix[i][3] = FRand(boundaries.dt_min, boundaries.dt_max);;
		matrix[i][4] = FRand(boundaries.h_min, boundaries.h_max);;
		matrix[i][5] = FRand(boundaries.k_min, boundaries.k_max);;
	}
	return matrix;
}

		//TODO: zjisti seed
double RandomVectorGenerator::FRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

vector<double> RandomVectorGenerator::GenerateVector()
{
	vector<double> vect(ROWS);

	for (int i = 0; i < ROWS; i++)
	{
		vect[i] = FRand(boundaries.p_min, boundaries.p_max);
		vect[i] = FRand(boundaries.cg_min, boundaries.cg_max);
		vect[i] = FRand(boundaries.c_min, boundaries.c_max);;
		vect[i] = FRand(boundaries.dt_min, boundaries.dt_max);;
		vect[i] = FRand(boundaries.h_min, boundaries.h_max);;
		vect[i] = FRand(boundaries.k_min, boundaries.k_max);;
	}
	return vect;
}


/*
vector<vector<double>> genarateMatrix(int rows, int columns)
{
vector<vector<double> > matrix(rows, vector<double>(columns));

for (int i = 0; i < rows; i++)
{
for (int j = 0; j < columns; j++)
{
matrix[i][j] = j;
}
}
return matrix;
}
*/