#include "ContactDirectory.h"
#include "commonHeader.h"


ContactDirectory::ContactDirectory() : _nbContacts(0)
{
}


ContactDirectory::~ContactDirectory()
{
	if (0 < _listContacts.size())
	{
		for (auto contact : _listContacts)
		{
			delete contact;
			contact = NULL;
		}
		_listContacts.empty();
	}
}

void ContactDirectory::create(string ifInputName)
{
	//ifInputName = "input_text.txt";
	_fInputFile.open(ifInputName);
	_fInputFile.clear();
	_fInputFile.seekg(0, ios::beg);

	if (_fInputFile.good() && _fInputFile.is_open())
	{
		string pFirstName = "";
		string pLastName = "";
		string pPhoneNumber = "";
		string line;

		while (getline(_fInputFile, line))
		{
			istringstream buffer(line);
			buffer >> pFirstName >> pLastName >> pPhoneNumber;
			ContactDetails *pContact = new ContactDetails(pFirstName,
				pLastName.substr(0, pLastName.length() - 1),
				pPhoneNumber);
			_listContacts.push_back(pContact);
			_nbContacts++;
		}
		_fInputFile.close();
	}
}

void ContactDirectory::sort_contact()
{
	RandomizedQuickSort(0, _listContacts.size() - 1);
	for (int i = 0; i < _listContacts.size(); i++) {
		ContactDetails* pTemp = _listContacts[i];
		pTemp->PrintContact();
	}
}

void ContactDirectory::search(string iName)
{
	string line;
	string pFirstName = "";
	string pLastName = "";
	string pPhone = "";
	int index = -1;	
	getline(cin, line);
	istringstream buffer(line);
	buffer >> pFirstName >> pLastName>> pPhone;
	if (pLastName != "" && ',' == pLastName.at(pLastName.length()-1))
	{
		pLastName = pLastName.substr(0, pLastName.length() - 1);
	}
	ContactDetails *pInputContact = new ContactDetails(pFirstName, pLastName, pPhone);
	index = BinarySearch(0, _listContacts.size() - 1, pInputContact);
	delete pInputContact; pInputContact = NULL;
	if (-1 != index)
	{	
		_listContacts[index]->PrintContact();
	}
	else
	{
			cout << "Name Not Found" << endl;
	}
}

void ContactDirectory::Delete(string iName)
{
	string pFirstName = "";
	string pLastName = "";
	string pPhoneNumber = "";

	cin >> pFirstName >> pLastName >> pPhoneNumber;
	if (pLastName != "" &&',' == pLastName.at(pLastName.length() - 1))
	{
		pLastName = pLastName.substr(0, pLastName.length() - 1);
	}
	ContactDetails *pInputContact = new ContactDetails(pFirstName, pLastName, pPhoneNumber);
	int index = BinarySearch(0, _listContacts.size() - 1, pInputContact);
	if (-1 != index)
	{
		_listContacts.erase(_listContacts.begin() + index);
		for (int i = 0; i < _listContacts.size(); i++) {
			ContactDetails* pTemp = _listContacts[i];
			pTemp->PrintContact();
		}
	}
	else
	{
		cout << "Name Not Found" << endl;
	}

	delete pInputContact; pInputContact = NULL;

}

void ContactDirectory::insert(string iName)
{
	string pFirstName = "";
	string pLastName = "";
	string pPhoneNumber = "";

	cin >> pFirstName >> pLastName >> pPhoneNumber;
	if (pLastName != "" &&',' == pLastName.at(pLastName.length() - 1))
	{
		pLastName = pLastName.substr(0, pLastName.length() - 1);
	}
	ContactDetails *pInputContact = new ContactDetails(pFirstName, pLastName.substr(0, pLastName.size() - 1), pPhoneNumber);

	for (int i = 0; i < _nbContacts; i++) {
		if ((*_listContacts[i]) < (*pInputContact)) {
			continue;
		}
		else {
			_listContacts.insert(_listContacts.begin() + i, pInputContact);
			for (int i = 0; i < _listContacts.size(); i++) {
				ContactDetails* pTemp = _listContacts[i];
				pTemp->PrintContact();
			}
			break;
		}
	}

}

int ContactDirectory::Partition(int iStart, int iEnd)
{
	int i, j;
	ContactDetails* x = NULL;

	x = _listContacts[iEnd];
	i = iStart - 1 < 0 ? 0 : iStart - 1;
	j = iEnd + 1 > _listContacts.size() - 1 ? _listContacts.size() - 1 : iEnd + 1;


	while (true) {
		while ((*_listContacts[j]) > (*x) && j > iStart) {
			j--;
		}
		while ((*_listContacts[i]) < (*x) && i < iEnd) {
			i++;
		}
		if (i < j) {
			ContactDetails *pTemp = NULL;
			pTemp = _listContacts[i];
			_listContacts[i] = _listContacts[j];
			_listContacts[j] = pTemp;
			i++;
			j--;
		}
		else
			break;
	}

	return j;
}

int ContactDirectory::RandomizedPartition(int iStart, int iEnd)
{
	int i = iStart;
	i = rand() % (iEnd - iStart + 1) + iStart;

	ContactDetails *pTemp = NULL;
	pTemp = _listContacts[i];
	_listContacts[i] = _listContacts[iEnd];
	_listContacts[iEnd] = pTemp;

	return Partition(iStart, iEnd);

}

void ContactDirectory::RandomizedQuickSort(int iStart, int iEnd)
{
	if (iStart < iEnd)
	{
		int q;
		q = RandomizedPartition(iStart, iEnd);
		RandomizedQuickSort(iStart, q);
		RandomizedQuickSort(q + 1, iEnd);
	}


}

int ContactDirectory::BinarySearch(int iStart, int iEnd, ContactDetails *ipContact)
{
	int index;
	if (iStart > iEnd) {
		index = -1;
	}
	else {
		int mid = (iStart + iEnd) / 2;

		if ((*ipContact) == (*_listContacts[mid])) {
			index = mid;
		}
		else {
			if ((*ipContact) < (*_listContacts[mid])) {
				index = BinarySearch(iStart, mid - 1, ipContact);
			}
			else {
				index = BinarySearch(mid + 1, iEnd, ipContact);
			}
		}
	}
	return index;
}

