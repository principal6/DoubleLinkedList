#include "DoubleLinkedList.h"

int main()
{
	DoubleLinkedList<int*> myList;

	myList.WillPrintLog(true);
	myList.WillPrintListAlways(true);

	int a = 1;
	int b = 3;
	int c = 5;

	myList.Push(&a);
	myList.Push(&b);
	myList.Push(&c);
	
	myList.Pop();
	myList.Pop();

	myList.Insert(0, &a);
	myList.Insert(2, &b);
	myList.Insert(13, &c);

	myList.Erase(3);

	myList.Pop();
	myList.Pop();
	myList.Pop();

	auto find = myList.GetItem(13);

	system("pause");
	return 0;
}