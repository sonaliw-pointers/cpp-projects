
#include "commonHeader.h"

#include <stdio.h>
using namespace std;

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "ContactDirectory.h"

int main(int argc, char *argv[])
{
	if (argc != 2) // argc should be 2 for correct execution
				   // We print argv[0] assuming it is the program name
		cout << "usage: " << argv[0] << " <file path>/<input file name> \n";
	else
	{
		ifstream inputFile(argv[1]);
		if (!inputFile)
		{
			cout << "Unable to open " << argv[1] << " for reading.\n";
			return(1);
		}
		ContactDirectory* pDirectory = new ContactDirectory();
		if (NULL != pDirectory)
		{
			pDirectory->create(argv[1]);
			int choice = 0;
			string name;
			do {
				cout << ("\n1) Sort Contact");
				cout << ("\n2) Search Contact");
				cout << ("\n3) Delete Contact");
				cout << ("\n4) Insert Contact");
				cout << ("\nEnter The Choice :");
				choice = 0;
				cin >> (choice);
				cin.ignore(1000, '\n');
				switch (choice) {
				case 1:
					pDirectory->sort_contact();
					break;

				case 2:
					cout << ("\nEnter the name -> ") << flush;
					pDirectory->search(name);
					break;

				case 3:
					cout << ("\nEnter the name -> ");
					pDirectory->Delete(name);
					break;

				case 4:
					cout << ("\nEnter the name -> ");
					pDirectory->insert(name);
					break;
				default:
					cout << ("\nWrong Choice... \nPlease enter the choice again: ");
					cin >> (choice);
					break;
				}
				
			} while (choice);
		}
	}
	return 0;
}

