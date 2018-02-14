#include "stdafx.h"
#include "Node.h"

Node::Node(int inbCities) :
	_level(0),
	_pvCurrentPath(NULL),
	_pvCitiesToVisit(NULL),
	_bound(-1),
	_currentCost(-1),
	_lastCity(-1)
{
	_pvCurrentPath = new std::vector<int>;
	if (_pvCurrentPath)
	{
		_pvCurrentPath->push_back(0);
	}
	_pvCitiesToVisit = new std::vector<int>;
	if (_pvCitiesToVisit)
	{
		for (int cityToVisit = 1; cityToVisit < inbCities; cityToVisit++)
		{
			_pvCitiesToVisit->push_back(cityToVisit);
		}
		_pvCitiesToVisit->push_back(0);
	}

	_lastCity = 0;
	_currentCost = 0;
}

Node::Node(const Node *& ipParentNode,
	int iCityToAdd,
	double icostForAddition) :
	_level(0),
	_pvCurrentPath(NULL),
	_pvCitiesToVisit(NULL),
	_bound(-1),
	_currentCost(-1),
	_lastCity(iCityToAdd)
{
	if (ipParentNode)
	{
		// level
		_level = ipParentNode->_level + 1;

		//current path
		_pvCurrentPath = new std::vector <int>(*(ipParentNode->_pvCurrentPath));
		if (_pvCurrentPath)
		{
			_pvCurrentPath->push_back(iCityToAdd);
		}
		_currentCost = ipParentNode->_currentCost + icostForAddition;


		//Possible cities to visit
		_pvCitiesToVisit = new std::vector<int>;
		if (ipParentNode->_pvCitiesToVisit && _pvCitiesToVisit)
		{
			for (int& cityToVisit :  (*(ipParentNode->_pvCitiesToVisit)))
			{
				if (cityToVisit != iCityToAdd)
				{
					_pvCitiesToVisit->push_back(cityToVisit);
				}				
			}
		}
	}
}

Node::~Node()
{
	if (_pvCurrentPath)
	{
		delete _pvCurrentPath;
		_pvCurrentPath = NULL;
	}
	if (_pvCitiesToVisit)
	{
		delete _pvCitiesToVisit;
		_pvCitiesToVisit = NULL;
	}
}

bool Node::operator<(const Node & iOtherNode)
{
	return _bound < iOtherNode._bound;
}

bool Node::operator>(const Node & iOtherNode)
{
	return _bound > iOtherNode._bound;
}

int Node::GetLevel() const
{
	return _level;
}

double Node::GetBound(double ** const &ippCostMatrix, const int & inbCities)
{
	// Compute bound
	if (-1 == _bound && ippCostMatrix && _pvCurrentPath && _pvCitiesToVisit)
	{
		_bound = _currentCost;

		int sizeCurrentPath = _pvCurrentPath->size();
		if (0 < sizeCurrentPath)
		{
			int startCity = (*_pvCurrentPath)[0];
			int fromCity = (*_pvCurrentPath)[sizeCurrentPath - 1];

			// Find min cost from last city to othr cities
			double minCost = MinimumPossibleCost(fromCity, ippCostMatrix,false);
			_bound = _bound + minCost;

			// find min of all the cities
			int sizeCitiesToVisit = _pvCitiesToVisit->size();
			for (int cityToVisit = 0; cityToVisit < sizeCitiesToVisit - 1; cityToVisit++)
			{
				fromCity = (*_pvCitiesToVisit)[cityToVisit];
				minCost = MinimumPossibleCost(fromCity, ippCostMatrix);
				_bound = _bound + minCost;
			}
		}
	}
	return _bound;
}

double Node::GetCurrentCost() const
{
	return _currentCost;
}

int Node::GetLastCity() const
{
	return _lastCity;
}

int Node::CompleteTour(double ** const &ippCostMatrix, const int &inbCities)
{	
	if (_pvCitiesToVisit && _pvCurrentPath)
	{
		for (auto & cityToVisit : (*_pvCitiesToVisit))
		{
			int lastCity = _pvCurrentPath->back();
			_currentCost = _currentCost + ippCostMatrix[lastCity][cityToVisit];
			_pvCurrentPath->push_back(cityToVisit);
		}
	}
	return 1;
}

int * Node::GetCurrentPath() const
{
	int * pCurrentPath = NULL;
	pCurrentPath = _pvCurrentPath->data();
	return pCurrentPath;
}

const vector<int>* Node::GetCitiesToVisit()const
{
	const vector<int> * pcCities = _pvCitiesToVisit;
	return pcCities;
}

bool Node::IsValidCityToAdd(int iCityToAdd)
{
	bool bIsValid = true;
	for (int & iVisitedCity : (*_pvCurrentPath))
	{
		if (iVisitedCity == iCityToAdd)
		{
			bIsValid = false;
		}
	}
	return bIsValid;
}

double Node::MinimumPossibleCost(int &iFromCity,
	double ** const &ippCostMatrix,
	bool ibAllowReturnTrip)
{
	double minimumCost = -1;
	if (_pvCitiesToVisit && ippCostMatrix)
	{
		int size = _pvCitiesToVisit->size();
		if (!ibAllowReturnTrip)
		{
			size--;
		}
		for (int iCity = 0 ; iCity < size ; iCity++)
		{
			int toCity = (*_pvCitiesToVisit)[iCity];
			if (toCity != iFromCity && (
				-1 == minimumCost ||
				minimumCost > ippCostMatrix[iFromCity][toCity]
				))
			{
				minimumCost = ippCostMatrix[iFromCity][toCity];
			}
		}
	}
	return minimumCost;
}
