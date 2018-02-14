#include "Printer.h"


Printer::Printer() :
	_printingJob(0)
{
	_outputFile.open("output.txt", ios::out | ios::trunc);
	_outputFile.clear();
	_outputFile.close();
}

int Printer::Print(Trip * ipTrip)
{
	if (ipTrip)
	{
		_outputFile.open("output.txt", ios::out | ios::app);
		if (_outputFile.is_open())
		{
			_printingJob++;

			int nbCities = ipTrip->GetNumberOfCities();
			_outputFile << _printingJob << " " << nbCities << " " << ipTrip->GetMinimumCost() << " "
				<< ipTrip->GetMaximumCost() << " " << ipTrip->GetRunningTime().count() << endl;

			int * pBestPath = new int[nbCities];
			ipTrip->GetBestPath(pBestPath);
			for (int iCity = 0; iCity < nbCities; iCity++)
			{
				_outputFile << pBestPath[iCity] << endl;
			}
			delete pBestPath; pBestPath = NULL;
		}
		_outputFile.close();
	}
	return 1;
}


Printer::~Printer()
{
	_outputFile.close();
}
