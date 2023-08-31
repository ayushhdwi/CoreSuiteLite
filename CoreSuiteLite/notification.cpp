#include <iostream>
#include <fstream>

#include "Policy.h"
#include "notification.h"
#include "db_connection.cpp"

bool notify(int pid) {
	// Opening a file for writing
	std::ofstream notificationFile("C:/Users/ayush.dwivedi/notification.txt");

	// Check if the file was opened successfully
	if (!notificationFile.is_open()) {
		std::cerr << "Error: Could not open the file for writing." << std::endl;
		return false;
	}

	// Connecting to DB
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.policies WHERE policyID = " + std::to_string(pid) + ";";

	try {
		pstmt = db.con->prepareStatement(s);
		result = pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		std::cout << "Error Occured: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	Policy currPolicy;
	bool flag = true;
	// Filling the details in object
	if (result->next()) {
		currPolicy.policyID = result->getInt(1);
		currPolicy.clientID = result->getInt(2);
		currPolicy.agentID = result->getInt(3);
		currPolicy.fname = result->getString(4);
		currPolicy.lname = result->getString(5);
		currPolicy.policyType = result->getString(6);
		currPolicy.email = result->getString(7);
		currPolicy.mobile = result->getString(8);
		currPolicy.gender = result->getString(9);
		currPolicy.tobacco = result->getBoolean(10);
		currPolicy.income = result->getInt(11);
		currPolicy.sum_assured = result->getInt(12);
		currPolicy.coverTillAge = result->getInt(13);
		currPolicy.adb = result->getBoolean(14);
		currPolicy.cc = result->getBoolean(15);
		currPolicy.tenure = result->getInt(16);
		currPolicy.city = result->getString(17);
		currPolicy.education = result->getString(18);
		currPolicy.occupation = result->getString(19);
		currPolicy.payment_method = result->getString(20);
		currPolicy.payment_frequency = result->getString(21);
		currPolicy.pstatus = result->getString(22);
		currPolicy.premium = result->getInt(23);
		currPolicy.adb_sa = result->getInt(24);
		currPolicy.cc_sa = result->getInt(25);
		currPolicy.age = result->getInt(26);
	}
	else return flag = false;

	// Write some data to the file
	/*notificationFile << "This is a sample text that will be written to the file." << std::endl;
	notificationFile << "You can add more lines as needed." << std::endl;*/

	notificationFile << "Your Policy Number " << currPolicy.policyID << " has been " << currPolicy.pstatus << std::endl;
	notificationFile << std::endl << "Other Policy Details" << std::endl;
	notificationFile << "Related Cliend ID: " << currPolicy.clientID << std::endl;
	notificationFile << "Related Agent ID: " << currPolicy.agentID << std::endl;
	notificationFile << "Client's Name: " << currPolicy.fname << ' ' << currPolicy.lname << std::endl;
	notificationFile << "Client's Age: " << currPolicy.age << std::endl;
	notificationFile << "Policy Type: " << currPolicy.policyType << std::endl;
	notificationFile << "Client Email: " << currPolicy.email << std::endl;
	notificationFile << "Client Mobile Number: " << currPolicy.mobile << std::endl;
	notificationFile << "Client Gender: " << currPolicy.gender << std::endl;
	notificationFile << "Client's Tobacco consumption status: " << (currPolicy.tobacco ? "Yes" : "No") << std::endl;
	notificationFile << "Client's Income: " << currPolicy.income << std::endl;
	notificationFile << "Policy Sum assured: " << currPolicy.sum_assured << std::endl;
	notificationFile << "Cover Till Age: " << currPolicy.coverTillAge << std::endl;
	notificationFile << "Additional Death Benefit Taken: " << (currPolicy.adb ? "Yes" : "No") << std::endl;
	notificationFile << "Additional Death Benefit Sum Assured: " << currPolicy.adb_sa << std::endl;
	notificationFile << "Comprehensive Care Taken: " << (currPolicy.cc ? "Yes" : "No") << std::endl;
	notificationFile << "Comprehensive Care Sum Assured: " << currPolicy.cc_sa << std::endl;
	notificationFile << "Policy Tenure: " << currPolicy.tenure << std::endl;
	notificationFile << "Client's City: " << currPolicy.city << std::endl;
	notificationFile << "Client's Highest Education level: " << currPolicy.education << std::endl;
	notificationFile << "Client's Occupation: " << currPolicy.occupation << std::endl;
	notificationFile << "Payment Method: " << currPolicy.payment_method << std::endl;
	notificationFile << "Payment Frequency: " << currPolicy.payment_frequency << std::endl;
	notificationFile << "Policy Premium: " << currPolicy.premium << std::endl << std::endl;

	// Close the file
	notificationFile.close();
	std::cout << "\nData has been written to the file 'notification.txt'.\n\n";
	return flag;
}