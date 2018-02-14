#include "Node.h"
#include <stdio.h>
using namespace std;


Node::Node():_data(0),_pNextNode(NULL)
{
}

Node::Node(int iData):_data(iData),_pNextNode(NULL)
{
}


Node::~Node()
{
}

Node * Node::GetNext()
{
	return _pNextNode;
}

int Node::GetData()
{
	return _data;
}

void Node::SetNext(Node * ipNode)
{
	_pNextNode = ipNode;
}

void Node::SetData(int iData)
{
	_data = iData;
}
