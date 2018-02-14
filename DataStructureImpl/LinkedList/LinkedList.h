#pragma once
#include "Node.h"
#include <stdio.h>

class LinkedList
{

public:
	LinkedList();
	~LinkedList();
	void Append(int iData);
	void InsertAt(int iData, int iIndex);
	void DeleteAt(int iIndex);
	void Reverse();

	void Print();


private:
	Node * _pRootNode;
	
};

