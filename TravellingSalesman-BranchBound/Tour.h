#pragma once

#include "stdafx.h"

// Class Tour : Stores decoded Tour data and computes optimum tour
class Tour
{
private:
	int							_nbCities;
	double						_minCost;
	double **					_pCostMatrix;
	int *						_pBestPath;
	chrono::milliseconds		_runningTime;
	int							_nbNodesInPQ;

	// Gets cost from origin to destination
	double GetDirectTourCost(int iOrigin, int iDestination)const;

public:
	//Constructor
	Tour(int iNbCities);

	// fill cost of tour in cost matrics
	int FillCostMatrix(int iorigin, int iDestinatio, double iCost);	

	// fill cost of tour in cost matrics
	int FillCostMatrix(int index, double iCost);

	// Computes best path to travel
	int ComputeBestPath();

	// Find best possible path using BFS branch and bound algo
	int BestPathUsingBFS();

	// Gets number of cities
	int GetNumberOfCities()const;

	// Get minimum cost of Tour
	double GetMinimumCost()const;	

	// Get time taken to find best path
	chrono::milliseconds GetRunningTime()const;

	// Get best path
	int GetBestPath(int *& iopBestPath) const;

	//Get number of nodes added to PQ
	int GetNbNodesToPQ() const;

	// Destructor
	~Tour();
};

