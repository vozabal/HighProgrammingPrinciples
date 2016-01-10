/*
============================================================================
Name        : Database.h
Author      : Miroslav Vozabal
Description : Provides the computation of Simplex Optimization Algorithm (Nelder and Mead). The entry data are segments and boundaries for the generation of coefficients.
============================================================================
*/
#pragma once

#include "tbb/tbb.h"
#include <vector>
#include "Fitness.h"
#include "Segment.h"
#include "RandomVectorGenerator.h"
#include "Difuse2Param.h"
#include <tbb/mutex.h>

using namespace std;

class Simplex
{
public:
	Simplex(vector<Segment*> segments, RandomVectorGenerator *randomVectGener);	// Passes the segments and the boundaries for generated coefficients of the algormithm
	~Simplex();
	vector<Difuse2Param*> Compute();
	Difuse2Param* ComputeSegment(unsigned int segment_index);	// Computes the algorithm for one segment
private:

	//addded 
	vector<double> fitnesses;	// Vector of fitnesses
	vector<double> xg, xr, xc, xe, xk;	// Centroid, reflection, contraction, expansion and dimensional contraction
	double xr_fitness, xc_fitness, xe_fitness;	// Relfection, expansion and dimensional contraction fitnesses
	double actual_fitness;	// Just generated fitness
	unsigned int generated_tries_counter = 0;	//A Counter of attempts to generate a vector of coefficients with a countable fitness
	vector<double> stop_actual_centroid;	// Centroid for the actual iteration to compare with the previous one
	vector<double> stop_previous_centroid;	// Centroid for the previous iteration to compare with the actual one
	Difuse2Param *difuse2param;	// Output of one computed segment by the algorithm

	//addded 

	const double A = 1.0, B = 1.0, G = 0.5, H = 0.5;	// Constants for the operations of the algorithm
	const unsigned int ITERATION_NUMBER = 10000;	// The maximum algorithm iterations count
	const unsigned int GENERATION_VECTOR_COUNT = 1000; // Start generation attempts of coefficients which don't have a valid fitness.

	// Indexes of compared coefficients
	unsigned int MAX_FITNESS_INDEX;
	unsigned int MAX2_FITNESS_INDEX;
	unsigned int MIN_FITNESS_INDEX;

	RandomVectorGenerator *randVectGener;
	vector<vector<double>> coefficients;
	vector<Segment*> segments;
	Fitness fitness;
	vector<Difuse2Param*> difuse2params;

	// Vectors for the operations
	vector<double> relfection;
	vector<double> centroid;

	// The operations which return results in vectors
	vector<double> GetCentroid(unsigned int max_position);
	vector<double> GetReflection(vector<double> xg, int max_position);
	vector<double> GetContraction(vector<double> xg, int max_position);
	vector<double> GetExpansion(vector<double> xg, vector<double> xr);

	void GetComparismIndexes(vector<double> fitnesses);	// Founds the max, max2 and min fitness indexes int a vector of fitnesses	
	bool ValidFitnessesCount(vector<double> fitnesses);	// Checks if there are at least 2 values in the vector of fitnesses	
	vector<double> GetAllPointsCentroid();	// Counts and returns the centroid of every coefficients vectors - THE ALGORITHM EXIT CRITERIA 	
	Parameters boundaries;
};