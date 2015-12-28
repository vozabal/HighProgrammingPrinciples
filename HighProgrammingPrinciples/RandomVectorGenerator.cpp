//Vygeneruje nahodne hodnoty kazdemu z vektoru na zaklade intervalu, ktere jsou poskytnuty tridou IntervalLoader.

#include "RandomVectorGenerator.h"


RandomVectorGenerator::RandomVectorGenerator()
{

}

RandomVectorGenerator::~RandomVectorGenerator()
{

}


vector<vector<double>> RandomVectorGenerator::GenarateMatrix()
{
	vector<vector<double>> matrix(COLUMNS, vector<double>(ROWS));

	for (int i = 0; i < COLUMNS; i++)
	{
		matrix[i][0] = FRand(intervalLoader.parameters.p_min, intervalLoader.parameters.p_max);
		matrix[i][1] = FRand(intervalLoader.parameters.cg_min, intervalLoader.parameters.cg_max);
		matrix[i][2] = FRand(intervalLoader.parameters.c_min, intervalLoader.parameters.c_max);;
		matrix[i][3] = FRand(intervalLoader.parameters.dt_min, intervalLoader.parameters.dt_max);;
		matrix[i][4] = FRand(intervalLoader.parameters.h_min, intervalLoader.parameters.h_max);;
		matrix[i][5] = FRand(intervalLoader.parameters.k_min, intervalLoader.parameters.k_max);;
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
		vect[i] = FRand(intervalLoader.parameters.p_min, intervalLoader.parameters.p_max);
		vect[i] = FRand(intervalLoader.parameters.cg_min, intervalLoader.parameters.cg_max);
		vect[i] = FRand(intervalLoader.parameters.c_min, intervalLoader.parameters.c_max);;
		vect[i] = FRand(intervalLoader.parameters.dt_min, intervalLoader.parameters.dt_max);;
		vect[i] = FRand(intervalLoader.parameters.h_min, intervalLoader.parameters.h_max);;
		vect[i] = FRand(intervalLoader.parameters.k_min, intervalLoader.parameters.k_max);;
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