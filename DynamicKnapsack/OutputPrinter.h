#pragma once
#include "stdafx.h"
#include "KnapSackProblem.h"

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

	// prints output of given KnapSackProblem
	int Print(KnapSackProblem * ipKnapSackProblem);
};

