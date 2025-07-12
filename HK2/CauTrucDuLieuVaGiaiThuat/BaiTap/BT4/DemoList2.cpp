#include <iostream>

using namespace std;

// Buoc 1: Dinh nghia cua truc Node
struct Node
{
	int data;
	Node *pNext;
	Node *pPrev;
};

// Buoc 2: Cap phat dong Node de luu gia tri
Node *initNode(int value)
{
	Node *p = new Node;

	if (p == NULL)
	{
		cout << "Khong du bo nho de cap phat" << endl;
		return NULL;
	}

	p->data = value;
	p->pNext = NULL;
	p->pPrev = NULL;

	return p;
};

// Buoc 3: Dinh nghi List
struct List
{
	Node *pHead;
	Node *pTail;
};

// Buoc 4: Khoi tao List
void initList(List &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
};

void pushHead(List &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		p->pNext = l.pHead;
		l.pHead->pPrev = p;
		l.pHead = p;
	}
};

void pushTail(List &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		p->pPrev = l.pTail;
		l.pTail->pNext = p;
		l.pTail = p;
	}
};

void printfList(List l)
{
	cout << endl
			 << "In tu pHead den cuoi:" << endl;
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		cout << p->data << " ";
	}

	cout << endl
			 << "In tu pTail ve pHead:" << endl;
	for (Node *p = l.pTail; p != NULL; p = p->pPrev)
	{
		cout << p->data << " ";
	}

	cout << endl;
};

int main()
{
	// 10 -> 79 -> 39 -> 40 -> 50
	Node *p1 = initNode(10);
	Node *p2 = initNode(79);
	Node *p3 = initNode(39);

	List l;
	initList(l);

	pushHead(l, p1);
	pushTail(l, p2);
	pushTail(l, p3);

	pushHead(l, initNode(50));
	pushTail(l, initNode(26));

	printfList(l);

	return 0;
}