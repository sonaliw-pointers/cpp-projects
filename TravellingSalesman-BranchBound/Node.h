#pragma once
#include"stdafx.h"


// class Node - stores the attributes of Node in space state tree.
class Node
{
private:
	int					_level;
	std::vector<int> *	_pvCurrentPath;
	std::vector<int> *	_pvCitiesToVisit;
	double				_bound;
	double				_currentCost;	
	int					_lastCity;

public:
	//Constructors
	//Parameter : inbCities - total number of cities
	//Creates a Root Node 
	Node(int inbCities);


	// parameters : iParentNode - parent node
	//				iCityToAdd - next city to visit
	//				icostForAddition - cost of visit to iCityToAdd
	Node(const Node *&iParentNode,int iCityToAdd, double icostForAddition);

	//Destructors
	~Node();

	// comparator operator implementations
	bool				operator<(const Node & iOtherNode);
	bool				operator>(const Node & iOtherNode);


	//returns level
	int					GetLevel() const;

	// Compute the bound of this node
	double				GetBound(double** const &ippCostMatrix, const int & inbCities);

	// Returns CurrentCost of this Node
	double				GetCurrentCost() const;

	// returns last city of path of this Node
	int					GetLastCity() const;

	// Appends the remaining cities to visit and start city to complete tour
	// It also updates the current cost of updated tour
	int					CompleteTour(double ** const &ippCostMatrix, const int &inbCities);

	// returns the path stored in this Node
	int*				GetCurrentPath() const;

	// returns the list of cities not visited
	const vector<int>*	GetCitiesToVisit()const;

	// Checks if iCitytoAdd already visited
	bool				IsValidCityToAdd(int iCityToAdd);
private:
	// picks min cost tour from iFromCity to rest of the cities
	double				MinimumPossibleCost(int &iFromCity,  double ** const &ippCostMatrix, bool ibAllowReturnTrip = true);
	
};



