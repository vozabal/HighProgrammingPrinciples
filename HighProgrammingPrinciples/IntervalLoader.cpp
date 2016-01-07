#include "IntervalLoader.h"

IntervalLoader::IntervalLoader(string file)
{
	this->file = file;
}


IntervalLoader::~IntervalLoader()
{

}

void IntervalLoader::CheckParameters()
{
	if (parameters.p_min == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.p_max == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.cg_min == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.cg_max == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.c_min == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.c_max == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.dt_min == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.dt_max == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.h_min == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.h_max == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.k_min == DBL_MAX) throw runtime_error(ERROR);
	if (parameters.k_max == DBL_MAX) throw runtime_error(ERROR);
}

Parameters IntervalLoader::LoadValues()
{	
	FILE *fr;
	char buffer[20];

	fr = fopen(file.c_str(), "r");
	if (fr == NULL)
	{
		throw std::runtime_error("Error of opening the boundaries file! Check the path of the file [==ERROR==]\n");
	}

	while (fgets(buffer, sizeof(buffer), fr) != NULL) {
		AssignValues(buffer);
	}
	fclose(fr);
	CheckParameters();
	
	return parameters;
}
void IntervalLoader::AssignValues(string entry)
{
	
	string result;
	size_t found_position;	

	try	
	{
		found_position = entry.find(P_MIN);
		if (found_position != string::npos)
		{
			result = entry.substr(P_MIN.length(), entry.length());
			parameters.p_min = stod(result.c_str());
		}

		found_position = entry.find(P_MAX);
		if (found_position != string::npos)
		{
			result = entry.substr(P_MAX.length(), entry.length());
			parameters.p_max = stod(result.c_str());
		}

		found_position = entry.find(CG_MIN);
		if (found_position != string::npos)
		{
			result = entry.substr(CG_MIN.length(), entry.length());
			parameters.cg_min = stod(result.c_str());
		}

		found_position = entry.find(CG_MAX);
		if (found_position != string::npos)
		{
			result = entry.substr(CG_MAX.length(), entry.length());
			parameters.cg_max = stod(result.c_str());
		}

		found_position = entry.find(C_MIN);
		if (found_position != string::npos)
		{
			result = entry.substr(C_MIN.length(), entry.length());
			parameters.c_min = stod(result.c_str());
		}

		found_position = entry.find(C_MAX);
		if (found_position != string::npos)
		{
			result = entry.substr(C_MAX.length(), entry.length());
			parameters.c_max = stod(result.c_str());
		}

		found_position = entry.find(DT_MIN);
		if (found_position != string::npos)
		{
			result = entry.substr(DT_MIN.length(), entry.length());
			parameters.dt_min = stod(result.c_str());
		}

		found_position = entry.find(DT_MAX);
		if (found_position != string::npos)
		{
			result = entry.substr(DT_MAX.length(), entry.length());
			parameters.dt_max = stod(result.c_str());
		}

		found_position = entry.find(H_MIN);
		if (found_position != string::npos)
		{
			result = entry.substr(H_MIN.length(), entry.length());
			parameters.h_min = stod(result.c_str());
		}

		found_position = entry.find(H_MAX);
		if (found_position != string::npos)
		{
			result = entry.substr(H_MAX.length(), entry.length());
			parameters.h_max = stod(result.c_str());
		}

		found_position = entry.find(K_MIN);
		if (found_position != string::npos)
		{
			result = entry.substr(K_MIN.length(), entry.length());
			parameters.k_min = stod(result.c_str());
		}

		found_position = entry.find(K_MAX);
		if (found_position != string::npos)
		{
			result = entry.substr(K_MAX.length(), entry.length());
			parameters.k_max = stod(result.c_str());
		}
	}
	catch (invalid_argument e)
	{
		throw invalid_argument(ERROR);
	}
}