#include <iostream>

using namespace std;

// Buoc 1: Dinh nghia cau truc Node
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

struct Stack
{
	Node* pTop;
};

void initStack (Stack &s)
{
	s.pTop = NULL;
}

void push(Stack &s, Node* p)
{
	if (s.pTop == NULL)
	{
		s.pTop = p;
	}
	else
	{
		p->pNext = s.pTop;
		s.pTop = p;
	}
}

void push(Stack &s, int value)
{
	Node* p = initNode(value);

	if (p == NULL)
	{
		return;
	}

	push(s, p);
}

void printStack(Stack s)
{
	Node* p = s.pTop;

	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->pNext;
	}
}

void pop(Stack &s)
{
	if (s.pTop == NULL)
	{
		return;
	}

	Node* p = s.pTop;
	s.pTop = s.pTop->pNext;

	delete p;
}

int getTop(Stack s)
{
	if(s.pTop == NULL) 
	{
		return NULL;
	}

	return s.pTop->data;
}

int main()
{
	Stack s;
	initStack(s);

	Node* p1 = initNode(10);
	Node* p2 = initNode(79);
	Node* p3 = initNode(39);

	push(s, p1);
	push(s, p2);
	push(s, p3);

	return 0;
}