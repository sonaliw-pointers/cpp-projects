
using namespace std;
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
#include <numeric>



struct Item
{
    int itemNum = -1;
    int weight = 0;
    int profit = 0;
};

struct Knapsack
{
    //input parameters
    int nbItems = 0;
    int maxWeight = 0;
    vector<Item> listItems;
    
    //output parameters
    int maxProfit = 0;
    int totalWeight = 0;
    vector<bool> solution;
};


//Read the input file
int ReadInputFile(ifstream & iFile, Knapsack & oKnapsack)
{
    int ret = 0;
    if (iFile.good() && iFile.is_open())
    {
        string line;
        //take first line and set it to the number of items in the knapsack
        if (getline(iFile, line))
        {
            istringstream buffer(line);
            buffer >> oKnapsack.nbItems;
            oKnapsack.solution = vector<bool>(oKnapsack.nbItems, 0);
        }
        
        //take second line and assign it as the weight of each item
        if (getline(iFile, line))
        {
            istringstream buffer(line);
            int index = 0;
            for (int i = 0; i < oKnapsack.nbItems && getline(buffer, line, ','); i++)
            {
                istringstream buffer(line);
                int weight = 0;
                buffer >> weight;
                Item item;
                item.itemNum = i;
                item.weight = weight;
                item.profit = 0;
                oKnapsack.listItems.push_back(item);
            }
        }
        
        //take third line and assign it as the weight of each item
        if (getline(iFile, line))
        {
            istringstream buffer(line);
            for (int i = 0; i < oKnapsack.nbItems && getline(buffer, line, ','); i++)
            {
                istringstream buffer(line);
                buffer >> oKnapsack.listItems[i].profit;
            }
        }
        
        //take the fourth line and evaluate it as capacity of knapsack
        if (getline(iFile, line))
        {
            istringstream buffer(line);
            buffer >> oKnapsack.maxWeight;
        }
    }
    return ret;
}


//Print Function for printing the Knapsack
void PrintKnapsack(Knapsack &iKnapsack)
{
    cout << "\nItems : " << iKnapsack.nbItems
    << " Total Profit : " << iKnapsack.maxProfit
    << " Total Weight : " << iKnapsack.totalWeight
    << endl;
    
    //Print items in solution
    cout << "\nSelected Items: " << endl;
    cout << "Weight    Profit" << endl;
    
    for (size_t iSol = 0; iSol < iKnapsack.solution.size(); iSol++)
    {
        if (iKnapsack.solution[iSol])
            cout << iKnapsack.listItems[iSol].weight
            << "        " << iKnapsack.listItems[iSol].profit
            << endl;
    }
    
    cout << endl;
}

//Recursive function which is used to find the solution by Brute Force Method
int RecursionBF(Knapsack &iKnapsack,int iStart, vector<int> &iPossibleSol)
{
    if (iStart < iKnapsack.nbItems - 1)
    {
        for (int j = iStart; j < iKnapsack.nbItems; j++)
        {
            swap(iPossibleSol[iStart], iPossibleSol[j]);
            RecursionBF(iKnapsack, iStart + 1, iPossibleSol);
            swap(iPossibleSol[iStart], iPossibleSol[j]);
        }
    }
    else
    {
        // Permutation found
        int totalWeight = 0 , totalProfit = 0;
        vector<bool> solution(iKnapsack.nbItems);
        for (auto item : iPossibleSol)
        {
            if (totalWeight + iKnapsack.listItems[item].weight <= iKnapsack.maxWeight)
            {
                totalWeight += iKnapsack.listItems[item].weight;
                totalProfit += iKnapsack.listItems[item].profit;
                solution[item] = 1;
            }
            else
            {
                break;
            }
        }
        bool isKnapsackEmpty = !iKnapsack.totalWeight;
        bool doesProfitIncrease = totalProfit && totalProfit > iKnapsack.maxProfit;
        bool doesWeightIncrease = totalWeight && totalWeight > iKnapsack.totalWeight;
        if (isKnapsackEmpty || (doesProfitIncrease) || (doesProfitIncrease && doesWeightIncrease))
        {
            iKnapsack.maxProfit = totalProfit;
            iKnapsack.totalWeight = totalWeight;
            iKnapsack.solution = solution;
        }
    }
    
    return 0;
}

//Main Brute force Algorithm which uses recursive function for the solution
int SolutionByBruteForce(Knapsack &iKnapsack)
{
    vector<int> possibleSolutions(iKnapsack.nbItems);
    iota(std::begin(possibleSolutions), std::end(possibleSolutions), 0);
    RecursionBF(iKnapsack, 0, possibleSolutions);
    
    return 0;
    
}

int main(int argc, char *argv[])
{
    if (argc != 2) // argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        cout << "usage: " << argv[0] << " <file path>/<input file name> \n";
    else
    {
        ifstream inputFile(argv[1]);
        if (!inputFile)
        {
            cout << "Unable to open " << argv[1] << " for reading.\n";
            return(1);
        }
        
        inputFile.open(argv[1]);
        inputFile.clear();
        inputFile.seekg(0, ios::beg);
        
        Knapsack knapsack;
        ReadInputFile(inputFile, knapsack);
        inputFile.close();
        
        cout << "\nSolution of Knapsack Problem Using Brute Force Method"<< endl;
        cout<< "----------------------------------------------------------"<<endl;

        SolutionByBruteForce(knapsack);
        PrintKnapsack(knapsack);
    }
    return 0;
}

