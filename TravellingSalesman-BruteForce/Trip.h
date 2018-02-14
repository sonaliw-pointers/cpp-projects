#pragma once

#include"CommonHeader.h"

// Class Trip : Stores decoded trip data
class Trip
{
private:
	int							_nbCities;
	int							_maxCost;
	int							_minCost;
	int *						_pCostMatrix;
	int *						_pBestPath;
	int *						_pPath;
	chrono::milliseconds		_runningTime;

	//Swap 2 numbers
	int Swap(int * ipStart, int * ipIndex);

	// Recursively iterates for all permutations of paths 
	int Perm(int iStart);

	// Gets cost from origin to destination
	int GetDirectTripCost(int iOrigin, int iDestination)const;

public:
	//Constructor
	Trip(int iNbCities);

	// fill cost of tour in cost matrics
	int FillCostMatrix(int iorigin, int iDestinatio, int iCost);	

	// Computes best path to travel
	int ComputeBestPath();

	// Gets number of cities
	int GetNumberOfCities()const;

	// Get minimum cost of trip
	int GetMinimumCost()const;

	// Get maximum cost of trip
	int GetMaximumCost()const;

	// Get time taken to find best path
	chrono::milliseconds GetRunningTime()const;

	// Get best path
	int GetBestPath(int *& iopBestPath) const;

	// Destructor
	~Trip();
};

