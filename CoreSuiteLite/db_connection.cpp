#pragma once

#include <iostream>
#include <stdlib.h>

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include <cppconn/resultset.h>
#include <cppconn/resultset.h>
#include "cppconn/prepared_statement.h"

using namespace std;

class DB_connection {
	const string server = "localhost:3306";
	const string username = "root";
	const string password = "Ad112233";
public:
	sql::Driver* driver;
	sql::Connection* con;

	DB_connection() 
	{
		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

		con->setSchema("cslite");
		//cout << "Connected to db !\n";
	}
	~DB_connection() {
		delete con;
	}
};