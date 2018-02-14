#include "stdafx.h"
#include "KnapSackProblem.h"


KnapSackProblem::KnapSackProblem(int inbItems, int iMaxWeight) :
	_nbItems(inbItems),
	_maxWeight(iMaxWeight),
	_pWeightMatrix(NULL),
	_pProfitMatrix(NULL),
	_runningTime(0),
	_maxProfit(-1),
	_ppB(NULL),
	_pvItemsInSolution(NULL)
{
	// Initialization
	_pWeightMatrix = new int[inbItems];
	_pProfitMatrix = new int[inbItems];
	for (int iIndex = 0; iIndex < _nbItems; iIndex++)
	{
		_pWeightMatrix[iIndex] = 0;
		_pProfitMatrix[iIndex] = 0;
	}


	_ppB = new int *[_nbItems + 1];
	if (_ppB)
	{
		for (int iRow = 0; iRow < _nbItems + 1; iRow++)
		{
			_ppB[iRow] = new int[_maxWeight + 1];
			for (int iCol = 0; iCol < _maxWeight + 1; iCol++)
			{
				_ppB[iRow][iCol] = -1;
			}
		}
	}

	_pvItemsInSolution = new vector<int>;
}


KnapSackProblem::~KnapSackProblem()
{
	// clear
	if (_pWeightMatrix)
	{
		delete[] _pWeightMatrix; _pWeightMatrix = NULL;
	}
	if (_pProfitMatrix)
	{
		delete[] _pProfitMatrix; _pProfitMatrix = NULL;
	}
	if (_ppB)
	{
		for (int iRow = 0; iRow < _nbItems + 1; iRow++)
		{
			delete[] _ppB[iRow]; _ppB[iRow] = NULL;
		}
		delete[] _ppB; _ppB = NULL;
	}

	if (_pvItemsInSolution)
	{
		delete _pvItemsInSolution; _pvItemsInSolution = NULL;
	}
}

void KnapSackProblem::FillWeightProfitMatrix(int iItemIndex, int iWeight, int iProfit)
{
	if (_pWeightMatrix && _pProfitMatrix)
	{
		_pWeightMatrix[iItemIndex] = iWeight;
		_pProfitMatrix[iItemIndex] = iProfit;
	}
}
int KnapSackProblem::Solve()
{

	//Start timer
	chrono::milliseconds msStartTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);

	// DP mechanism to find Max profit of KnapSackProblem
	SolveUsingDynamicProg();

	// End Timer
	chrono::milliseconds msEndTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);

	// total running time
	_runningTime = msEndTime - msStartTime;

	return 0;
}

int KnapSackProblem::GetNumberOfItems()
{
	return _nbItems;
}

int KnapSackProblem::GetMaxProfit()
{
	return _maxProfit;
}

chrono::milliseconds KnapSackProblem::GetRunningTime()
{
	return _runningTime;
}

void KnapSackProblem::GetItemsInSolution(vector<int>* ipvWeights, vector<int>* ipvProfits)
{
	if (ipvProfits && ipvWeights && _pvItemsInSolution)
	{
		for (int iItem : (*_pvItemsInSolution))
		{
			ipvProfits->push_back(_pProfitMatrix[iItem]);
			ipvWeights->push_back(_pWeightMatrix[iItem]);
		}
	}
}

int KnapSackProblem::SolveUsingDynamicProg()
{
	if (_ppB)
	{
		// ppKeptMatrix keeps record of items added in solution
		int **ppKeptMatrix = NULL;
		ppKeptMatrix = new int *[_nbItems + 1];

		//initialise all cells to 0
		if (ppKeptMatrix)
		{
			for (int iRow = 0; iRow < _nbItems + 1; iRow++)
			{
				ppKeptMatrix[iRow] = new int[_maxWeight + 1];
				for (int iCol = 0; iCol < _maxWeight + 1; iCol++)
				{
					ppKeptMatrix[iRow][iCol] = 0;
				}
			}
		}

		// intialize row0 to 0
		for (int iCol = 0; iCol < _maxWeight + 1; iCol++)
		{
			_ppB[0][iCol] = 0;
		}
		for (int k = 1; k < _nbItems + 1; k++)
		{
			_ppB[k][0] = 0;
			for (int w = 1; w < _maxWeight + 1; w++)
			{				
				int wk = _pWeightMatrix[k - 1];
				int bk = _pProfitMatrix[k - 1];
				if (wk <= w && (_ppB[k - 1][w - wk] + bk > _ppB[k - 1][w]))
				{
					_ppB[k][w] = _ppB[k - 1][w - wk] + bk;

					// put 1 when item is included
					ppKeptMatrix[k][w] = 1;
				}
				else
				{
					_ppB[k][w] = _ppB[k - 1][w];
				}
			}
		}

		_maxProfit = _ppB[_nbItems][_maxWeight];

		int remainingWt = _maxWeight;
		for (int iItem = _nbItems-1; iItem >= 0; iItem--)
		{
			if (_pvItemsInSolution && 1 == ppKeptMatrix[iItem+1][remainingWt])
			{
				_pvItemsInSolution->push_back(iItem);

				// intermediate weights doesnt matter
				// jump to Weight valid weight column
				remainingWt = remainingWt - _pWeightMatrix[iItem];
			}			
		}

		// clear ppKeptMatrix
		if (ppKeptMatrix)
		{
			for (int iRow = 0; iRow < _nbItems + 1; iRow++)
			{
				delete[] ppKeptMatrix[iRow]; ppKeptMatrix[iRow] = NULL;
			}
			delete[] ppKeptMatrix; ppKeptMatrix = NULL;
		}
	}
	return 0;
}
