#pragma once

#include <iostream>
#include <ctime>

class Person {
	std::string m_name;
	std::string m_password;
public:

	Person() : m_name(""), m_password("") {}

	Person(const std::string& name, const std::string& password)
		:m_name(name), m_password(password) {}

	// getters
	std::string getName() const { return m_name; }
	std::string getPassword() const { return m_password; }

	// setters
	void setName(const std::string& name) { m_name = name; }
	void setPassword(const std::string& password) { m_password = password; }
};