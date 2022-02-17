#pragma once


#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>


struct Person {

	std::string surname;
	std::string name;
	std::optional<std::string> patronymic;

};


struct PhoneNumber {

	int pageCode;
	int cityCode;
	std::string phoneNum;
	std::optional<int> addNum;
};

class PhoneBook {
private:
	std::vector<std::pair<Person, PhoneNumber>> m_contacts;


public:

	PhoneBook(std::ifstream& in);

	PhoneBook(std::stringstream& in);

	~PhoneBook() {}

	friend std::ostream& operator<< (std::ostream& out, const PhoneBook& pb);

	void SortByName();

	void SortByPhone();

	void ChangePhoneNumber(const Person& person, const PhoneNumber& newpn);

	std::pair<std::string, std::vector<PhoneNumber>> GetPhoneNumber(const std::string& surname);
};

bool operator< (const Person& person1, const Person& person2);
bool operator== (const Person& person1, const Person& person2);
std::optional<int> getAddNum(std::string& add);
std::ostream& operator<< (std::ostream& out, const PhoneNumber& pn);
bool operator< (const PhoneNumber& pn1, const PhoneNumber& pn2);
bool operator== (const PhoneNumber& pn1, const PhoneNumber& pn2);
