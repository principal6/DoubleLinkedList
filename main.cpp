#include "DoubleLinkedList.h"

int main()
{
	DoubleLinkedList myList;

	myList.WillPrintLog(true);
	myList.WillPrintListAlways(true);

	myList.Push(1);
	myList.Push(3);
	myList.Push(5);

	myList.Clear();

	myList.Push(7);
	myList.Push(9);
	myList.Push(11);
	myList.Push(13);
	
	myList.Pop();
	myList.Pop();

	myList.Insert(0, 0);
	myList.Insert(2, 2);
	myList.Insert(13, 99);

	myList.Erase(3);

	myList.SetItem(1, 27);
	DATA_TYPE find = myList.GetItem(13);

	system("pause");
	return 0;
}