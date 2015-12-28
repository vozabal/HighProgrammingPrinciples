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
	double actual_fitness;
	int regenerate_count = 10000;
	int generated_tries = 0;
		
		for each (Segment* seg in segments) //segmenty
		{
			coefficients = randVectGener.GenarateMatrix();
			fitnesses.clear();

			for each (vector<double> coeff in coefficients)
			{				
				actual_fitness = fitness.GetFitness(seg, coeff);
				while (actual_fitness == DBL_MAX && generated_tries < regenerate_count)
				{
					coeff = randVectGener.GenerateVector();
					actual_fitness = fitness.GetFitness(seg, coeff);
					generated_tries++;
				}
				fitnesses.push_back(actual_fitness);// leze tam minus 
			}						

			for (size_t i = 0; i < ITERATION_NUMBER; i++)
			{			
				// Relfection
				GetComparismIndexes(fitnesses);
				xg = GetCentroid(MAX_FITNESS_INDEX);
				xr = GetReflection(xg, MAX_FITNESS_INDEX);// pada

				xr_fitness = fitness.GetFitness(seg, xr);

				if (fitnesses[MIN_FITNESS_INDEX] < xr_fitness && xr_fitness < fitnesses[MAX2_FITNESS_INDEX])
				{
					coefficients[MAX2_FITNESS_INDEX].swap(xr);
					fitnesses[MAX2_FITNESS_INDEX] = xr_fitness;					
				}
				else
				{
					if (fitnesses[MIN_FITNESS_INDEX] < xr_fitness)
					{
						// Contraction
						xc = GetContraction(xg, MAX2_FITNESS_INDEX);
						xc_fitness = fitness.GetFitness(seg, xc);

						if (xc_fitness < fitnesses[MAX_FITNESS_INDEX])
						{
							coefficients[MAX_FITNESS_INDEX].swap(xc);
							fitnesses[MAX_FITNESS_INDEX] = xc_fitness;
							
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
							// Update fitnesses
							fitnesses.clear();
							for each (vector<double> coeff in coefficients)
							{
								actual_fitness = fitness.GetFitness(seg, coeff);
								fitnesses.push_back(actual_fitness);
							}
						}
					}
					else
					{
						// Expansion
						xe = GetExpansion(xg, xr);
						xe_fitness = fitness.GetFitness(seg, xe);

						if (xe_fitness < xr_fitness)
						{
							coefficients[MAX_FITNESS_INDEX].swap(xe);
							fitnesses[MAX_FITNESS_INDEX] = xe_fitness;
							
						}
						else
						{
							coefficients[MAX_FITNESS_INDEX].swap(xr);
							fitnesses[MAX_FITNESS_INDEX] = xr_fitness;
						}
					}
				}
			}
			//moznost vylepsit - pocitani koeficientu pouze pro jeden vektor a pak prohodit (vlozit na prislusne misto v stromu rozhodovani)
			
			//pocitani fitness
			fitnesses.clear();
			for each (vector<double> coeff in coefficients)
			{
				actual_fitness = fitness.GetFitness(seg, coeff);
				fitnesses.push_back(actual_fitness);// leze tam minus 
				actual_fitness = fitness.GetFitness(seg, coeff);
				cout << actual_fitness << endl;

			}
		
			if (seg->segmentNumber == 2)
			{
				double cus;
				cus = 2;
			}
			if (seg->segmentNumber == 24)
			{
				double cus;
				cus = 2;
			}
			if (seg->segmentNumber == 25)
			{
				double cus;
				cus = 2;
			}

			//22
  			db.PushCoefficients(coefficients[MIN_FITNESS_INDEX], seg->segmentNumber);
			cout << "Segment counted = " << seg->segmentNumber << endl;
		}
}//	
//zkontrolovat


// Vytvori xg, ze vsech vektoru, krome vektoru s maximalni fitness.
vector<double> Simplex::GetCentroid(int max_position)
{
	// Inicializace centroidu
	vector<double> xg = { 0, 0, 0, 0, 0, 0 };

	// Scitani vektoru (krome vektoru n+1)
	for (size_t i = 0; i < coefficients.size(); i++)
	{
		if (i != max_position)
		{
			for (size_t j = 0; j < xg.size(); j++)
			{
				xg[j] += coefficients[i][j];
			}
		}
	}
	// Deleni poctem scitanych vektoru
	for each (double item in xg)
	{
		item /= coefficients.size() - 1;
	}
	return xg;
}

vector<double> Simplex::GetExpansion(vector<double> xg, vector<double> xr)
{
	vector<double> xe = { 0, 0, 0, 0, 0, 0 };

	for (size_t j = 0; j < xg.size(); j++)
	{
		xe[j] = B * (xr[j] - xg[j]) + xr[j];
	}
	return xe;
}

vector<double> Simplex::GetContraction(vector<double> xg, int max_position)
{
	vector<double> xc = { 0, 0, 0, 0, 0, 0 };

	for (size_t j = 0; j < xg.size(); j++)
	{
		xc[j] = G * (coefficients[max_position][j] - xg[j]) + xg[j];
	}
	return xc;
}


vector<double> Simplex::GetReflection(vector<double> xg, int max_position)
{
	vector<double> xr = { 0, 0, 0, 0, 0, 0 };

	for (size_t j = 0; j < xg.size(); j++)
	{
		xr[j] = A * (xg[j] - coefficients[max_position][j]) + xg[j];
	}
	return xr;
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