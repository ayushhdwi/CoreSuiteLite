#include <iostream>

#include "Policy.h"
#include "Client.h"
#include "Approver.h"
#include "notification.h"
#include "db_connection.cpp"

// todo
void Policy::showDetails(Policy* currPolicy) {
	std::cout << std::endl;
	std::cout << "Policy number: " << currPolicy->policyID << std::endl;
	std::cout << "Related Cliend ID: " << currPolicy->clientID << std::endl;
	std::cout << "Related Agent ID: " << currPolicy->agentID << std::endl;
	std::cout << "Client's Name: " << currPolicy->fname << ' ' << currPolicy->lname << std::endl;
	std::cout << "Client's Age: " << currPolicy->age << std::endl;
	std::cout << "Policy Type: " << currPolicy->policyType << std::endl;
	std::cout << "Client Email: " << currPolicy->email << std::endl;
	std::cout << "Client Mobile Number: " << currPolicy->mobile << std::endl;
	std::cout << "Client Gender: " << currPolicy->gender << std::endl;
	std::cout << "Client's Tobacco consumption status: " << (currPolicy->tobacco ? "Yes" : "No") << std::endl;
	std::cout << "Client's Income: " << currPolicy->income << std::endl;
	std::cout << "Policy Sum assured: " << currPolicy->sum_assured << std::endl;
	std::cout << "Cover Till Age: " << currPolicy->coverTillAge << std::endl;
	std::cout << "Additional Death Benefit Taken: " << (currPolicy->adb ? "Yes" : "No") << std::endl;
	std::cout << "Additional Death Benefit Sum Assured: " << currPolicy->adb_sa << std::endl;
	std::cout << "Comprehensive Care Taken: " << (currPolicy->cc ? "Yes" : "No") << std::endl;
	std::cout << "Comprehensive Care Sum Assured: " << currPolicy->cc_sa << std::endl;
	std::cout << "Policy Tenure: " << currPolicy->tenure << std::endl;
	std::cout << "Client's City: " << currPolicy->city << std::endl;
	std::cout << "Client's Highest Education level: " << currPolicy->education << std::endl;
	std::cout << "Client's Occupation: " << currPolicy->occupation << std::endl;
	std::cout << "Payment Method: " << currPolicy->payment_method << std::endl;
	std::cout << "Payment Frequency: " << currPolicy->payment_frequency << std::endl;
	std::cout << "Policy Status: " << currPolicy->pstatus << std::endl;
	std::cout << "Policy Premium: " << currPolicy->premium << std::endl << std::endl;
	
}

bool Policy::searchPolicy(int policyID) {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.policies WHERE policyID = " + std::to_string(policyID) + ";";

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

	int option;
	while (true) {
		// -------------- client dashboard starts from here --------------
		cout << "Press enter to continue\n";
		cin.get();
		cin.get();
		system("cls");
		std::cout << "---------- POLICY DASHBOARD ----------\n";
		std::cout << "1. Show Policy Details\n";
		std::cout << "2. Cancel Policy\n";
		std::cout << "3. Approve Policy\n";
		std::cout << "0. Exit from policy dashboard\n";
		std::cout << "Enter value from 0-3 for option selection: ";
		std::cin >> option;

		if (option == 1) {
			currPolicy.showDetails(&currPolicy);
		}
		else if (option == 2) {
			Policy::cancelPolicy(currPolicy.policyID);
		}
		else if (option == 3) {
			Approver::approve(currPolicy.policyID);
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

void Policy::listPolicy() {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.policies;";

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

// helper functions for policy creation
Client* getClient(int id) {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	std::string s = "SELECT * FROM cslite.clients WHERE clientid = " + std::to_string(id) + ";";

	try {
		pstmt = db.con->prepareStatement(s);
		result = pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		std::cout << "Error Occured: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	Client* currClient = new Client();
	int c_id;
	if (result->next()) {
		c_id = result->getInt(1);
		currClient->name = result->getString(2);
		currClient->age = result->getInt(3);
		currClient->occupation = result->getString(4);
		currClient->mobile = result->getString(5);
		currClient->email = result->getString(6);
		currClient->address = result->getString(7);
		currClient->payment_method = result->getString(8);
	}
	else return nullptr;

	delete pstmt;
	return currClient;
}
void flushPolicy(Policy &policy) {
	DB_connection db;
	sql::PreparedStatement* pstmt;
	pstmt = db.con->prepareStatement("INSERT INTO policies(clientid, agentid, fname, lname, policytype, email, mobile, gender, tobacco, income, sum_assured, coverTillAge, adb, cc, tenure, city, education, occupation, payment_method, payment_frequency, pstatus, premium, adb_sa, cc_sa, age) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
		pstmt->setInt(1, policy.clientID);
		pstmt->setInt(2, policy.agentID);
		pstmt->setString(3, policy.fname);
		pstmt->setString(4, policy.lname);
		pstmt->setString(5, policy.policyType);
		pstmt->setString(6, policy.email);
		pstmt->setString(7, policy.mobile);
		pstmt->setString(8, policy.gender);
		pstmt->setBoolean(9, policy.tobacco);
		pstmt->setInt(10, policy.income);
		pstmt->setInt(11, policy.sum_assured);
		pstmt->setInt(12, policy.coverTillAge);
		pstmt->setBoolean(13, policy.adb);
		pstmt->setBoolean(14, policy.cc);
		pstmt->setInt(15, policy.tenure);
		pstmt->setString(16, policy.city);
		pstmt->setString(17, policy.education);
		pstmt->setString(18, policy.occupation);
		pstmt->setString(19, policy.payment_method);
		pstmt->setString(20, policy.payment_frequency);
		pstmt->setString(21, policy.pstatus);
		pstmt->setInt(22, policy.premium);
		pstmt->setInt(23, policy.adb_sa);
		pstmt->setInt(24, policy.cc_sa);
		pstmt->setInt(25, policy.age);
	pstmt->execute();

	cout << "New Policy Created with pending status." << endl;

	delete pstmt;
}
bool confirmSumAssured(Policy &newp) {
	std::cout << "Enter Sum Assured for Policy: ";
	std::cin >> newp.sum_assured;
	std::cout << "Enter Cover Till Age: ";
	std::cin >> newp.coverTillAge;

	if (newp.sum_assured <= 30000000 && newp.sum_assured >= 10000) {
		if (newp.coverTillAge <= 100 && newp.coverTillAge > 15) {
			int premium = (newp.sum_assured * newp.age) / (1200);
			std::cout << "The Premium for the following will be: " << premium << endl;
			std::cout << "Continue with same Sum assured & Cover till age ? (Y/N)\n";
			char inp;
			std::cin >> inp;
			if (inp == 'Y') return true;
			else if ('N') return false;
			else std::cout << "Please enter correct input\n";
		}
		else {
			std::cout << "Cover Period Till Age should be less than 100 years\n";
			return false;
		}
	}
	else {
		std::cout << "Sum assured, should be between 10,000 and 3,00,00,000 Rupees\n";
		return false;
	}
}
void addRiders(Policy& newp) {
	char inp;
	// Aditional Death Benefit
	std::cout << "Do you want Aditional Death Benefit (Y/N): ";
	std::cin >> inp;
	if (inp == 'Y') newp.adb = true;
	else if (inp == 'N') newp.adb = false;
	else std::cout << "Wrong Input";
	if (newp.adb) {
		while (true) {
			std::cout << "Enter Sum Assured for Aditional Death Benefit: ";
			std::cin >> newp.adb_sa;
			if (newp.adb_sa >= 25000) break;
			else std::cout << "Please enter sum greater than 25K.\n";
		}
	}
	else newp.adb_sa = 0;

	// Comprehensive Cover
	std::cout << "Do you want Comprehensive Coverage (Y/N): ";
	std::cin >> inp;
	if (inp == 'Y') newp.cc = true;
	else if (inp == 'N') newp.cc = false;
	else std::cout << "Wrong Input";
	if (newp.cc) {
		while (true) {
			std::cout << "Enter Sum Assured for Comprehensive Cover: ";
			std::cin >> newp.cc_sa;
			if (newp.cc_sa >= 200000) break;
			else std::cout << "Please enter sum greater than 2 Lakhs.\n";
		}
	}
	else newp.cc_sa = 0;
}
bool Policy::createPolicy() {
	Policy newp;
	Client* newc;
	while (true) {
		std::cout << "Enter Client ID: ";
		std::cin >> newp.clientID;
		if (newp.clientID == 0) return false;
		newc = getClient(newp.clientID);
		if (newc == nullptr) {
			std::cout << "Client ID does not exist\nTo continue enter correct client ID or enter 0 to exit this screen\n";
		} else break;
	}

	std::cout << "Enter Agent ID: ";
	std::cin >> newp.agentID;
	std::cout << "Enter First Name: ";
	std::cin >> newp.fname;
	std::cout << "Enter Last Name: ";
	std::cin >> newp.lname;

	// getting info from client
	newp.age = newc->age;
	newp.email = newc->email;
	newp.mobile = newc->mobile;

	std::cout << "Enter Gender (male/female): ";
	std::cin >> newp.gender;

	std::cout << "Enter Tobacco(Y/N): ";
	char inp; std::cin >> inp;
	if (inp == 'Y') newp.tobacco = true;
	else if (inp == 'N') newp.tobacco = false;
	else {
		std::cout << "Wrong Input";
		return false;
	}

	std::cout << "Enter Policy Type (term, whole life, money back, endowment): ";
	std::cin >> newp.policyType;

	std::cout << "Enter Income: ";
	std::cin >> newp.income;

	while (confirmSumAssured(newp) == false) {
		std::cout << "Enter the values again\n";
	}
	
	// Adding Riders
	addRiders(newp);

	std::cout << "Enter Tenure (pay upto age): ";
	std::cin >> newp.tenure;

	//std::cout << "Enter city: ";
	newp.city = newc->address; // REDUNDANT with client address

	std::cout << "Enter Highest Education Degree: ";
	std::cin >> newp.education;

	// Getting info from client
	newp.occupation = newc->occupation;
	newp.payment_method = newc->payment_method;

	int option;
	std::cout << "Select from the following payment frequency\n1.Monthly\n2.Quarterly\n3.Half Yearly\n4. Annually\nEnter Payment Frequency: ";
	std::cin >> option;
	if (option == 1) {
		newp.payment_frequency = "monthly";
	}
	else if (option == 2) {
		newp.payment_frequency = "quarterly";
	}
	else if (option == 3) {
		newp.payment_frequency = "half yearly";
	}
	else if (option == 4) {
		newp.payment_frequency = "annually";
	}

	newp.pstatus = "pending";
	
	// to calculate premium
	newp.premiumCalc(newp);

	std::cout << "\nDo you accept the terms and conditions ?\n";
	bool accept = false;
	std::cout << "Enter 1 = Yes | 0 = No.\n";
	std::cin >> accept;
	if (!accept) {
		std::cout << "Terms and conditions not accepted, aborting\n";
		return false;
	}

	std::cout << "\nTo continue, Complete the Payment\n";
	std::cout << "Payment Completed ? 1 = Yes | 0 = No\n";
	bool payment;
	std::cin >> payment;
	if (!payment) {
		std::cout << "Payment not done, aborting\n";
		return false;
	}

	flushPolicy(newp);

	return true;
}

// todo -> notificatoin left to be sent
void Policy::cancelPolicy(int policyID) {
	DB_connection db;

	// check if the policy exist or not
	sql::PreparedStatement* pstmt1;
	sql::ResultSet* result1;

	std::string s = "SELECT * FROM cslite.policies WHERE policyID = " + std::to_string(policyID) + ";";

	try {
		pstmt1 = db.con->prepareStatement(s);
		result1 = pstmt1->executeQuery();
	}
	catch (sql::SQLException e) {
		std::cout << "Error Occured: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}

	Policy currPolicy;
	bool flag = true;
	// Filling the details in object
	if (result1->next()) {
		currPolicy.policyID = result1->getInt(1);
	}
	else {
		std::cout << "Policy Does not exist\n";
		return;
	}

	sql::PreparedStatement* pstmt;
	
	bool cancel;
	std::cout << "Confirm cancellation of the policy (1=Yes || 0=No): ";
	std::cin >> cancel;

	if (!cancel) {
		std::cout << "Policy not cancelled\n";
	}
	else {
		// updating the policy status to cancelled in database
		pstmt = db.con->prepareStatement("UPDATE cslite.policies SET pstatus = 'cancelled' WHERE policyid = ?");
		pstmt->setInt(1, policyID);
		pstmt->executeQuery();
		printf("\nPolicy Cancelled\n\n");

		// deleting the pointer
		delete pstmt;
		// notify the client
		notify(policyID);
	}
}

int Policy::premiumCalc(Policy &policy) { 
	int premium = (policy.sum_assured * policy.age) / (1200);
	int adb_cover = policy.adb_sa;
	int cc_cover = policy.cc_sa;
	int adbPremium = 0, ccPremium = 0, finalPremium = 0;

	int multiple = 0;
	if (adb == true) {
		finalPremium += 10;
		adb_cover -= 25000;
		multiple = adb_cover / 50000;
		finalPremium += multiple * 10;
	}

	multiple = 0;
	if (cc == true) {
		finalPremium += 80;
		cc_cover -= 200000;
		multiple += cc_cover / 300000;
		finalPremium += multiple * 400;
	}

	// Adding the 18% tax to the premium calculated
	finalPremium += (int)(1.18 * finalPremium);
	
	// changing the premium value from monthly to other
	// half yearly
	// monthly
	// annually
	// quarterly
	if (policy.payment_frequency == "half yearly") {
		finalPremium *= 6;
	}
	else if (policy.payment_frequency == "annually") {
		finalPremium *= 12;
	}
	else if (policy.payment_frequency == "quarterly") {
		finalPremium *= 3;
	}
	policy.premium = finalPremium;
	return finalPremium;
}
