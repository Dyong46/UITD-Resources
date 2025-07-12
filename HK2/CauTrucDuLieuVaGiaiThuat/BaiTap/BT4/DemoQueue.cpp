#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node *pNext;
};

Node* initNode(int value)
{
	Node *p = new Node;

	if (p == NULL)
	{
		cout << "Khong du bo nho de cap phat" << endl;
		return NULL;
	}

	p->data = value;
	p->pNext = NULL;

	return p;
}


struct Queue
{
	Node* pFront;
	Node* pRear;
};

// Buoc 4: Tao hang doi
void initQueue(Queue &q)
{
	q.pFront = NULL;
	q.pRear = NULL;
};

void enQueue(Queue &q, Node *p)
{
	if (q.pFront == NULL)
	{
		q.pFront = p;
		q.pRear = p;
	}
	else
	{
		q.pRear->pNext = p;
		q.pRear = p;
	}
};

bool deQueue(Queue &q)
{
	if (q.pFront == NULL)
	{
		return false;
	}

	Node *p = q.pFront;
	q.pFront = q.pFront->pNext;
	delete p;

	if (q.pFront == NULL)
	{
		q.pRear = NULL;
	}

	return true;
};

void printfQueue(Queue q)
{
	if (q.pFront == NULL)
	{
		cout << "Hang doi rong" << endl;
		return;
	}

	cout << "<<Front<< ";
	for (Node *p = q.pFront; p != NULL; p = p->pNext)
	{
		cout << p->data << " ";
	}
	cout << "<<Rear<<" << endl << endl;
}

int main()
{
	Queue q;
	initQueue(q);

	enQueue(q, initNode(45));
	enQueue(q, initNode(78));
	enQueue(q, initNode(12));

	printfQueue(q);

	deQueue(q);
	printfQueue(q);

	return 0;
}