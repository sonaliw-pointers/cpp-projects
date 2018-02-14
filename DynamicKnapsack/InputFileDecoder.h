#pragma once
#include "stdafx.h"
#include "KnapSackProblem.h"

// Class InputFileDecoder: Parse input file to get a KnapSackProblem at a time.
class InputFileDecoder
{
private:
	ifstream				_fInputFile;
	KnapSackProblem *					_pCurrentKNP;
public:
	InputFileDecoder(string ifInputName);
	
	int GetKnapSackProblem(KnapSackProblem *& opKnapSackProblem);
	
	~InputFileDecoder();
};

