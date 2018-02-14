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


int OutputPrinter::Print(Tour * ipTour)
{
	if (ipTour)
	{
		_fOutputFile.open(_sOutputFileName, ios::out | ios::app);
		if (_fOutputFile.is_open())
		{
			_printingJob++;

			int nbCities = ipTour->GetNumberOfCities();
			_fOutputFile	<< _printingJob 
							<< " " << nbCities 
							<< " " << ipTour->GetMinimumCost() 
							<< " " << ipTour->GetNbNodesToPQ() 
							<< " " << ipTour->GetRunningTime().count() 
							<<  endl;

			if (nbCities <= 14)
			{
				int * pBestPath = new int[nbCities + 1];
				ipTour->GetBestPath(pBestPath);
				for (int iCity = 0; iCity < nbCities + 1; iCity++)
				{
					_fOutputFile << pBestPath[iCity] << endl;
				}
				delete pBestPath; pBestPath = NULL;
			}
		}
		_fOutputFile.close();
	}
	return 1;
}
