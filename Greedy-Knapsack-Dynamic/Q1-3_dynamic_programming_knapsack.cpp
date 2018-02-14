
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


//Function which solve the 0/1 knapsack problem by Dynamic Programming
int SolutionByDP(Knapsack &iKnapsack)
{
    int ret = 0;
    vector<vector<int>> dpMatrix(iKnapsack.nbItems + 1, vector<int>(iKnapsack.maxWeight + 1, 0));
    vector<vector<int>> keepMatrix(iKnapsack.nbItems + 1, vector<int>(iKnapsack.maxWeight + 1, 0));
    
    for (int i = 1; i <= iKnapsack.nbItems; i++)
    {
        int currentWeight = iKnapsack.listItems[i - 1].weight;
        int currentProfit = iKnapsack.listItems[i - 1].profit;
        for (int w = 1; w <= iKnapsack.maxWeight; w++)
        {
            int updatedProfit = dpMatrix[i - 1][w - currentWeight] + currentProfit;
            if (currentWeight <= w && (updatedProfit > dpMatrix[i - 1][w]))
            {
                dpMatrix[i][w] = dpMatrix[i - 1][w - currentWeight] + currentProfit;
                keepMatrix[i][w] = 1;
            }
            else
            {
                dpMatrix[i][w] = dpMatrix[i - 1][w];
            }
        }
    }
    
    //max profit
    iKnapsack.maxProfit = dpMatrix[iKnapsack.nbItems][iKnapsack.maxWeight];
    
    //solution and total weight
    int leftWt = iKnapsack.maxWeight;
    for (int j = iKnapsack.nbItems - 1; j >= 0; j--)
    {
        if (1 == keepMatrix[j + 1][leftWt])
        {
            iKnapsack.solution[j] = 1;
            leftWt = leftWt - iKnapsack.listItems[j].weight;
            iKnapsack.totalWeight += iKnapsack.listItems[j].weight;
        }
    }
    return ret;
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
        
        cout << "\nSolution of Knapsack Problem Using Dynamic Programming"<< endl;
        cout<< "----------------------------------------------------------"<<endl;

        SolutionByDP(knapsack);
        PrintKnapsack(knapsack);
        
    }
    return 0;
}

