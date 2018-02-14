#pragma once

#include "commonHeader.h"
#include "ContactDetails.h"
class ContactDirectory
{

private:
	vector<ContactDetails*>			_listContacts;
	ifstream				_fInputFile;
	int						_nbContacts;

	




public:
	ContactDirectory();

	~ContactDirectory();

	void create(string ifInputName);

	void sort_contact();

	void search(string iName);

	void Delete(string iName);

	void insert(string iName);

private:
	int Partition(int iStart, int iEnd);
	int RandomizedPartition(int iStart, int iEnd);
	void RandomizedQuickSort(int iStart, int iEnd);

	int BinarySearch(int iStart, int iEnd, ContactDetails *ipContact);

};

