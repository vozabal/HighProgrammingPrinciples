#include "Simplex.h"

Simplex::Simplex()
{
	segments = db.GetSegments();
}

Simplex::~Simplex()
{
}

void Simplex::Compute()
{
	vector<double> fitnesses;
	vector<double> xg, xr, xc, xe, xk;
	double xg_fitness, xr_fitness, xc_fitness, xe_fitness;
		
		for each (Segment* seg in segments) //segmenty
		{
			coefficients = randVectGener.GenarateMatrix();

			for each (vector<double> coeff in coefficients)
			{
				fitnesses.push_back(fitness.GetFitness(seg, coeff));
			}						

			for (size_t i = 0; i < ITERATION_NUMBER; i++)
			{			
				// Relfection
				GetComparismIndexes(fitnesses);
				GetCentroid(&xg, MAX_FITNESS_INDEX);
				GetReflection(xr, xg, MAX_FITNESS_INDEX);

				xr_fitness = fitness.GetFitness(seg, xr);

				if (fitnesses[MIN_FITNESS_INDEX] < xr_fitness && xr_fitness < fitnesses[MAX2_FITNESS_INDEX])
				{
					coefficients[MAX2_FITNESS_INDEX].swap(xr);
				}
				else
				{//
					if (fitnesses[MIN_FITNESS_INDEX] < xr_fitness)
					{
						// Contraction
						GetContraction(xc, xg, MAX2_FITNESS_INDEX);
						xc_fitness = fitness.GetFitness(seg, xc);

						if (xc_fitness < fitnesses[MAX_FITNESS_INDEX])
						{
							coefficients[MAX_FITNESS_INDEX].swap(xc);
						}
						else
						{
							//Contraction allong all dimensions toward X[1]
							for (size_t i = 0; i < coefficients.size(); i++)
							{
								if (i != MIN_FITNESS_INDEX)
								{
									for (size_t j = 0; j < coefficients[i].size(); j++)
									{
										coefficients[i][j] = H * (coefficients[i][j] - coefficients[MIN_FITNESS_INDEX][j]) + coefficients[MIN_FITNESS_INDEX][j];
									}
								}
							}
						}
					}
					else
					{
						// Expansion
						GetExpansion(xe, xg, xr);
						xe_fitness = fitness.GetFitness(seg, xe);

						if (xe_fitness < xr_fitness)
						{
							coefficients[MAX_FITNESS_INDEX].swap(xe);
						}
						else
						{
							coefficients[MAX_FITNESS_INDEX].swap(xr);
						}
					}
				}
			}
		}
}//	
//zkontrolovat


// Vytvori xg, ze vsech vektoru, krome vektoru s maximalni fitness.
void Simplex::GetCentroid(vector<double> *xg, int max_position)
{
	// Inicializace centroidu
	*xg = { 0, 0, 0, 0, 0, 0 };

	// Scitani vektoru (krome vektoru n+1)
	for (size_t i = 0; i < coefficients.size(); i++)
	{
		if (i != max_position)
		{
			for (size_t j = 0; j < (*xg).size(); j++)
			{
				(*xg)[j] += coefficients[i][j];
			}
		}
	}
	// Deleni poctem scitanych vektoru
	for each (double item in *xg)
	{
		item /= coefficients.size() - 1;
	}
}

void Simplex::GetExpansion(vector<double> xe, vector<double> xg, vector<double> xr)
{

	for (size_t j = 0; j < xg.size(); j++)
	{
		xe[j] = B * (xr[j] - xg[j]) + xr[j];
	}
}

void Simplex::GetContraction(vector<double> xc, vector<double> xg, int max_position)
{

	for (size_t j = 0; j < xg.size(); j++)
	{
		xc[j] = G * (coefficients[max_position][j] - xg[j]) + xg[j];
	}
}


void Simplex::GetReflection(vector<double> xr, vector<double> xg, int max_position)
{
	
	for (size_t j = 0; j < xg.size(); j++)
	{
		xr[j] = A * (xg[j] - coefficients[max_position][j]) + xg[j];
	}
}

void Simplex::GetComparismIndexes(vector<double> fitnesses)
{
	int min = 0, max2 = 0, max = 0; // min, second min, max of fitnesses.

	for (int i = 0; i < fitnesses.size(); ++i){
		if (fitnesses[i]<fitnesses[min]){
			min = i;
		}
		if (fitnesses[i]>fitnesses[max]){
			max = i;
		}
	}
		
	for (int i = 0; i < fitnesses.size(); ++i){
		if (fitnesses[i]>fitnesses[max] && i != max){
			max2 = i;
		}
	}
	MIN_FITNESS_INDEX = min;
	MAX2_FITNESS_INDEX= max2;
	MAX_FITNESS_INDEX = max;
}