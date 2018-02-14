#include "stdafx.h"
#include "InputFileDecoder.h"


InputFileDecoder::InputFileDecoder(string ifInputName) : 
							_pCurrentKNP(NULL)
{
	_fInputFile.open(ifInputName);
	_fInputFile.clear();
	_fInputFile.seekg(0, ios::beg);
}

InputFileDecoder::~InputFileDecoder()
{
	_fInputFile.close();
	if (_pCurrentKNP)
	{
		delete _pCurrentKNP;
	}
	_pCurrentKNP = NULL;
}


int InputFileDecoder::GetKnapSackProblem(KnapSackProblem  *&opKNP)
{
	int rc = 0;

	if (_fInputFile.good() && _fInputFile.is_open())
	{
		int maxWeight = -1,			
			nbItems = 0;

		string line;

		if (getline(_fInputFile, line))
		{
			istringstream buffer(line);
			buffer >> nbItems >> maxWeight;

			if (_pCurrentKNP)
			{
				// Delete previous KnapSackProblem
				delete _pCurrentKNP; _pCurrentKNP = NULL;
			}

			// Create KnapSackProblem 
			if (0 < nbItems)
			{
				_pCurrentKNP = new KnapSackProblem(nbItems,maxWeight);
			}

			// Read cost from input file and store it to _pCurrentKNP
			if (_pCurrentKNP)
			{		
				for (int iItem = 0; iItem < nbItems; iItem++)
				{
					if (getline(_fInputFile, line))
					{
						int itemWt = -1, itemProfit = -1;
						istringstream buffer(line);

						// format of input weight profit
						buffer >> itemWt >> itemProfit;
						_pCurrentKNP->FillWeightProfitMatrix(iItem, itemWt, itemProfit);
					}
				}										
				rc = 1;
			}
		}
	}
	opKNP = _pCurrentKNP;
	return rc;
}


