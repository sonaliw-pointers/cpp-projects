#include "stdafx.h"
#include "InputFileDecoder.h"


InputFileDecoder::InputFileDecoder(string ifInputName) : 
							_pCurrentTour(NULL), 
							_fileFormat(UnDefined)
{
	_fInputFile.open(ifInputName);

	CheckFileFormat();

	_fInputFile.clear();
	_fInputFile.seekg(0, ios::beg);
}

InputFileDecoder::~InputFileDecoder()
{
	_fInputFile.close();
	if (_pCurrentTour)
	{
		delete _pCurrentTour;
	}
	_pCurrentTour = NULL;
}

void InputFileDecoder::CheckFileFormat()
{
	if (UnDefined == _fileFormat)
	{
		string line;
		getline(_fInputFile, line);
		getline(_fInputFile, line);
		_fileFormat = CostMatrixFormat;

		int iSpaces = 0;
		for (unsigned int iLoop(0); iLoop < line.length(); iLoop++)
		{
			if (line.at(iLoop) == ' ')
				iSpaces++;
			if (3 == iSpaces)
			{
				_fileFormat = AdjMatrixFormat;
				break;
			}
		}

	}
}
int InputFileDecoder::GetTour(Tour  *&opTour)
{
	int rc = 0;

	if (_fInputFile.good() && _fInputFile.is_open())
	{
		int indexOrigin = -1,
			indexDestination = -1,			
			nbCities = 0;

		double travelCost = -1;

		string line;

		if (getline(_fInputFile, line))
		{
			// read number of cities
			if (string::npos == line.find(" "))
			{
				nbCities = atoi(line.c_str());
				if (_pCurrentTour)
				{
					// Delete previous Tour
					delete _pCurrentTour; _pCurrentTour = NULL;
				}

				// Create Tour 
				if (0 < nbCities )
				{
					_pCurrentTour = new Tour(nbCities);
				}
			}

			// Read cost from input file and store it to _pCurrentTour
			if (_pCurrentTour)
			{		
				switch (_fileFormat)
				{
				case InputFileDecoder::UnDefined:
					break;
				case InputFileDecoder::CostMatrixFormat:
				{
					for (int iCost = 0; iCost < nbCities*nbCities; iCost++)
					{
						if (getline(_fInputFile, line))
						{
							istringstream buffer(line);

							// format of input indexOrigin indexDestination travelCost
							buffer >> indexOrigin >> indexDestination >> travelCost;
							_pCurrentTour->FillCostMatrix(indexOrigin, indexDestination, travelCost);

							travelCost = indexOrigin = indexDestination =  -1;
						}
					}
				}
					break;
				case InputFileDecoder::AdjMatrixFormat:
				{
					if (getline(_fInputFile, line))
					{
						istringstream buffer(line);
						for (int iCost = 0; iCost < nbCities*nbCities; iCost++)
						{
							buffer >> travelCost;
							_pCurrentTour->FillCostMatrix(iCost, travelCost);
						}
					}
				}
					break;
				}						
				rc = 1;
			}
		}
	}
	opTour = _pCurrentTour;
	return rc;
}


