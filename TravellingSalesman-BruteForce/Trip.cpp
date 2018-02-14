#include "Trip.h"

Trip::Trip(int iNbCities):
				_nbCities(iNbCities),
				_maxCost(-1),
				_minCost(-1),
				_pCostMatrix(NULL),
				_pBestPath(NULL),
				_pPath(NULL),
				_runningTime(0)
{
	_pCostMatrix = new int[_nbCities*_nbCities];
	for (int iCost = 0; iCost < _nbCities*_nbCities; iCost++)
	{
		_pCostMatrix[iCost] = 0;
	}
	_pBestPath = new int[_nbCities];
	_pPath = new int[_nbCities];
	for (int iCity = 0; iCity < _nbCities; iCity++)
	{
		_pBestPath[iCity] = _pPath[iCity] = iCity;
	}
}

int Trip::FillCostMatrix(int iOrigin, int iDestination, int iCost)
{
	if (_pCostMatrix)
	{
		_pCostMatrix[iDestination + _nbCities * iOrigin] = iCost;
	}
	return 1;
}

int Trip::GetDirectTripCost(int iOrigin, int iDestination)const
{
	return _pCostMatrix[iDestination + _nbCities * iOrigin];
}

int Trip::ComputeBestPath()
{
	//Start timer
	chrono::milliseconds msStartTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);

	// Check all permutations for given number of cities
	Perm(0);

	// End Timer
	chrono::milliseconds msEndTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);

	// total running time
	_runningTime = msEndTime - msStartTime;
	return 0;
}
int Trip::GetNumberOfCities() const
{
	return _nbCities;
}
int Trip::GetMinimumCost() const
{
	return _minCost;
}
int Trip::GetMaximumCost() const
{
	return _maxCost;
}
chrono::milliseconds Trip::GetRunningTime() const
{
	return _runningTime;
}
 int Trip::GetBestPath(int *& iopBestPath) const
{
	if (_pBestPath && iopBestPath)
	{
		for (int iCity = 0; iCity < _nbCities; iCity++)
		{
			iopBestPath[iCity] = _pBestPath[iCity];
		}
	}
	return 1;
}
int Trip::Swap(int * ipStart, int * ipIndex)
{
	int temp = *ipStart;
	*ipStart = *ipIndex;
	*ipIndex = temp;
	return 1;
}

// Recursive fuction to find all possible permutations
int Trip::Perm(int iStart)
{
	if (iStart < _nbCities - 1)
	{
		for (int j = iStart; j < _nbCities; j++)
		{
			Swap(&_pPath[iStart], &_pPath[j]);
			Perm(iStart + 1);
			Swap(&_pPath[iStart], &_pPath[j]);
		}
	}
	else
	{
		// Permutation found
		int currentCost = GetDirectTripCost(_pPath[_nbCities-1], _pPath[0]);
		for (int iCity = 0; iCity < _nbCities-1; iCity++)
		{
			currentCost = currentCost + GetDirectTripCost(_pPath[iCity], _pPath[iCity + 1]);
		}
		if (-1 == _minCost && -1 == _maxCost)
		{
			_minCost = _maxCost = currentCost;
		}
		else if (currentCost < _minCost)
		{
			_minCost = currentCost;

			//Store best Path
			for (int iCity = 0; iCity < _nbCities; iCity++)
			{
				_pBestPath[iCity] = _pPath[iCity];
			}
		}
		else if (currentCost > _maxCost)
		{
			_maxCost = currentCost;
		}
	}
	return 1;
}
Trip::~Trip()
{
	if (_pCostMatrix)
	{
		delete []_pCostMatrix; _pCostMatrix = NULL;
	}
	if (_pBestPath)
	{
		delete []_pBestPath; _pBestPath = NULL;
	}
	if (_pPath)
	{
		delete[]_pPath; _pPath = NULL;
	}
}


