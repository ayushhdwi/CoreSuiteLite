#include <iostream>

#include "Clerk.h"
#include "Policy.h"
#include "Client.h"
#include "db_connection.cpp"

void Clerk::clerkDashboard() {
	int c_option;
	while (true) {
		cout << "Press enter to continue";
		cin.get(); cin.get();
		system("cls");
		std::cout << "\n|------- CLERK DASHBOARD -------|\n";
		std::cout << "1. Create Client\n";
		std::cout << "2. Search Client\n";
		std::cout << "3. List Clients\n";
		std::cout << "4. Search Policy\n";
		std::cout << "5. List Policies\n";
		std::cout << "6. List Of Cancelled Policies\n";
		std::cout << "0. Logout\n";
		std::cout << "Enter 0-5 for selection: ";
		std::cin >> c_option;

		if (c_option == 1) {
			createClient();
		}
		else if (c_option == 2) {
			int id;
			std::cout << "Enter client ID: ";
			std::cin >> id;
			Client::searchClient(id);
		}
		else if (c_option == 3) {
			Client::listClients();
		}
		else if (c_option == 4) {
			int id;
			std::cout << "Enter Policy ID: ";
			std::cin >> id;
			Policy::searchPolicy(id);
		}
		else if (c_option == 5) {
			Policy::listPolicy();
		}
		else if (c_option == 6) {
			Clerk::cancelledPolicies();
		}
		else if (c_option == 0) {
			std::cout << "\nLogged out of the program.\n";
			break;
		}
	}
}

void Clerk::createClient() {
	Client newClient;
	system("cls");
	std::cout << "Provide the following details for client creation\n";
	std::cout << "Enter client name: \n";
	std::cin.get();
	std::getline(std::cin, newClient.name);
	std::cout << "Enter client Age: ";
	std::cin >>	newClient.age;
	std::cout << "Enter client Occupation: ";
	std::cin >> newClient.occupation;
	std::cout << "Enter client Mobile number: ";
	std::cin >>	newClient.mobile;
	std::cout << "Enter client Email address: ";
	std::cin >>	newClient.email;
	std::cout << "Enter client Address: \n";
	std::cin.get();
	std::getline (std::cin, newClient.address);
	std::cout << "Enter client's Payment method: \n";
	std::cin.get();
	std::getline(std::cin ,newClient.payment_method);

	DB_connection db;
	sql::PreparedStatement* pstmt;
	pstmt = db.con->prepareStatement("INSERT INTO cslite.clients (Name, age, occupation, mobile, email, address, pmnt_method) VALUES (?,?,?,?,?,?,?)");
		pstmt->setString(1, newClient.name);
		pstmt->setInt(2,newClient.age);
		pstmt->setString(3, newClient.occupation);
		pstmt->setString(4, newClient.mobile);
		pstmt->setString(5, newClient.email);
		pstmt->setString(6, newClient.address);
		pstmt->setString(7, newClient.payment_method);
	pstmt->execute();
	std::cout << "Client created successfully\n";
}

void Clerk::cancelledPolicies() {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.policies WHERE pstatus = 'cancelled';";

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
		std::cout << std::endl << "Policy ID: " << id << std::endl;
		std::cout << "Client ID: " << result->getInt(2) << std::endl;
		std::cout << "Agent ID: " << result->getInt(3) << std::endl;
		std::cout << "Client Name: " << result->getString(4) << ' ' << result->getString(5) << std::endl;
		std::cout << "Policy Type: " << result->getString(6) << std::endl;
		std::cout << "Sum Assured: " << result->getInt(13) << std::endl;
		std::cout << "Premium: " << result->getInt(24) << std::endl << std::endl;
	}
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