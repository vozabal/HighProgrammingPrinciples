#include "Simplex.h"

Simplex::Simplex(vector<Segment*> segments, Parameters boundaries)
{
	this->randVectGener.Initializate(boundaries);
	this->segments = segments;
}

Simplex::~Simplex()
{
}

vector<Difuse2Param*> Simplex::Compute()
{
	vector<double> fitnesses;	// Vector of fitnesses
	vector<double> xg, xr, xc, xe, xk;	// Centroid, reflection, contraction, expansion and dimensional contraction
	double xg_fitness, xr_fitness, xc_fitness, xe_fitness;	// Centroid, relfection, expansion and dimensional contraction fitnesses
	double actual_fitness;	// Just generated fitness
	int generated_tries_counter = 0;	//A Counter of attempts to generate a vector of coefficients with a countable fitness
	vector<double> stop_actual_centroid;	// Centroid for the actual iteration to compare with the previous one
	vector<double> stop_previous_centroid;	// Centroid for the previous iteration to compare with the actual one
	Difuse2Param *difuse2param;	// Output of one computed segment by the algorithm
	

	for each (Segment* seg in segments) // Segments
	{
		fitnesses.clear();	// Initialization of the fitnesses values
		
		coefficients = randVectGener.GenarateMatrix();	// Generation of all coefficients vectors

		for (size_t i = 0; i < coefficients.size(); i++) // Iterrations 
		{
			actual_fitness = fitness.GetFitness(seg, coefficients[i]);	// Computation of the fitness for the vector of coefficient

			// Generates new coefficients until the fitness is generated
			while (actual_fitness == DBL_MAX && generated_tries_counter < GENERATION_VECTOR_COUNT) 
			{
				coefficients[i] = randVectGener.GenerateVector();
				actual_fitness = fitness.GetFitness(seg, coefficients[i]);
				generated_tries_counter++;
			}
			generated_tries_counter = 0;
			fitnesses.push_back(actual_fitness);
		}
		GetComparismIndexes(fitnesses);	// Compares the particular vectors of the coefficients

		for (size_t i = 0; i < ITERATION_NUMBER; i++)
		{
			//	Stop conditions
			stop_actual_centroid = GetAllPointsCentroid();
			if (stop_actual_centroid == stop_previous_centroid) break;	// It's stopped when the centroid of all vectors is not changing.
			if (ValidFitnessesCount(fitnesses) != true)	break;	// It's stopped when the fitnesses have just one valid fitness.

			//	Relfection				
			xg = GetCentroid(MAX_FITNESS_INDEX);
			xr = GetReflection(xg, MAX_FITNESS_INDEX);

			xr_fitness = fitness.GetFitness(seg, xr);

			if (fitnesses[MIN_FITNESS_INDEX] < xr_fitness && xr_fitness < fitnesses[MAX2_FITNESS_INDEX])
			{
				coefficients[MAX_FITNESS_INDEX].swap(xr);
				fitnesses[MAX_FITNESS_INDEX] = xr_fitness;
				GetComparismIndexes(fitnesses);
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
						GetComparismIndexes(fitnesses);
					}
					else
					{
						if (seg->segmentNumber == 25) {
							double d = 0;
							d++;
						}
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
						GetComparismIndexes(fitnesses);
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
						GetComparismIndexes(fitnesses);

					}
					else
					{
						coefficients[MAX_FITNESS_INDEX].swap(xr);
						fitnesses[MAX_FITNESS_INDEX] = xr_fitness;
						GetComparismIndexes(fitnesses);
					}
				}
			}
			stop_previous_centroid = stop_actual_centroid;
		}
		cout << fitnesses[MIN_FITNESS_INDEX] << endl;
		//db.PushCoefficients(coefficients[MIN_FITNESS_INDEX], seg->segmentNumber);

		difuse2param = new Difuse2Param(); // vycistit pamet
		difuse2param->coefficients = coefficients[MIN_FITNESS_INDEX];
		difuse2param->segment_id = seg->segmentNumber;
		difuse2params.push_back(difuse2param);

		cout << "Segment counted = " << seg->segmentNumber << endl;
	}
	return difuse2params;
}

bool Simplex::ValidFitnessesCount(vector<double> fitnesses)
{
	bool valid_count = true;
	int count = 0;

	for each (double item in fitnesses)
	{
		if (item == DBL_MAX)
		{
			count++;
		}
	}
	if (count == fitnesses.size() - 1)
	{
		valid_count = false;
	}

	return valid_count;
}

// Creates xg from all the vectors apart from the one of the max fitness.
vector<double> Simplex::GetCentroid(int max_position)
{
	// Inicialization of the centroid
	vector<double> xg = { 0, 0, 0, 0, 0, 0 };

	// Summation of the vectors
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
	for (size_t i = 0; i < xg.size(); i++)
	{
		xg[i] /= coefficients.size() - 1; // n = coeff size -1
	}

	return xg;
}


vector<double> Simplex::GetAllPointsCentroid()
{
	// Inicializace centroidu
	vector<double> xg = { 0, 0, 0, 0, 0, 0 };

	// Scitani vektoru (krome vektoru n+1)
	for (size_t i = 0; i < coefficients.size(); i++)
	{
		{
			for (size_t j = 0; j < xg.size(); j++)
			{
				xg[j] += coefficients[i][j];
			}
		}
	}
	for (size_t i = 0; i < xg.size(); i++)
	{
		xg[i] /= coefficients.size(); // n= coeff size -1
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
	MAX2_FITNESS_INDEX = max2;
	MAX_FITNESS_INDEX = max;
}