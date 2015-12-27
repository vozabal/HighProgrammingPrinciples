#pragma once

#include <iostream>
#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>
#include <QDateTime>
#include "Segment.h"
#include "MeasuredValue.h"
using namespace std;

class Database
{
	public:
		//Prepare statement
		sqlite3 *db;            /* Database handle */
		const char *query;       /* SQL statement, UTF-8 encoded */
		int nByte;              /* Maximum length of zSql in bytes. */
		sqlite3_stmt *stmt;  /* OUT: Statement handle */
		const char *pzTail;     /* OUT: Pointer to unused portion of zSql */

		Database();
		~Database();

		vector<Segment*> GetSegments();

		void PushCoefficients(vector<double> coefficients, int segment_id);
		double QDateTime2RatTime(const QDateTime *qdt);
		double GetTimeFromDB(const QString time);

		void Print_query_results(); // k nicemu
		sqlite3_stmt *GetNextResult(); // k nicemu
		void Get_missing_ist(); // K nicemu
		void SetUpStatement(); // K nicemu

	private:
		void Open_database();
		void Close_database();

};

