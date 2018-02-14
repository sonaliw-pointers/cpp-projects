#pragma once

#include"CommonHeader.h"
#include"Trip.h"

// Class Decoder : Decodes input file.
class Decoder
{
private:
	ifstream _inputFile;
	Trip *_pCurrentTrip;
	
public:
	//Constructor
	Decoder();

	//Destructor
	~Decoder();

	// Gets Trip starting from current line.
	// returns 1  - When Decode of Trip succesful
	//		   0  - End of input file 
	int GetTrip(Trip *&opTrip);
};

