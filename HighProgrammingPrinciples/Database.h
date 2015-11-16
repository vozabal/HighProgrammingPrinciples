#include "sqlite3.h"
#include <iostream>
#pragma once
using namespace std;
class Database
{
	public:
		Database();

		~Database();

		void Open_database();
		void Close_database();
		void Print_query_results();
};

