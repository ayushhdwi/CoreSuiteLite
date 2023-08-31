#pragma once

#include <iostream>

class Client {
public:
	std::string name;
	int age;
	std::string occupation;
	std::string mobile;
	std::string email;
	std::string address;
	std::string payment_method;

	void showDetails(Client *currClient, int clientID);

	static bool searchClient(int id); // will open client dashboard
	static void listClients();
	
	void listOwnedPolicies(int clientID);
};