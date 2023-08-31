#include <iostream>
#include <stdlib.h>

#include "db_connection.cpp"
#include "auth.h"
#include "Approver.h"
#include "Clerk.h"

using namespace std;

int main() {
	DB_connection db;

	while (true) {
		int option;
		system("cls");
		cout << "Select the user type:\n";
		cout << "1. Approver\n";
		cout << "2. Clerk\n";
		cout << "3. Create account\n";
		cout << "0. Exit\n\n";
		cout << "Enter 1/2/3/0 for selection: ";
		cin >> option;

		if (option == 1) {
			// _______ login for Approver _______
			int id = login("approver");
			if (id > 0) {
				Approver* approver = new Approver(id,"","");
				cout << "logged in\n";
				approver->approverDashboard();
			}
			else cout << "Login Failed, wrong credentials\n";
		}
		else if (option == 2) {
			// _______ Login for clerk _______
			int id = login("clerk");
			if (id > 0) {
				Clerk* clerk = new Clerk(id,"","");
				cout << "logged in\n";
				clerk->clerkDashboard();
			}
			else cout << "Login Failed, wrong credentials\n";
		}
		else if (option == 3) {
			if (createUser()) cout << "User created successfully\n";
			else cout << "User Creation Failed !\n";
		}
		else if (option == 0) {
			cout << "\nEXITING THE PROGRAM \n";
			return 0;
		}
		else {
			cout << "Please enter the correct number\n";
		}
	}
}
