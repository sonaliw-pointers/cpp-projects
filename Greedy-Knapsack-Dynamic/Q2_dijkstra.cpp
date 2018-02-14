
using namespace std;
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<queue>
#include<list>

#define INF 9999
struct Node {
    int index = -1;
    int minDistance = INF;
    vector<int> shortestPath;
};

//Read input file
int ReadInputFile(ifstream & iFile, vector<vector<int>> &iGraph)
{
    int ret = 0;
    if (iFile.good() && iFile.is_open())
    {
        string line;
        while (getline(iFile, line))//read the whole matrix
        {
            vector<int> row;
            
            istringstream buffer(line);
            while (getline(buffer, line, ','))
            {
                istringstream buffer(line);
                int weight = 0;
                buffer >> weight;
                row.push_back(weight);
            }
            
            iGraph.push_back(row);
        }
    }
    return ret;
}

//Comparator for priority queue
class NodeCompare
{
    bool reverse;
public:
    NodeCompare(const bool& revparam = false)
    {
        reverse = revparam;
    }
    bool operator() (const Node *lhs, const Node *rhs) const
    {
        if (reverse) return (lhs->minDistance > rhs->minDistance);
        else return (lhs->minDistance < rhs->minDistance);
    }
};


typedef std::priority_queue<Node*, std::vector<Node*>, NodeCompare> prio_queue;//Priority queue  as minHeap
int Dijkstra(vector<vector<int>> &iGraph, int iSource, vector<Node*> & iListNodes)
{
    int curSource = iSource;
    iListNodes[curSource]->minDistance = 0;
    
    prio_queue toVisitPQ(iListNodes.begin(), iListNodes.end(),NodeCompare(true));
    while (!toVisitPQ.empty())
    {
        Node* curNode = toVisitPQ.top();
        curSource = curNode->index;
        vector<int> currentRow = iGraph[curSource];
        int distOfCurrent = iListNodes[curSource]->minDistance;
        for (size_t i = 0; i < currentRow.size(); i++)
        {
            if (0 < currentRow[i])
            {
                int dist = distOfCurrent + currentRow[i];
                if (iListNodes[i]->minDistance > dist)//if distance is less update the new distnace
                {
                    iListNodes[i]->minDistance = dist;
                    iListNodes[i]->shortestPath = iListNodes[curSource]->shortestPath;
                    iListNodes[i]->shortestPath.push_back(curSource);
                }
            }
            
        }
        
        toVisitPQ.pop();//Pop minimum distance node
    }
    
    return 0;
}
// Print each node and it's path from source
int PrintOutput(vector<Node*> list, int source)
{
    cout << "Source Node : " << source << endl;
    for (auto node : list)
    {
        int dist = -99;
        if(node->minDistance != INF) {
            dist = node->minDistance;
        }
        cout << "" << node->index << ", Distance : " << dist ;
        if (INF != node->minDistance)
        {
            cout << "\t\tPath : ";
            for (auto i : node->shortestPath)
            {
                cout << i << " - ";
            }
            cout << node->index << endl;
        }
        else
        {
            cout << "\tNo path found " << endl;
        }
    }
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
        
        vector<vector<int>> graph;
        ReadInputFile(inputFile, graph);
        inputFile.close();
        
        vector<Node*>listNodes;
        for (int i = 0; i < graph.size(); i++)
        {
            Node *pNode = new Node;
            pNode->index = i;
            listNodes.push_back(pNode);
        }
        int source = 0;
        Dijkstra(graph, source, listNodes);
        PrintOutput(listNodes, source);
        
        for(auto node:listNodes)
        {
            delete node; node = NULL;
        }
        listNodes.empty();
    }
    return 0;
}

