#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList()
{
	// Ctor, clear all data without printing anything
	m_bPrintLog = false;
	m_bPrintListAlways = false;

	Clear();
}

DoubleLinkedList::~DoubleLinkedList()
{
	// Dtor, clear all data without printing anything
	m_bPrintLog = false;
	m_bPrintListAlways = false;

	Clear();
}

void DoubleLinkedList::Clear()
{
	if (m_bPrintLog)
	{
		std::cout << "CLEAR" << std::endl;
	}

	// Delete all the nodes
	while (m_pHead)
	{
		if (m_pHead->pNext)
		{
			// If the head has the next item, it will be our new head,
			// and we delete the former head and nullptr it.
			m_pHead = m_pHead->pNext;
			delete m_pHead->pPrev;
			m_pHead->pPrev = nullptr;
		}
		else
		{
			// If the head is the only item left, delete it and nullptr it.
			delete m_pHead;
			m_pHead = nullptr;
		}
	}

	m_pTail = nullptr;
	m_Size = 0;

	if (m_bPrintListAlways)
	{
		Print();
	}
}

auto DoubleLinkedList::IsEmpty() const->bool
{
	// Return true if the list is empty
	return m_pHead == nullptr;
}

void DoubleLinkedList::Push(DATA_TYPE Data)
{
	if (m_bPrintLog)
	{
		std::cout << "PUSH <" << Data << ">" << std::endl;
	}

	if (IsEmpty())
	{
		// If the list is empty, create a new head, which is also the tail
		m_pHead = new Node(Data);
		m_pTail = m_pHead;
	}
	else
	{
		// If the list already exists, Just add a new tail
		m_pTail->pNext = new Node(Data, m_pTail);
		m_pTail = m_pTail->pNext;
	}

	m_Size++;

	if (m_bPrintListAlways)
	{
		Print();
	}
}

void DoubleLinkedList::Pop()
{
	if (m_bPrintLog)
	{
		if (IsEmpty())
		{
			std::cout << "POP FAILED (EMPTY LIST)" << std::endl;
			return;
		}
		else
		{
			std::cout << "POP" << std::endl;
		}
	}

	if (m_pHead == m_pTail)
	{
		// Popping the tail, which is also the head
		// So we just clear the list
		Clear();
	}
	else
	{
		// Popping the tail, which is not the head
		// Our new tail is the previous node of the current tail
		m_pTail = m_pTail->pPrev;
		delete m_pTail->pNext;
		m_pTail->pNext = nullptr;
		m_Size--;
	}

	if (m_bPrintListAlways)
	{
		Print();
	}
}

void DoubleLinkedList::Insert(size_t ID, DATA_TYPE Data)
{
	// Limitting the ID between (0) to (m_Size)
	// We're not limiting the maximum ID to (m_Size - 1),
	// because you can insert a new item after the currrent tail
	ID = max(ID, 0);
	ID = min(ID, m_Size);

	if (m_bPrintLog)
	{
		std::cout << "INSERT <" << Data << "> AT [" << ID << "]" << std::endl;
	}

	if (IsEmpty())
	{
		// If the list is empty, Insert() is the same as Push()

		if (m_bPrintLog)
		{	
			m_bPrintLog = false;
			Push(Data);
			m_bPrintLog = true;
		}
		else
		{
			Push(Data);
		}

		return;
	}

	if (ID == 0)
	{
		// The head changes
		m_pHead->pPrev = new Node(Data, nullptr, m_pHead);
		m_pHead = m_pHead->pPrev;
	}
	else if (ID == m_Size)
	{
		// The tail changes
		m_pTail->pNext = new Node(Data, m_pTail);
		m_pTail = m_pTail->pNext;
	}
	else
	{
		// One of the middle items changes
		Node* iterator = m_pHead;
		size_t iterator_count = 0;

		while (iterator)
		{
			if (iterator_count == ID)
			{
				iterator->pPrev = new Node(Data, iterator->pPrev, iterator);
				iterator->pPrev->pPrev->pNext = iterator->pPrev;
				break;
			}
			iterator = iterator->pNext;
			iterator_count++;
		}
	}

	m_Size++;

	if (m_bPrintListAlways)
	{
		Print();
	}
}

void DoubleLinkedList::Erase(size_t ID)
{
	// Limitting the ID between (0) to (m_Size - 1)
	ID = max(ID, 0);
	ID = min(ID, m_Size - 1);
	
	if (m_bPrintLog)
	{
		if (IsEmpty())
		{
			std::cout << "ERASE [" << ID << "] FAILED (EMPTY LIST)" << std::endl;
			return;
		}
		else
		{
			std::cout << "ERASE [" << ID << "]" << std::endl;
		}
	}
		
	if (ID == 0)
	{
		// The head changes
		m_pHead = m_pHead->pNext;
		delete m_pHead->pPrev;
		m_pHead->pPrev = nullptr;
	}
	else if (ID == m_Size - 1)
	{
		// The tail changes
		m_pTail = m_pTail->pPrev;
		delete m_pTail->pNext;
		m_pTail->pNext = nullptr;
	}
	else
	{
		// One of the middle items changes
		Node* iterator = m_pHead;
		size_t iterator_count = 0;

		while (iterator)
		{
			if (iterator_count == ID)
			{
				iterator->pPrev->pNext = iterator->pNext;
				iterator->pNext->pPrev = iterator->pPrev;
				delete iterator;
				iterator = nullptr;
				break;
			}
			iterator = iterator->pNext;
			iterator_count++;
		}
	}

	m_Size--;

	if (m_bPrintListAlways)
	{
		Print();
	}
}

void DoubleLinkedList::SetItem(size_t ID, DATA_TYPE Data)
{
	// Limitting the ID between (0) to (m_Size - 1)
	ID = max(ID, 0);
	ID = min(ID, m_Size - 1);

	if (m_bPrintLog)
	{
		if (IsEmpty())
		{
			std::cout << "SETITEM [" << ID << "] <" << Data << "> FAILED (EMPTY LIST)" << std::endl;
			return;
		}
		else
		{
			std::cout << "SETITEM [" << ID << "] <- <" << Data << ">" << std::endl;
		}
	}

	Node* iterator = m_pHead;
	size_t iterator_id = 0;

	while (iterator)
	{
		if (iterator_id == ID)
		{
			iterator->Data = Data;
			break;
		}
		iterator = iterator->pNext;
		iterator_id++;
	}

	if (m_bPrintListAlways)
	{
		Print();
	}
}

auto DoubleLinkedList::GetItem(size_t ID) const->DATA_TYPE
{
	// Limitting the ID between (0) to (m_Size - 1)
	ID = max(ID, 0);
	ID = min(ID, m_Size - 1);

	if (m_bPrintLog)
	{
		if (IsEmpty())
		{
			std::cout << "GETITEM [" << ID << "] FAILED (EMPTY LIST)" << std::endl << std::endl;
			return DATA_NULL;
		}
		else
		{
			std::cout << "GETITEM [" << ID << "]";
		}
	}

	Node* iterator = m_pHead;
	size_t iterator_id = 0;

	while (iterator)
	{
		if (iterator_id == ID)
		{
			if (m_bPrintLog)
			{
				std::cout << " -> <" << iterator->Data << ">" << std::endl << std::endl;
			}
			return iterator->Data;
		}
		iterator = iterator->pNext;
		iterator_id++;
	}

	return DATA_NULL;
}

auto DoubleLinkedList::GetSize() const->size_t
{
	return m_Size;
}

void DoubleLinkedList::Print() const
{
	// Print the list length and all the items' data
	std::cout << " # LIST (LENGTH = " << m_Size << ") => ";

	Node* iterator = m_pHead;
	while (iterator)
	{
		std::cout << "<" << iterator->Data << "> ";
		iterator = iterator->pNext;
	}
	std::cout << std::endl << std::endl;
}

void DoubleLinkedList::WillPrintLog(bool Value)
{
	m_bPrintLog = Value;
}

void DoubleLinkedList::WillPrintListAlways(bool Value)
{
	m_bPrintListAlways = Value;
}