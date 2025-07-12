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
		return -1;
	}

	return s.pTop->data;
}

void move(Stack &s1, Stack &s2, int &count)
{
	if (s1.pTop == NULL)
	{
		return;
	}

	if (s2.pTop != NULL && getTop(s1) > getTop(s2))
	{
		cout << "Khong the chuyen dia nay!" << endl;
		return;
	}

	int top = getTop(s1);
	pop(s1);
	push(s2, top);
	count++;
}

void createTower(Stack &s1, int n)
{
	for (int i = n; i >= 1; i--)
	{
		push(s1, i);
	}
}

int main()
{
	Stack s1;
	initStack(s1);

	Stack s2;
	initStack(s2);

	Stack s3;
	initStack(s3);

	int count = 0;

	while(1) {
		cout << endl;
		cout << "============= DEMO STACK =============" << endl;
		cout << "\t 0. Create Tower." << endl;
		cout << "\t 1. A -> B." << endl;
		cout << "\t 2. A -> C." << endl;
		cout << "\t 3. B -> A." << endl;
		cout << "\t 4. B -> C." << endl;
		cout << "\t 5. C -> A." << endl;
		cout << "\t 6. C -> B." << endl;
		cout << "\t 7. Exit." << endl; 
		cout << "=======================================" << endl;

		cout << "\tStack A: ";
		printStack(s1);
		cout << endl << "=======================================" << endl;

		cout << "\tStack B: ";
		printStack(s2);
		cout << endl << "=======================================" << endl;

		cout << "\tStack C: ";
		printStack(s3);
		cout << endl << "=======================================" << endl;

		cout << "\tInput: ";
		int chon;
		cin >> chon;
		cout << endl << endl;

		switch (chon)
		{
		case 0:
			int n;
			cout << "Nhap so dia: ";
			cin >> n;
			createTower(s1, n);
			cout << "Da tao xong Tower!" << endl;
			break;
		case 1:
			move(s1, s2, count);
			break;
		case 2:
			move(s1, s3, count);
			break;
		case 3:
			move(s2, s1, count);
			break;
		case 4:
			move(s2, s3, count);
			break;
		case 5:
			move(s3, s1, count);
			break;
		case 6:
			move(s3, s2, count);
			break;
		case 7:
			return 0;
		default:
			break;
		}
	}

	return 0;
}