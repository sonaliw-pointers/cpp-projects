#include "ContactDetails.h"


ContactDetails::ContactDetails(string iFirstName, string iLastName, string iPhone)
{
	_firstName = iFirstName;
	_lastName = iLastName;
	_phoneNumber = iPhone;
}

ContactDetails::~ContactDetails()
{
}

bool ContactDetails::operator>(ContactDetails iContact)
{
	bool rc = false;
	int compare = 0;
	compare = StringCompare(_firstName, iContact._firstName);
	if (1 == compare)
	{
		rc = true;
	}
	else if (0 == compare || -2 == compare)
	{
		compare = StringCompare(_lastName, iContact._lastName);
		if (1 == compare)
		{
			rc = true;
		}
		else if (0 == compare || -2 == compare)
		{
			compare = StringCompare(_phoneNumber, iContact._phoneNumber);
			if (1 == compare)
			{
				rc = true;
			}
		}
	}
	return rc;
}

bool ContactDetails::operator<(ContactDetails iContact)
{
	bool rc = false;
	int compare = 0;
	compare = StringCompare(_firstName, iContact._firstName);
	if (-1 == compare)
	{
		rc = true;
	}
	else if (0 == compare || -2 == compare)
	{
		compare = StringCompare(_lastName, iContact._lastName);
		if (-1 == compare)
		{
			rc = true;
		}
		else if (0 == compare || -2 == compare)
		{
			compare = StringCompare(_phoneNumber, iContact._phoneNumber);

			if (-1 == compare)
			{
				rc = true;
			}
		}
	}
	return rc;
}

bool ContactDetails::operator==(ContactDetails iContact)
{
	bool rc = false;
	int compare1 = 0;
	compare1 = StringCompare(_firstName, iContact._firstName);

	int compare2 = 0;
	compare2 = StringCompare(_lastName, iContact._lastName);

	int compare3 = 0;
	compare3 = StringCompare(_phoneNumber, iContact._phoneNumber);

	if (0 == compare1)
	{
		if (-2 == compare2 && -2 == compare3)
		{
			rc = true;
		}
		else if(0 == compare2 && -2 == compare3)
		{
			rc = true;
		}
		else if (0 == compare2 && 0 == compare3)
		{
			rc = true;
		}
	}

	else if (0 == compare2)
	{
		if (-2 == compare1 && -2 == compare3)
		{
			rc = true;
		}
		else if (0 == compare1 && -2 == compare3)
		{
			rc = true;
		}
		else if (0 == compare1 && 0 == compare3)
		{
			rc = true;
		}
	}

	else if (0 == compare3)
	{
		if (-2 == compare2 && -2 == compare1)
		{
			rc = true;
		}
		else if (0 == compare2 && -2 == compare1)
		{
			rc = true;
		}
		else if (0 == compare2 && 0 == compare1)
		{
			rc = true;
		}
	}	
	return rc;
}

bool ContactDetails::operator>=(ContactDetails iContact)
{
	bool rc = false;
	if ((*this) > iContact)
	{
		rc = true;
	}
	else if ((*this) == iContact)
	{
		rc = true;
	}
	return rc;
}

bool ContactDetails::operator<=(ContactDetails iContact)
{
	bool rc = false;
	if ((*this) < iContact)
	{
		rc = true;
	}
	else if ((*this) == iContact)
	{
		rc = true;
	}
	return rc;
}

void ContactDetails::PrintContact()
{
	cout << _firstName << " "
		<< _lastName << ", "
		<< _phoneNumber << endl;
}

int ContactDetails::StringCompare(string iString1, string iString2)
{
	int rc = 0;
	//iString1 is greater - return 1
	//iString1 is less - return -1
	// equals return 0
	// any string is empty return -2
	if (iString1 == "" || iString2 == "")
	{
		return -2;
	}
	int minLen = iString1.length() <= iString2.length() ? iString1.length() : iString2.length();
	for (size_t i = 0; i < minLen; i++)
	{
		char string1Char = iString1.at(i);
		char string2Char = iString2.at(i);
		if (string1Char == string2Char)
		{
			continue;
		}
		else
		{
			if (string1Char < string2Char)
			{
				rc = -1;
			}
			else
			{
				rc = 1;
			}
			break;
		}
	}

	// If string lenths are different
	if (0 == rc)
	{
		if (iString1.length() > iString2.length())
		{
			rc = 1;
		}
		else if (iString1.length() < iString2.length())
		{
			rc = -1;
		}
	}
	return rc;
}

