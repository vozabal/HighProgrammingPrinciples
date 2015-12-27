
#include "Database.h"

	Database::Database()
	{
			
	}

	Database::~Database()
	{

	}

	void Database::PushCoefficients(vector<double> coefficients, int segment_id)
	{
		stmt = NULL;
		Open_database();		
		query = "INSERT INTO difuse2params (p, cg, c, dt, h, k, s, segmentid) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
		sqlite3_prepare_v2(db, query, -1, &stmt, 0);

		//if (sqlite3_bind_double(stmt, 0, 1.0) != SQLITE_OK) cout << "nejdes";   DEMENCE indexovani parametru od 1
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
		Close_database();
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
		sqlite3_prepare_v2(db, query, -1, &stmt, &pzTail);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int segment = 0;
			actual_measuredat = "";

			actual_blood = sqlite3_column_double(stmt, blood_position);
			/*if (actual_blood == 0)
			{
				continue; //chyba nenacita neistovy
			}
			*/
			MeasuredValue *p_measuredValue = new MeasuredValue(); // TODO: new				

			actual_id = sqlite3_column_int(stmt, id_position);
			actual_ist = sqlite3_column_double(stmt, ist_position);
			actual_measuredat.append((char *)sqlite3_column_text(stmt, measuredat_position));				
			new_segment_number = sqlite3_column_double(stmt, segment_position);
				
			p_measuredValue->id = actual_id;
			p_measuredValue->ist = actual_ist;
			p_measuredValue->blood = actual_blood;				
			p_measuredValue->measuredate = GetTimeFromDB(QString::fromStdString(actual_measuredat));
				

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
		sqlite3_prepare_v2(db, query, -1, &stmt, 0);

	}	

	sqlite3_stmt* Database::GetNextResult()
	{
		sqlite3_step(stmt);
		return stmt;
	}

	void Database::SetUpStatement()
	{
		query = "SELECT * FROM measuredat";
		sqlite3_prepare_v2(db, query, -1, &stmt, 0);
		//const int index = sqlite3_bind_parameter_index(stmt, "id");
		//sqlite3_bind_int(stmt, index, )
		sqlite3_bind_int(stmt, 1, 2);

		int step = sqlite3_step(stmt);

		if (step == SQLITE_ROW)
		{
			cout << "The parameter is " << sqlite3_column_text(stmt, 1);
		}
		sqlite3_finalize(stmt);
	}

	double Database::QDateTime2RatTime(const QDateTime *qdt) {
		const qint64 diffFrom1970To1900 = 2209161600000;
		const double MSecsPerDay = 24.0*60.0*60.0*1000.0;
		const double InvMSecsPerDay = 1.0 / MSecsPerDay;

		qint64 diff = qdt->toMSecsSinceEpoch() + diffFrom1970To1900;
		return ((double)diff)*InvMSecsPerDay;
	}

	double Database::GetTimeFromDB(const QString time)
	{
		QDateTime q_time = QDateTime::fromString(time, Qt::ISODate);
		double d_time = QDateTime2RatTime(&q_time);

		return d_time;
	}
