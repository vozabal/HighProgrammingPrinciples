#include <iostream>
#include "Database.h"

	Database::Database()
	{
			
	}

	Database::~Database()
	{

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
		string actual_measuredat = "";
		double actual_blood = 0;
		double actual_ist = 0;
		double actual_segment_number_number = 0;
		double new_segment_number = 0;

		vector<Segment*> segments; //TODO:AFTER - free the memory
			
		Open_database();
		query = "SELECT * FROM measuredvalue";
		sqlite3_prepare_v2(db, query, -1, &result, &pzTail);

		while (sqlite3_step(result) == SQLITE_ROW)
		{
			int segment = 0;
			actual_measuredat = "";

			actual_blood = sqlite3_column_double(result, blood_position);
			if (actual_blood == 0)
			{
				continue;
			}
			MeasuredValue *p_measuredValue = new MeasuredValue(); // TODO: new				

			actual_id = sqlite3_column_int(result, id_position);
			actual_ist = sqlite3_column_double(result, ist_position);
			actual_measuredat.append((char *)sqlite3_column_text(result, measuredat_position));				
			new_segment_number = sqlite3_column_double(result, segment_position);
				
			p_measuredValue->id = actual_id;
			p_measuredValue->ist = actual_ist;
			p_measuredValue->blood = actual_blood;				
			p_measuredValue->measuredate += actual_measuredat;
				

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
					actual_segment_number_number = sqlite3_column_double(result, segment_position);
				}
			}
			
		}
		sqlite3_finalize(result);
		Close_database();

		return segments;
	}


	void Database::Open_database()
	{
		int rc;

		rc = sqlite3_open("Resources\\direcnet.sqlite", &db);
		if (rc)
		{
			cerr << "Error opening SQLite3 database:" << sqlite3_errmsg;
		}
		else
		{
			cout << "The database has been opened succesfully" << endl;
		}
	}

	void Database::Close_database()
	{
		sqlite3_close(db);
		cout << "The database has been closed succesfully" << endl;
	}

	void Database::Get_missing_ist()
	{
		query = "SELECT * FROM subject WHERE id = ?";
		Open_database();
		sqlite3_prepare_v2(db, query, -1, &result, 0);

	}	

	sqlite3_stmt* Database::GetNextResult()
	{
		sqlite3_step(result);
		return result;
	}

	void Database::SetUpStatement()
	{
		query = "SELECT * FROM measuredat";
		sqlite3_prepare_v2(db, query, -1, &result, 0);
		//const int index = sqlite3_bind_parameter_index(result, "id");
		//sqlite3_bind_int(result, index, )
		sqlite3_bind_int(result, 1, 2);

		int step = sqlite3_step(result);

		if (step == SQLITE_ROW)
		{
			cout << "The parameter is " << sqlite3_column_text(result, 1);
		}
		sqlite3_finalize(result);
	}
