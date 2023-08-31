#pragma once
#include <iostream>

#include "Person.h"

class Approver : public Person {
	int m_id;
public:
	Approver() : Person("",""), m_id(-1) {}
	Approver(int id, std::string name = "", std::string pass = "") : Person(name, pass), m_id(id) {}

	void approverDashboard();
	static bool approve(int policyID);
};