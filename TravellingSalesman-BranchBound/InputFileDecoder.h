#pragma once
#include "stdafx.h"
#include "Tour.h"

// Class InputFileDecoder: Parse input file and store cost matrix in Tour
class InputFileDecoder
{
private:
	// FileFormat to handle both type of input files
	enum FileFormat
	{
		UnDefined = 1,
		CostMatrixFormat , 
		AdjMatrixFormat
	};
private:
	ifstream				_fInputFile;
	Tour *					_pCurrentTour;
	FileFormat				_fileFormat;
	
	void CheckFileFormat();
public:
	InputFileDecoder(string ifInputName);
	
	int GetTour(Tour *& opTour);	
	
	~InputFileDecoder();
};

