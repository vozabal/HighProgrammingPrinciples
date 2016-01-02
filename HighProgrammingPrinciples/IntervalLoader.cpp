#include "IntervalLoader.h"

IntervalLoader::IntervalLoader(string file)
{
	this->file = file;
}


IntervalLoader::~IntervalLoader()
{

}

Parameters IntervalLoader::LoadValues()
{
	FILE *fr;
	char buffer[20];

	fr = fopen(file.c_str(), "r");
	while (fgets(buffer, sizeof(buffer), fr) != NULL) {
		fputs(buffer, stdout);
		AssignValues(buffer);
	}
	fclose(fr);
	return parameters;
}
void IntervalLoader::AssignValues(string entry)
{
	string result;
	size_t found_position;

	found_position = entry.find(P_MIN);
	if (found_position != -1)
	{
		result = entry.substr(P_MIN.length(), entry.length());
		parameters.p_min = atof(result.c_str());
	}

	found_position = entry.find(P_MAX);
	if (found_position != -1)
	{
		result = entry.substr(P_MAX.length(), entry.length());
		parameters.p_max = atof(result.c_str());
	}

	found_position = entry.find(CG_MIN);
	if (found_position != -1)
	{
		result = entry.substr(CG_MIN.length(), entry.length());
		parameters.cg_min = atof(result.c_str());
	}

	found_position = entry.find(CG_MAX);
	if (found_position != -1)
	{
		result = entry.substr(CG_MAX.length(), entry.length());
		parameters.cg_max = atof(result.c_str());
	}

	found_position = entry.find(C_MIN);
	if (found_position != -1)
	{
		result = entry.substr(C_MIN.length(), entry.length());
		parameters.c_min = atof(result.c_str());
	}

	found_position = entry.find(C_MAX);
	if (found_position != -1)
	{
		result = entry.substr(C_MAX.length(), entry.length());
		parameters.c_max = atof(result.c_str());
	}

	found_position = entry.find(DT_MIN);
	if (found_position != -1)
	{
		result = entry.substr(DT_MIN.length(), entry.length());
		parameters.dt_min = atof(result.c_str());
	}

	found_position = entry.find(DT_MAX);
	if (found_position != -1)
	{
		result = entry.substr(DT_MAX.length(), entry.length());
		parameters.dt_max = atof(result.c_str());
	}

	found_position = entry.find(H_MIN);
	if (found_position != -1)
	{
		result = entry.substr(H_MIN.length(), entry.length());
		parameters.h_min = atof(result.c_str());
	}

	found_position = entry.find(H_MAX);
	if (found_position != -1)
	{
		result = entry.substr(H_MAX.length(), entry.length());
		parameters.h_max = atof(result.c_str());
	}

	found_position = entry.find(K_MIN);
	if (found_position != -1)
	{
		result = entry.substr(K_MIN.length(), entry.length());
		parameters.k_min = atof(result.c_str());
	}

	found_position = entry.find(K_MAX);
	if (found_position != -1)
	{
		result = entry.substr(K_MAX.length(), entry.length());
		parameters.k_max = atof(result.c_str());
	}
}