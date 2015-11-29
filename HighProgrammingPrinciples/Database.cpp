#include <iostream>
#include <sqlite3.h>

using namespace std;
class Database {	
	//Prepare statement
	sqlite3 *db;            /* Database handle */
	const char *query;       /* SQL statement, UTF-8 encoded */
	int nByte;              /* Maximum length of zSql in bytes. */
	sqlite3_stmt *result;  /* OUT: Statement handle */
	const char *pzTail;     /* OUT: Pointer to unused portion of zSql */
	
	public:
		Database()
		{
			
		}

		void Open_database()
		{
			int rc;

			rc = sqlite3_open("Resources\\direcnet.sqlite", &db);
			if (rc)
			{
				cerr << "Error opening SQLite3 database:" << sqlite3_errmsg;
			}
			else
			{
				cout << "The database has been opened succesfully";
			}
		}
		void Get_missing_ist()
		{
			query = "SELECT * FROM subject WHERE id = ?";
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
};
