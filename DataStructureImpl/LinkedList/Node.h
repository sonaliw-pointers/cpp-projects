#pragma once
class Node
{
public:
	Node();
	Node(int iData);
	~Node();
	Node * GetNext();
	int GetData();
	void SetNext(Node * ipNode);
	void SetData(int iData);
private:
	int _data;
	Node * _pNextNode;
};

