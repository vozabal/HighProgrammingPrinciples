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
	for (size_t k = 0; k < segments.size(); k++) // Segments
	{
	difuse2params.push_back(ComputeSegment(k));;
	}
	

		//difuse2params.push_back(ComputeSegment(0));;

	return difuse2params;
}

Difuse2Param* Simplex::ComputeSegment(unsigned int segment_index)
{
	// Difference between two consecutive centroids.
	// Epsilon for termination condition.
	const double EPSILON = epsilon_mul * std::numeric_limits<double>::epsilon();

	double centroid_diff = 0; //TODO

	fitnesses.clear();	// Initialization of the fitnesses values		
	coefficients = randVectGener.GenarateMatrix();	// Generation of all coefficients vectors

	for (size_t i = 0; i < coefficients.size(); i++) // Iterrations 
	{
		actual_fitness = fitness.GetFitness(segments[segment_index], coefficients[i]);	// Computation of the fitness for the vector of coefficient

		// Generates new coefficients until the fitness is generated
		while (actual_fitness == DBL_MAX && generated_tries_counter < GENERATION_VECTOR_COUNT)
		{
			coefficients[i] = randVectGener.GenerateVector();
			actual_fitness = fitness.GetFitness(segments[segment_index], coefficients[i]);
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
		if (i > 0)
		{
			centroid_diff = GetCentroidDifference(stop_actual_centroid, stop_previous_centroid);
		}
		else
		{
			centroid_diff = EPSILON;
		}
		//centroid_diff = (stop_actual_centroid - stop_previous_centroid).abs_sum() / 6;
		if (centroid_diff < EPSILON) {
		//	break;	// It's stopped when the centroid of all vectors is not changing.
		}
		if (ValidFitnessesCount(fitnesses) != true)	break;	// It's stopped when the fitnesses have just one valid fitness.

		//	Relfection				
		xg = GetCentroid(MAX_FITNESS_INDEX);
		xr = GetReflection(xg, MAX_FITNESS_INDEX);

		xr_fitness = fitness.GetFitness(segments[segment_index], xr);

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
				xc_fitness = fitness.GetFitness(segments[segment_index], xc);

				if (xc_fitness < fitnesses[MAX_FITNESS_INDEX])
				{
					coefficients[MAX_FITNESS_INDEX].swap(xc);
					fitnesses[MAX_FITNESS_INDEX] = xc_fitness;
					GetComparismIndexes(fitnesses);
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
							randVectGener.WatchBoundaries(&coefficients[i]);
						}
					}
					// Update fitnesses
					fitnesses.clear();
					for (size_t i = 0; i < coefficients.size(); i++)
					{
						actual_fitness = fitness.GetFitness(segments[segment_index], coefficients[i]);
						fitnesses.push_back(actual_fitness);
					}
					GetComparismIndexes(fitnesses);
				}
			}
			else
			{
				// Expansion
				xe = GetExpansion(xg, xr);
				xe_fitness = fitness.GetFitness(segments[segment_index], xe);

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
	difuse2param = new Difuse2Param();
	difuse2param->coefficients = coefficients[MIN_FITNESS_INDEX];
	difuse2param->segment_id = segments[segment_index]->segmentNumber;
	difuse2param->fitness = fitnesses[MIN_FITNESS_INDEX];


	return difuse2param;
}



bool Simplex::ValidFitnessesCount(vector<double> fitnesses)
{
	bool valid_count = true;
	unsigned int count = 0;

	for (size_t i = 0; i < fitnesses.size(); i++)
	{
		if (fitnesses[i] == DBL_MAX)
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


vector<double> Simplex::GetCentroid(unsigned int max_position)
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

double Simplex::GetCentroidDifference(vector<double> centroid1, vector<double> centroid2)
{
	double difference = 0;
	for (size_t i = 0; i < centroid1.size(); i++)
	{
		difference += std::abs(centroid1[i] - centroid2[i]);
	}
	difference /= centroid1.size();

	return difference;
}

vector<double> Simplex::GetAllPointsCentroid()
{
	// Initialization of the centroid
	vector<double> xg = { 0, 0, 0, 0, 0, 0 };

	// Summation of the vectors apart from vector(n+1)
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
	randVectGener.WatchBoundaries(&xe);
	return xe;
}

vector<double> Simplex::GetContraction(vector<double> xg, int max_position)
{
	vector<double> xc = { 0, 0, 0, 0, 0, 0 };

	for (size_t j = 0; j < xg.size(); j++)
	{
		xc[j] = G * (coefficients[max_position][j] - xg[j]) + xg[j];
	}
	randVectGener.WatchBoundaries(&xc);
	return xc;
}


vector<double> Simplex::GetReflection(vector<double> xg, int max_position)
{
	vector<double> xr = { 0, 0, 0, 0, 0, 0 };

	for (size_t j = 0; j < xg.size(); j++)
	{
		xr[j] = A * (xg[j] - coefficients[max_position][j]) + xg[j];
	}
	randVectGener.WatchBoundaries(&xr);

	return xr;
}

void Simplex::GetComparismIndexes(vector<double> fitnesses)
{
	unsigned int min = 0, max2 = 0, max = 0; // min, second min, max of fitnesses.

	for (size_t i = 0; i < fitnesses.size(); ++i){
		if (fitnesses[i]<fitnesses[min]){
			min = i;
		}
		if (fitnesses[i]>fitnesses[max]){
			max = i;
		}
	}

	for (size_t i = 0; i < fitnesses.size(); ++i){
		if (fitnesses[i]>fitnesses[max] && i != max){
			max2 = i;
		}
	}
	MIN_FITNESS_INDEX = min;
	MAX2_FITNESS_INDEX = max2;
	MAX_FITNESS_INDEX = max;
}