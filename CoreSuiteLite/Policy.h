#pragma once
#include <iostream>

class Policy {
public:
	int policyID, clientID, agentID,income, sum_assured, coverTillAge, tenure, premium, adb_sa, cc_sa, age;
	std::string fname, lname, policyType, email, mobile, gender, city, education, occupation, payment_method, payment_frequency, pstatus;
	bool tobacco, adb, cc;
	
	// functions
	void showDetails(Policy* currPolicy);
	static bool searchPolicy(int policyID);
	static void listPolicy();
	static bool createPolicy(); // working
	static void cancelPolicy(int policyID);
	int premiumCalc(Policy &policy); // todo
};