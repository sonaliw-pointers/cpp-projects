#pragma once
#include"CommonHeader.h"
#include"Trip.h"

//Class Printer : prints details of Trip
class Printer
{
	ofstream	_outputFile;
	int			_printingJob;
public:
	//Constructor
	Printer();

	// print output of Trip to outpuFile
	int Print(Trip* ipTrip);

	//Destructor
	~Printer();
};

