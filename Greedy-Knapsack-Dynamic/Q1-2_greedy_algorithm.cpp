
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
    
    // Print items in solution
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



//All functions are to actually sort the elements based on the some criteria like Weight or Profit or profit/weight
bool HasGreaterWeight(Item first, Item second)
{
    return first.weight > second.weight;
}

bool HasLessWeight(Item first, Item second)
{
    return first.weight < second.weight;
}

bool HasGreaterProfit(Item first, Item second)
{
    return first.profit > second.profit;
}

bool HasGreterProfitPerUnit(Item first, Item second)
{
    return first.profit/first.weight > second.profit/second.weight;
}


//Function to solve 0/1 knapsack problem using greedy method 1. i.e. Maximum Benefit First
int SolutionByGreedy1(Knapsack &iKnapsack)
{
    vector<Item> listSorted = iKnapsack.listItems;
    //Sort the list based on greater benefit first basis
    sort(listSorted.begin(), listSorted.end(), HasGreaterProfit);
    
    int weight = 0 , maxProfit = 0;
    vector<bool> solution(iKnapsack.nbItems,false);
    for (Item item : listSorted)
    {
        if (weight + item.weight <= iKnapsack.maxWeight)//check if it is not exceeding the knapsack capacity
        {
            //if not exceeding then add weight and profit
            solution[item.itemNum] = true;
            weight += item.weight;
            maxProfit += item.profit;
        }
    }
    
    iKnapsack.totalWeight = weight;
    iKnapsack.maxProfit = maxProfit;
    iKnapsack.solution = solution;
    
    return 0;
}

//Function to solve 0/1 knapsack problem using greedy method 2. i.e. Minumum Weight First
int SolutionByGreedy2(Knapsack &iKnapsack)
{
    vector<Item> listSorted = iKnapsack.listItems;
    //Sort the list based on less weight first basis
    sort(listSorted.begin(), listSorted.end(), HasLessWeight);
    
    int weight = 0 , maxProfit = 0;
    vector<bool> solution(iKnapsack.nbItems,false);
    for (Item item : listSorted)
    {
        if (weight + item.weight <= iKnapsack.maxWeight)//check if it is not exceeding the knapsack capacity
        {
            //if not exceeding then add weight and profit
            solution[item.itemNum] = true;
            weight += item.weight;
            maxProfit += item.profit;
        }
    }
    
    iKnapsack.totalWeight = weight;
    iKnapsack.maxProfit = maxProfit;
    iKnapsack.solution = solution;
    
    return 0;
}

//Function to solve 0/1 knapsack problem using greedy method 3. i.e. Maximum Wight First
int SolutionByGreedy3(Knapsack &iKnapsack)
{
    vector<Item> listSorted = iKnapsack.listItems;
    //Sort the list based on greater weight first basis
    sort(listSorted.begin(), listSorted.end(), HasGreaterWeight);
    
    int weight = 0 , maxProfit = 0;
    vector<bool> solution(iKnapsack.nbItems,false);
    for (Item item : listSorted)
    {
        if (weight + item.weight <= iKnapsack.maxWeight)//check if it is not exceeding the knapsack capacity
        {
            //if not exceeding then add weight and profit
            solution[item.itemNum] = true;
            weight += item.weight;
            maxProfit += item.profit;
        }
    }
    
    iKnapsack.totalWeight = weight;
    iKnapsack.maxProfit = maxProfit;
    iKnapsack.solution = solution;
    
    return 0;
}

//Function to solve 0/1 knapsack problem using greedy method 4. i.e. Max Benefit Per Unit Item First
int SolutionByGreedy4(Knapsack &iKnapsack)
{
    vector<Item> listSorted = iKnapsack.listItems;
    //Sort the list based on greater benefit/weight ratio first basis
    sort(listSorted.begin(), listSorted.end(), HasGreterProfitPerUnit);
    
    int weight = 0 , maxProfit = 0;
    vector<bool> solution(iKnapsack.nbItems,false);
    for (Item item : listSorted)
    {
        if (weight + item.weight <= iKnapsack.maxWeight)//check if item is not exceeding the knapsack capacity
        {
            //if not exceeding then add weight and profit
            solution[item.itemNum] = true;
            weight += item.weight;
            maxProfit += item.profit;
        }
    }
    
    iKnapsack.totalWeight = weight;
    iKnapsack.maxProfit = maxProfit;
    iKnapsack.solution = solution;
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
        
        cout << "\nSolution of Knapsack Problem Greedy Method 1 -> Maximum Benefit First"<< endl;
        cout << "-----------------------------------------------------" <<endl;
        
        SolutionByGreedy1(knapsack);
        PrintKnapsack(knapsack);
        
        cout <<"\nSolution of Knapsack Problem Greedy Method 2 -> Minimum Weight First"<< endl;
        cout << "-----------------------------------------------------" <<endl;

        
        SolutionByGreedy2(knapsack);
        PrintKnapsack(knapsack);
        
        cout << "\nSolution of Knapsack Problem Greedy Method 3 -> Maximum Weight First"<< endl;
        cout << "-----------------------------------------------------" <<endl;

        
        SolutionByGreedy3(knapsack);
        PrintKnapsack(knapsack);
        
        cout << "\nSolution of Knapsack Problem Greedy Method 4 -> Max Benefit Per Unit Item First"<< endl;
        cout << "-----------------------------------------------------" <<endl;

        
        SolutionByGreedy4(knapsack);
        PrintKnapsack(knapsack);
        
    }
    return 0;
}

