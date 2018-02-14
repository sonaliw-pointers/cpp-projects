#pragma once
#include "stdafx.h"
#include "Node.h"
#include <queue>

// compaeator class
class NodeComparator
{
public:
	bool operator()(Node *ipRightNode , Node *ipLeftNode);
};
// node priority_queue
typedef priority_queue<Node *, vector<Node *>, NodeComparator> NodePriorityQ;
