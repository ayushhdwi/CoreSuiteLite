#include <iostream>

#include "Client.h"
#include "Policy.h"
#include "Approver.h"
#include "notification.h"
#include "db_connection.cpp"

void Approver::approverDashboard() {
	int c_option;
	while (true) {
		cout << "Press Enter to continue:\n";
		cin.get();
		cin.get();
		system("cls");
		std::cout << "\n|------- APPROVER DASHBOARD -------|\n";
		std::cout << "1. Search Client\n";
		std::cout << "2. List Clients\n";
		std::cout << "3. Search Policy\n";
		std::cout << "4. List Policies\n";
		std::cout << "0. Logout\n";
		std::cout << "Enter 0-4 for selection: ";
		std::cin >> c_option;

		if (c_option == 1) {
			int id;
			std::cout << "Enter client ID: ";
			std::cin >> id;
			Client::searchClient(id);
		}
		else if (c_option == 2) {
			Client::listClients();
		}
		else if (c_option == 3) {
			int id;
			std::cout << "Enter Policy ID: ";
			std::cin >> id;
			Policy::searchPolicy(id);
		}
		else if (c_option == 4) {
			Policy::listPolicy();
		}
		else if (c_option == 0) {
			std::cout << "\nLogged out of the program.\n";
			break;
		}
	}
}

bool Approver::approve(int policyID) {
	DB_connection db;
	sql::PreparedStatement* pstmt;

	bool approve;
	std::cout << "Do you want to approve the policy (1=Yes || 0=No): ";
	std::cin >> approve;

	if (!approve) {
		std::cout << "Policy Not approved\n";
		return false;
	}
	else {
		// updating the policy status to cancelled in database
		pstmt = db.con->prepareStatement("UPDATE cslite.policies SET pstatus = 'approved' WHERE policyid = ?");
		pstmt->setInt(1, policyID);
		pstmt->executeQuery();
		printf("\nPolicy Approved\n\n");

		// deleting the pointer
		delete pstmt;

		// notify the client
		if (!notify(policyID)) std::cout << "Notification Not sent, some error occured\n";
		else std::cout << "Notification Sent Successfully.\n";
		return true;
	}
}