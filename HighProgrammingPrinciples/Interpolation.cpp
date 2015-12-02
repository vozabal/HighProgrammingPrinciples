#include <iostream>
#include <sqlite3.h>
#include <QtCore/QCoreApplication>
#include <QDateTime>
#include "Record.cpp"
#include <string>


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
	const int measuredat_position = 1;
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
		double previous_point_measuredat = 0;
		double last_point = 0;
		double last_point_measuredat = 0;
		int actual_id = 0;
		double actual_ist = 0;
		double actual_measuredat = 0;

		int count = 0;
		
		Record *missing_records[50]; //TODO: dodelat konstantu

		while (sqlite3_step(result) == SQLITE_ROW)
		{
			actual_id = sqlite3_column_int(result, id_position);
			actual_ist = sqlite3_column_double(result, ist_position);
			actual_measuredat = sqlite3_column_double(result, measuredat_position);

			if (actual_ist == 0)
			{
				missing_records[not_processed_records_number] = new Record(actual_id, actual_ist, actual_measuredat);
				not_processed_records_number++;
				//destructe the memory
			}
			else
			{
				if (not_processed_records_number != 0)
				{
					last_point = actual_ist;
					last_point_measuredat = actual_measuredat;
					int count = 0;

					while (count < not_processed_records_number)
					{
						//the process of the interpolation
						previous_point = interpolate_point(previous_point, last_point, previous_point_measuredat, last_point_measuredat);
						missing_records[count]->ist = previous_point;
						//delete missing_records[count];
						count++;
					}
					//InsertResultsIntoDatabase(missing_records, not_processed_records_number);
					not_processed_records_number = 0;
					previous_point = actual_ist;
				}
				else
				{
					previous_point = actual_ist;
					previous_point_measuredat = actual_measuredat;
				}
			}
			count++;
		}
		sqlite3_finalize(result);
		cout << count;
	}
	void Push_point_into_database(double point)
	{
		string query = "INSERT into measuredvalue (ist) values (?)";

	}

	double interpolate_point(double first_point, double second_point, double first_point_time, double second_point_time)
	{
		double x = (second_point_time - first_point_time) / 2;
		double result = first_point + (x - first_point_time) * (second_point - first_point) / (second_point_time - first_point_time);


		return result;
	}

	double QDateTime2RatTime(const QDateTime *qdt) {
		const qint64 diffFrom1970To1900 = 2209161600000;
		const double MSecsPerDay = 24.0*60.0*60.0*1000.0;
		const double InvMSecsPerDay = 1.0 / MSecsPerDay;

		qint64 diff = qdt->toMSecsSinceEpoch() + diffFrom1970To1900;
		return ((double)diff)*InvMSecsPerDay;
	}

	double GetTimeFromDB(const QString time)
	{
		QDateTime q_time = QDateTime::fromString(time, Qt::ISODate);
		double d_time = QDateTime2RatTime(&q_time);

		return d_time;
	}
	void InsertResultsToDatabase(Record missing_records[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			missing_records[i];
		}
	}
	void InsertRecordIntoDatabase(Record *record)
	{
		const char *query;       /* SQL statement, UTF-8 encoded */
		int nByte;              /* Maximum length of zSql in bytes. */
		sqlite3_stmt *stmt;  /* OUT: Statement handle */
		const char *pzTail;     /* OUT: Pointer to unused portion of zSql */

		sqlite3_prepare(db, query, -1, &stmt, &pzTail);

		sqlite3_bind_double(stmt, 0, record->ist);
		//sqlite3_bind_text(stmt, 1, record->measuredat); //TODO: pridelat konverzi zpet3
		sqlite3_bind_int(stmt, 1, record->id);


	}
	
};
