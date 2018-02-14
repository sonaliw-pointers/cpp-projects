#pragma once
#include "stdafx.h"
#include "Tour.h"

// Class OutputPrinter : For printing output in file
class OutputPrinter
{
private:
	ofstream	_fOutputFile;
	string		_sOutputFileName;
	int			_printingJob;
public:
	OutputPrinter(string ifOutputFileName);
	~OutputPrinter();
	int Print(Tour * ipTour);
};

