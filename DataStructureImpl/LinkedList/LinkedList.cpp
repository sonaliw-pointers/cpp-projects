#include "LinkedList.h"
#include <iostream>
#include <list>
using namespace std;


LinkedList::LinkedList()
{
}


LinkedList::~LinkedList()
{
	Node* pCurrentNode = _pRootNode;
	Node* pPrevNode = NULL;


	while (NULL != pCurrentNode)
	{
		pPrevNode = pCurrentNode;
		pCurrentNode = pCurrentNode->GetNext();
		delete pPrevNode;
	}
}

void LinkedList::Append(int iData)
{
	Node * pNewNode = new Node(iData);
	Node* pCurrentNode = _pRootNode;
	Node* pPrevNode = _pRootNode;

	if (NULL == pCurrentNode)
	{
		_pRootNode = pNewNode;
		return;
	}

	while (pCurrentNode = pCurrentNode->GetNext())
	{
		pPrevNode = pCurrentNode;
	}

	pPrevNode->SetNext(pNewNode);
}

void LinkedList::InsertAt(int iData, int iIndex)
{
	int count = 0;
	Node * pNewNode = new Node(iData);
	Node *pCurrentNode = _pRootNode;
	Node* pNextNode = NULL;

	while (iIndex > count)
	{
		if (NULL != pCurrentNode)
		{
			pCurrentNode = pCurrentNode->GetNext();
			count++;
		}
	}
	pNewNode->SetNext(pCurrentNode->GetNext());
	pCurrentNode->SetNext(pNewNode);
}

void LinkedList::DeleteAt(int iIndex)
{
	int count = 0;
	Node *pCurrentNode = _pRootNode;
	Node* pPrevNode = NULL;

	while (iIndex > count)
	{
		if (NULL != pCurrentNode)
		{
			pPrevNode = pCurrentNode;
			pCurrentNode = pCurrentNode->GetNext();
			count++;
		}
	}

	if (pPrevNode)
	{
		pPrevNode->SetNext(pCurrentNode->GetNext());
	}
}

void LinkedList::Reverse()
{
	if (_pRootNode)
	{
		Node *pTempNode = new Node();
		//pTempNode->SetNext(_pRootNode);

		Node *pCurrentNode = _pRootNode;
		Node *pNextNode = NULL;
		Node *pPrevNode = NULL;

		while (pCurrentNode)
		{
			pNextNode = pCurrentNode->GetNext();

			pCurrentNode->SetNext(pTempNode->GetNext());
			pTempNode->SetNext(pCurrentNode);

			pCurrentNode = pNextNode;
		}

		_pRootNode = pTempNode->GetNext();
		delete pTempNode;
		pTempNode = NULL;
	}
	
}

void LinkedList::Print()
{
	Node *pCurrentNode = _pRootNode;

	while (NULL != pCurrentNode)
	{
		cout << pCurrentNode->GetData();
		pCurrentNode = pCurrentNode->GetNext();
	}
	cout << endl;
}

int main()
{
	LinkedList *pList = new LinkedList();
	// STL 
	list<int> *pSTLList = new list<int>();

	for (int i = 0; i < 5; i++)
	{
		/*int data = 0;
		cin >> data;*/
		pList->Append(i);
		pSTLList->push_back(i);
	}
	pList->Print();

	pList->InsertAt(4, 4);
	pList->Print();


	pList->DeleteAt(4);
	pList->Print();

	pList->Reverse();
	pList->Print();

	delete pList;
	pList = NULL;


	

}
