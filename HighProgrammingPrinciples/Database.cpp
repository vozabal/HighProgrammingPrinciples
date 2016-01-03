
#include "Database.h"

Database::Database(string file)
{
	this->file = file;
}

Database::~Database()
{

}

void Database::PushResults(vector<Difuse2Param*> difuse2Params)
{
	Open_database();

	for (size_t i = 0; i < difuse2Params.size(); i++)
	{
		PushCoefficients(difuse2Params[i]->coefficients, difuse2Params[i]->segment_id);
	}

	Close_database();
}

void Database::PushCoefficients(vector<double> coefficients, int segment_id)
{
	stmt = NULL;

	query = "INSERT INTO difuse2params (p, cg, c, dt, h, k, s, segmentid) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
	sqlite3_prepare_v2(db, query, -1, &stmt, 0);

	sqlite3_bind_double(stmt, 1, coefficients[0]);
	sqlite3_bind_double(stmt, 2, coefficients[1]);
	sqlite3_bind_double(stmt, 3, coefficients[2]);
	sqlite3_bind_double(stmt, 4, coefficients[3]);
	sqlite3_bind_double(stmt, 5, coefficients[4]);
	sqlite3_bind_double(stmt, 6, coefficients[5]);
	sqlite3_bind_double(stmt, 7, 1);
	sqlite3_bind_double(stmt, 8, segment_id);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

vector<Segment*> Database::GetSegments()
{
	//Positions of the values of the row
	const int id_position = 0;
	const int measuredat_position = 1;
	const int blood_position = 2;
	const int ist_position = 3;
	const int segment_position = 4;

	//Represents values of the row
	int actual_id = 0;
	double actual_measuredat = 0;
	double actual_blood = 0;
	double actual_ist = 0;
	double actual_segment_number_number = 0;
	double new_segment_number = 0;

	vector<Segment*> segments;

	Open_database();
	query = "SELECT id, julianday(measuredat)-julianday('1900-01-01'), blood, ist, segmentid FROM measuredvalue";
	sqlite3_prepare_v2(db, query, -1, &stmt, &pzTail);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		actual_blood = sqlite3_column_double(stmt, blood_position);

		MeasuredValue *p_measuredValue = new MeasuredValue();

		actual_id = sqlite3_column_int(stmt, id_position);
		actual_ist = sqlite3_column_double(stmt, ist_position);
		actual_measuredat = sqlite3_column_double(stmt, measuredat_position);
		new_segment_number = sqlite3_column_double(stmt, segment_position);

		p_measuredValue->id = actual_id;
		p_measuredValue->ist = actual_ist;
		p_measuredValue->blood = actual_blood;
		p_measuredValue->measuredate = actual_measuredat;

		if (segments.size() == 0)
		{
			segments.push_back(new Segment(new_segment_number));
			segments.back()->measuredValues.push_back(p_measuredValue);
			actual_segment_number_number = new_segment_number;
		}
		else
		{
			if (actual_segment_number_number == new_segment_number)
			{
				segments.back()->measuredValues.push_back(p_measuredValue);
			}
			else {
				Segment *p_segment = new Segment(new_segment_number);
				segments.push_back(p_segment);
				segments.back()->measuredValues.push_back(p_measuredValue);
				actual_segment_number_number = sqlite3_column_double(stmt, segment_position);
			}
		}
	}
	sqlite3_finalize(stmt);
	Close_database();

	return segments;
}


void Database::Open_database()
{
	int rc;
	rc = sqlite3_open(file.c_str(), &db);
	if (rc != SQLITE_OK)
	{
		cerr << "Error opening SQLite3 database! Check the path of the database" << sqlite3_errmsg(db) << endl;
	}
}

void Database::Close_database()
{
	sqlite3_close(db);
}