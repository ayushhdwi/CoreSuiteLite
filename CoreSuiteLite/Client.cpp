#include <iostream>

#include "Policy.h"
#include "Client.h"
#include "db_connection.cpp"

void Client::showDetails(Client *currClient, int clientID) {
	std::string inp;
	system("cls");
	std::cout << "\n|------- CLIENT DETAILS -------|\n";
	std::cout << "Client ID: " << clientID << std::endl;
	std::cout << "Client Name: " << currClient->name << std::endl;
	std::cout << "Client Age: " << currClient->age << std::endl;
	std::cout << "Client Occupation: " << currClient->occupation << std::endl;
	std::cout << "Client Mobile: " << currClient->mobile << std::endl;
	std::cout << "Client Email: " << currClient->email << std::endl;
	std::cout << "Client Address: " << currClient->address << std::endl;
	std::cout << "Client Payment Method: " << currClient->payment_method << std::endl;
	std::cout << std::endl;
}

bool Client::searchClient(int id) {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.clients WHERE clientid = "+std::to_string(id)+";";

	try {
		pstmt = db.con->prepareStatement(s);
		result = pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		std::cout << "Error Occured: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	Client currClient;
	int c_id;
	bool flag = true;
	if (result->next()) {
		c_id = result->getInt(1);
		currClient.name = result->getString(2);
		currClient.age = result->getInt(3);
		currClient.occupation = result->getString(4);
		currClient.mobile = result->getString(5);
		currClient.email = result->getString(6);
		currClient.address = result->getString(7);
		currClient.payment_method = result->getString(8);
	}
	else return flag = false;

	int option;
	while (true) {
		// -------------- client dashboard starts from here --------------
		cout << "Press enter to continue\n";
		cin.get(); cin.get();
		system("cls");
		std::cout << "\n------- CLIENT DASHBOARD -------\n";
		std::cout << "1. Show Client Details\n";
		std::cout << "2. Create New Policy\n";
		std::cout << "3. Show List of owned Policies\n";
		std::cout << "4. Cancel a Policy\n";
		std::cout << "0. Exit from client dashboard\n";
		std::cout << "Enter value from 0-4 for option selection: ";
		std::cin >> option;

		if (option == 1) {
			currClient.showDetails(&currClient, c_id);
		}
		else if (option == 2) {
			Policy::createPolicy();
		}
		else if (option == 3) {
			currClient.listOwnedPolicies(c_id);
		}
		else if (option == 4) {
			int pid;
			std::cout << "Enter policy ID to cancel the policy: \n";
			std::cin >> pid;
			Policy::cancelPolicy(pid);
		}
		else if (option == 0) {
			break;
		}
		else {
			std::cout << "Wrong input, try again !\n";
		}

	}
	

	return flag;
}

void Client::listClients()
{
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.clients;";

	try {
		pstmt = db.con->prepareStatement(s);
		result = pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		std::cout << "Error Occured: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	int id;
	while (result->next()) {
		id = result->getInt(1);
		std::cout << std::endl << "Client ID: " << id << std::endl;
		std::cout << "Client Name: " << result->getString(2) << std::endl;
		std::cout << "Client Age: " << result->getInt(3) << std::endl << std::endl;
	}
	std::cout << "Enter client id to open client dashboard. Enter 0 to exit this screen.\nInput: ";
	std::cin >> id;

	if (id > 0) {
		if (!Client::searchClient(id)) {
			std::cout << "Client ID not found.\n";
			return;
		}
	}
	else if (id == 0) {
		std::cout << "Returning to ClerkDashboard\n";
		return;
	}
	else {
		std::cout << "Please enter correct input\n";
		return;
	}
}

void Client::listOwnedPolicies(int clientID) {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.policies WHERE clientid = "+to_string(clientID) + ";";

	try {
		pstmt = db.con->prepareStatement(s);
		result = pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		std::cout << "Error Occured: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	bool flag = false;
	int id;
	while (result->next()) {
		flag = true;
		id = result->getInt(1);
		std::cout << std::endl << "Policy ID: " << id << std::endl;
		std::cout << "Client ID: " << result->getInt(2) << std::endl;
		std::cout << "Agent ID: " << result->getInt(3) << std::endl;
		std::cout << "Client Name: " << result->getString(4) << ' ' << result->getString(5) << std::endl;
		std::cout << "Policy Type: " << result->getString(6) << std::endl;
		std::cout << "Sum Assured: " << result->getInt(13) << std::endl;
		std::cout << "Premium: " << result->getInt(24) << std::endl << std::endl;
	}
	if (!flag) cout << "Client Does not have any policies";
	else {
		std::cout << "Enter Policy id to open Policy dashboard. Enter 0 to exit this screen.\nInput: ";
		std::cin >> id;
		if (id > 0) {
			if (!Policy::searchPolicy(id)) {
				std::cout << "PolicyID did not match.\n";
				return;
			}
		}
		else if (id == 0) {
			std::cout << "Returning to Previous Dashboard\n";
			return;
		}
		else {
			std::cout << "Please enter correct input\n";
			return;
		}
	}
}