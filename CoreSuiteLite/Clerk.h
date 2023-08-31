#pragma once

#include <iostream>

#include "Person.h"

class Clerk : public Person {
	int m_id;
public:
	Clerk() : Person("", ""), m_id(-1) {}
	Clerk(int id, std::string name = "", std::string pass = "") : Person(name, pass), m_id(id) {}

	void clerkDashboard();
	void createClient();
	static void cancelledPolicies();
};