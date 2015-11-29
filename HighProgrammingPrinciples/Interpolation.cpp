#include <iostream>
#include <sqlite3.h>
#include "Record.cpp"

using namespace std;
class Interpolation {
	//Prepare statement
	sqlite3 *db;            /* Database handle */
	const char *query;       /* SQL statement, UTF-8 encoded */
	int nByte;              /* Maximum length of zSql in bytes. */
	sqlite3_stmt *result;  /* OUT: Statement handle */
	const char *pzTail;     /* OUT: Pointer to unused portion of zSql */
	const int ist_position = 3;
	const int id_position = 0;
	int Missing_records_length = 50;

public:
	Interpolation()
	{

	}

	void Open_database()
	{
		int rc;

		rc = sqlite3_open("Resources\\direcnet.sqlite", &db);
		if (rc)
		{
			cerr << "Error opening SQLite3 database:" << sqlite3_errmsg << endl;
		}
		else
		{
			cout << "The database has been opened succesfully" << endl;
		}
	}
	void Get_missing_ist()
	{
		query = "SELECT * FROM measuredvalue";
		Open_database();
		sqlite3_prepare_v2(db, query, -1, &result, 0);

	}

	void Close_database()
	{
		sqlite3_close(db);
	}

	void Print_query_results()
	{

	}

	sqlite3_stmt *GetNextResult()
	{
		sqlite3_step(result);
		return result;
	}
	void SetUpStatement()
	{
		query = "SELECT * FROM measuredvalue";
		sqlite3_prepare_v2(db, query, -1, &result, &pzTail);
		
		int not_processed_records_number = 0;
		//bool missing_record = false;
		double previous_point = 0;
		double last_point = 0;
		int actual_id = 0;
		double actual_ist = 0;
		Record *missing_records[50]; //TODO: dodelat konstantu

		while (sqlite3_step(result) == SQLITE_ROW)
		{
			actual_id = sqlite3_column_int(result, id_position);
			actual_ist = sqlite3_column_double(result, ist_position);

			if (actual_ist == 0)
			{
				missing_records[not_processed_records_number] = new Record(actual_id, actual_ist);
				not_processed_records_number++;
				//destructe the memory
			}
			else
			{
				if (not_processed_records_number != 0)
				{
					last_point = actual_ist;
					int count = 0;

					while (count < not_processed_records_number)
					{
						//the process of the interpolation
						previous_point = interpolate_point(previous_point, last_point);
						missing_records[count]->ist = previous_point;
						//delete missing_records[count];
						count++;
					}
					not_processed_records_number = 0;
					previous_point = actual_ist;
				}
				else
				{
					previous_point = actual_ist;
				}
			}
		}
		sqlite3_finalize(result);
	}
	void Push_point_into_database(double point)
	{

	}

	double interpolate_point(double first_point, double second_point)
	{
		double result = 1.0;

		return result;
	}
};
