#pragma once

#include <iostream>

#define max(a, b) {a > b? a : b};
#define min(a, b) {a < b? a : b};

using DATA_TYPE = int;
static const DATA_TYPE DATA_NULL = 0;

class DoubleLinkedList
{
protected:
	struct Node
	{
		Node* pPrev;
		Node* pNext;
		DATA_TYPE Data;

		Node() : pNext(nullptr), pPrev(nullptr), Data(DATA_NULL) {};
		Node(DATA_TYPE _Data) : pNext(nullptr), pPrev(nullptr), Data(_Data) {};
		Node(DATA_TYPE _Data, Node* _pPrev) : pNext(nullptr), pPrev(_pPrev), Data(_Data) {};
		Node(DATA_TYPE _Data, Node* _pPrev, Node* _pNext) : pNext(_pNext), pPrev(_pPrev), Data(_Data) {};
	};

	Node* m_pHead;
	Node* m_pTail;
	size_t m_Size;

	bool m_bPrintLog;
	bool m_bPrintListAlways;

public:
	DoubleLinkedList();
	virtual ~DoubleLinkedList();

	virtual auto IsEmpty() const->bool;
	virtual auto GetSize() const->size_t;

	virtual void Clear(bool Silent = false);
	
	virtual void Push(DATA_TYPE Data);
	virtual void Pop();

	virtual void Insert(size_t ID, DATA_TYPE Data);
	virtual void Erase(size_t ID);

	virtual void SetItem(size_t ID, DATA_TYPE Data);
	virtual auto GetItem(size_t ID) const->DATA_TYPE;

	virtual void Print() const;

	virtual void WillPrintLog(bool Value);
	virtual void WillPrintListAlways(bool Value);
};