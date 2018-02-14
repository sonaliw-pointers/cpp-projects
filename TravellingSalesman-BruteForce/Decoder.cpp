#include "Decoder.h"

Decoder::Decoder() :
	_inputFile("input.txt"),
	_pCurrentTrip(NULL)
{
}

int Decoder::GetTrip(Trip  *&opTrip)
{
	int rc = 0;
	if (_inputFile.good() && _inputFile.is_open())
	{
		int indexOrigin = -1, 
			indexDestination = -1, 
			travelCost = -1, 
			nbCities = 0;

		string line;		
		
		if (getline(_inputFile, line) )
		{
			// read number of cities
			if (string::npos == line.find(" "))
			{
				nbCities = atoi(line.c_str());
				if (_pCurrentTrip)
				{
					// Delete previous Trip
					delete _pCurrentTrip; _pCurrentTrip = NULL;
				}

				// Create Trip 
				if (nbCities)
				{
					_pCurrentTrip = new Trip(nbCities);
				}				
			}

			// Read cost from input file and store it to _pCurrentTrip
			if (_pCurrentTrip)
			{
				for (int iCost = 0; iCost < nbCities*nbCities; iCost++)
				{
					if (getline(_inputFile, line))
					{
						istringstream buffer(line);
						buffer >> indexOrigin >> indexDestination >> travelCost;
						_pCurrentTrip->FillCostMatrix(indexOrigin, indexDestination, travelCost);

						indexOrigin = indexDestination = travelCost = -1;
					}
				}

				rc = 1;
			}
		}
	}
	opTrip = _pCurrentTrip;
	return rc;

}
Decoder::~Decoder()
{
	_inputFile.close();
	if (_pCurrentTrip)
	{
		delete _pCurrentTrip; _pCurrentTrip = NULL;
	}
}
