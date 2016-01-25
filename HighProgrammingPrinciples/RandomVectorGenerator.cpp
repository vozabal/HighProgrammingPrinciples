#include "RandomVectorGenerator.h"


RandomVectorGenerator::RandomVectorGenerator()
{
	srand(SEED);
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

double RandomVectorGenerator::FRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

vector<double> RandomVectorGenerator::GenerateVector()
{
	vector<double> vect(ROWS);


	vect[0] = FRand(boundaries.p_min, boundaries.p_max);
	vect[1] = FRand(boundaries.cg_min, boundaries.cg_max);
	vect[2] = FRand(boundaries.c_min, boundaries.c_max);;
	vect[3] = FRand(boundaries.dt_min, boundaries.dt_max);;
	vect[4] = FRand(boundaries.h_min, boundaries.h_max);;
	vect[5] = FRand(boundaries.k_min, boundaries.k_max);;

	return vect;
}