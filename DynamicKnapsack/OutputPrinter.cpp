#include "stdafx.h"
#include "OutputPrinter.h"


OutputPrinter::OutputPrinter(string ifOutputFileName): _printingJob(0)
{
	_sOutputFileName = ifOutputFileName;
	// Clear this file if anything is already there
	_fOutputFile.open(_sOutputFileName, ios::out | ios::trunc);
	//_fOutputFile.clear();
	_fOutputFile.close();
	
}

OutputPrinter::~OutputPrinter()
{
	_fOutputFile.close();
}


int OutputPrinter::Print(KnapSackProblem * ipKNP)
{
	if (ipKNP)
	{
		_fOutputFile.open(_sOutputFileName, ios::out | ios::app);
		if (_fOutputFile.is_open())
		{
			_printingJob++;

			int nbItems = ipKNP->GetNumberOfItems();
			_fOutputFile	<< _printingJob 
							<< " " << nbItems
							<< " " << ipKNP->GetMaxProfit() 
							<< " " << ipKNP->GetRunningTime().count() /1000 << "sec"
							<<  endl;

			// Print items in solution
			vector<int> vWeights, vProfits;
			ipKNP->GetItemsInSolution(&vWeights, &vProfits);
			for (size_t iSol = 0; iSol < vWeights.size(); iSol++)
			{
				_fOutputFile	<< vWeights[iSol]
								<< " " << vProfits[iSol]
								<< endl;
			}
			
		}
		_fOutputFile.close();
	}
	return 1;
}
