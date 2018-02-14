#include "stdafx.h"
#include "Tour.h"
#include "Node.h"
#include "NodePriorityQ.h"


Tour::Tour(int iNbCities) :
	_nbCities(iNbCities),
	_minCost(-1),
	_pCostMatrix(NULL),
	_pBestPath(NULL),
	_runningTime(0),
	_nbNodesInPQ(0)
{
	_pCostMatrix = new double*[_nbCities];

	for (int iCity = 0; iCity < _nbCities; iCity++)
	{
		_pCostMatrix[iCity] = new double[_nbCities];
		for (int iCostRow = 0; iCostRow < _nbCities; iCostRow++)
		{
			_pCostMatrix[iCity][iCostRow] = 0;
		}
	}
}

int Tour::FillCostMatrix(int iOrigin, int iDestination, double iCost)
{
	_pCostMatrix[iOrigin][iDestination] = iCost;
	return 1;
}

int Tour::FillCostMatrix(int index, double iCost)
{
	if (_pCostMatrix)
	{
		if (index == 0)
		{
			_pCostMatrix[0][0] = iCost;
		}
		else
		{
			_pCostMatrix[index / _nbCities][index % _nbCities] = iCost;
		}
	}
	return 1;
}

double Tour::GetDirectTourCost(int iOrigin, int iDestination)const
{
	return _pCostMatrix[iOrigin][iDestination];
}

int Tour::ComputeBestPath()
{

	//Start timer
	chrono::milliseconds msStartTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);

	// BSF mechanism to find Best Tour
	BestPathUsingBFS();

	// End Timer
	chrono::milliseconds msEndTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);

	// total running time
	_runningTime = msEndTime - msStartTime;

	return 0;
}

int Tour::BestPathUsingBFS()
{
	//initialization
	int rc = 0;
	_nbNodesInPQ = 0;

	double minCost = -1;
	double bound = -1;

	Node * pParentNode = NULL;
	Node * pCurrentNode = NULL;

	//Creation Root Node 
	//enqueque this node in PQ
	Node * pRootNode = new Node(_nbCities);
	NodePriorityQ *pNodePQ = new NodePriorityQ;

	if (pRootNode && pNodePQ)
	{
		pNodePQ->push(pRootNode);
		_nbNodesInPQ++;
		pRootNode = NULL;

		double   ** const ppcCostMatrix = _pCostMatrix;
		//BFS
		while (!pNodePQ->empty())
		{
			// Remove Node with best bound
			pParentNode = pNodePQ->top();
			pNodePQ->pop();

			//Get Bound
			bound = pParentNode->GetBound(ppcCostMatrix, _nbCities);
			const vector<int> * pvCitiesToVisit = pParentNode->GetCitiesToVisit();
			if ((pParentNode && bound < minCost) || -1 == minCost)
			{
				for (int iCity : (*pvCitiesToVisit))
				{
					if (0 == iCity)
					{
						continue;
					}
					//creation of node for Parent.path + path from lastCity to iCity
					int lastCity = pParentNode->GetLastCity();
					const Node *pcParentNode = pParentNode;
					pCurrentNode = new Node(pcParentNode, iCity, _pCostMatrix[lastCity][iCity]);

					// Check if next vertex completes Tour
					if (pCurrentNode && pCurrentNode->GetLevel() == _nbCities - 2)
					{
						pCurrentNode->CompleteTour(ppcCostMatrix, _nbCities);
						double currentCost = pCurrentNode->GetCurrentCost();
						if (currentCost < minCost || -1 == minCost)
						{
							//cost of complete tour
							minCost = currentCost;
							_pBestPath = pCurrentNode->GetCurrentPath();
						}
					}
					else if ((pCurrentNode &&
						(pCurrentNode->GetBound(ppcCostMatrix, _nbCities)) < minCost) || // check of promising Node
						-1 == minCost)
					{
						//insert Promising Nodes to Queque
						pNodePQ->push(pCurrentNode);
						_nbNodesInPQ++;
						pCurrentNode = NULL;
					}
				}
			}
			delete pParentNode; pParentNode = NULL;
		}

		delete pNodePQ; pNodePQ = NULL;
	}
	_minCost = minCost;
	return rc;
}


int Tour::GetNumberOfCities() const
{
	return _nbCities;
}

double Tour::GetMinimumCost() const
{
	return _minCost;
}

chrono::milliseconds Tour::GetRunningTime() const
{
	return _runningTime;
}

int Tour::GetBestPath(int *& iopBestPath) const
{
	if (_pBestPath && iopBestPath)
	{
		for (int iCity = 0; iCity < _nbCities + 1; iCity++)
		{
			iopBestPath[iCity] = _pBestPath[iCity];
		}
	}
	return 1;
}

int Tour::GetNbNodesToPQ() const
{
	return _nbNodesInPQ;
}

Tour::~Tour()
{
	if (_pCostMatrix)
	{
		for (int iCostCol = 0; iCostCol < _nbCities; iCostCol++)
		{
			delete[] _pCostMatrix[iCostCol]; _pCostMatrix[iCostCol] = NULL;
		}
		delete[]_pCostMatrix; _pCostMatrix = NULL;
	}
	_pBestPath = NULL;
}


