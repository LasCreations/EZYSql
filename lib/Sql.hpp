#pragma once

#include<stdlib.h>
#include<string>
#include<iostream>
#include<vector>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class Sql{
	private:
        	sql::Driver *driver;
        	sql::Connection *con;
        	sql::Statement *stmt;
        	sql::PreparedStatement *prep_stmt;
        	sql::ResultSet *res;

    	public:
        	bool Login(string, string);
        
		void CreateDatabase(string);
        
		vector<string> DatabaseAvailable();
        
		void CreateTable();
        
		void Insert();
        
		void Read();
};

