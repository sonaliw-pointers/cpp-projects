#pragma once

// class to solve KnapSackProblem
class KnapSackProblem
{
private:
	int							_nbItems;
	int							_maxWeight;
	int *						_pWeightMatrix;
	int *						_pProfitMatrix;
	chrono::milliseconds		_runningTime;
	int							_maxProfit;
	int **						_ppB;
	vector<int>	*				_pvItemsInSolution;

	// DP algo implemented here
	int SolveUsingDynamicProg();

public:
	// Constructor
	KnapSackProblem(int inbItems, int iMaxWeight);

	//Destructor
	~KnapSackProblem();

	// Fill weight and profit arrays
	void FillWeightProfitMatrix(int iItemIndex,int iWeight, int iProfit);

	// Call this to Solve this problem
	int Solve();	

	//returns Number of items
	int GetNumberOfItems();

	// returns Max profit
	int GetMaxProfit();

	// returns time required to solve this problem
	chrono::milliseconds GetRunningTime();

	// returns weight and profits of items in solution.
	void GetItemsInSolution(vector<int> *ipvWeights, vector<int> *ipvProfits);
};

