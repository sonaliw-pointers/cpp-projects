#pragma once
#include "commonHeader.h"
class ContactDetails
{
private:
	string _firstName;
	string _lastName;
	string _phoneNumber;

	
public:
	ContactDetails(string iFirstName, string iLastName, string iPhone);
	~ContactDetails();

	bool operator >(ContactDetails iContact);
	bool operator <(ContactDetails iContact);
	bool operator ==(ContactDetails iContact);
	bool operator >=(ContactDetails iContact);
	bool operator <=(ContactDetails iContact);
	void PrintContact();

private:
	int StringCompare(string iString1, string iString2);
	
};

