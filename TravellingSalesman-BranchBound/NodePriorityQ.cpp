#include "stdafx.h"
#include "NodePriorityQ.h"


bool NodeComparator::operator()(Node * ipRightNode, Node * ipLeftNode)
{
	return (*ipRightNode) > (*ipLeftNode);
}
