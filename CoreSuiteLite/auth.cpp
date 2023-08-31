#pragma once

#include <iostream>

#include "auth.h"
#include "Approver.h"
#include "Clerk.h"
#include "db_connection.cpp"

void flushToDB(std::string uname, std::string pass, std::string type) {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	pstmt = db.con->prepareStatement("INSERT INTO persons(Name, Password, alias) VALUES(?,?,?)");
		pstmt->setString(1, uname);
		pstmt->setString(2, pass);
		pstmt->setString(3, type);
	try {
		pstmt->execute();
		cout << "Row inserted to database." << endl;
	}
	catch (sql::SQLException e) {
		std::cout << "User already exists: \n" << e.what() << std::endl;
	}

	string s;
	cout << "Continue ?";
	cin >> s;

	delete pstmt;
}

bool createUser() {
	/*
	* returns true if task is completed else false
	*/

	int inp;
	system("cls");
	std::cout << "1. Approver\n";
	std::cout << "2. Clerk\n";
	std::cout << "3. Exit\n";
	std::cout << "Enter the user type: ";
	std:: cin >> inp;

	std::string uname, pswd, type;

	if (inp == 1) {
		type = "approver";
		std::cout << "Enter new username: ";
		std::cin >> uname;
		std::cout << "Enter new password: ";
		std::cin >> pswd;
		flushToDB(uname, pswd, type);
	}
	else if (inp == 2) {
		type = "clerk";
		std::cout << "Enter new username: ";
		std::cin >> uname;
		std::cout << "Enter new password: ";
		std::cin >> pswd;
		flushToDB(uname, pswd, type);
	}
	else if (inp == 3) {
		return false;
	}
	else {
		std::cout << "Please enter the correct value\n";
	}
}

int login(std::string type)
{
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	string username, pswd;
	cout << "\nEnter Username: ";
	cin >> username;
	cout << "\nEnter Password: ";
	cin >> pswd;

	std::string s = "SELECT * FROM persons WHERE alias = '"+type+"';";

	try {
		pstmt = db.con->prepareStatement(s);
		result = pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		cout << "Error occured : " << e.what() << endl;
		return -1;
		system("pause");
		exit(1);
	}

	int id;
	string name, alias, passwords;
	while (result->next()) {
		id = result->getInt(1);
		name = result->getString(2);
		passwords = result->getString(3);
		alias = result->getString(4);
		if (name == username && passwords == pswd) return id;
	}
	return -1;
}