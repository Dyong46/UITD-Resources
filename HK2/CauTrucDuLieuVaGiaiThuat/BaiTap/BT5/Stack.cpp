#include <iostream>

using namespace std;

// Buoc 1: Dinh nghia cau truc Node va Stack
struct Node
{
	float data;
	Node *pNext;
};

struct Stack
{
	Node *pTop;
};

// Buoc 2: Viet ham khoi tao Node va Stack
Node *initNode(float value)
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

void initStack(Stack &s)
{
	s.pTop = NULL;
}

/* Buoc 3: Viet ham day kiem tra Stack rong
Input:
	+ l: Stack&
Output:
	+ return: boolean
*/
bool isEmpty(Stack &s)
{
	return s.pTop == NULL;
}

/* Buoc 3: Viet ham kiem tra Stack co full hay khong (optional)
Input:
	+ l: Stack&
Output:
	+ return: boolean
*/
bool isFullStack(Stack &s)
{

	return true;
}

/* Buoc 5: Viet ham day mot phan tu vao Stack
Input:
	+ l: Stack&
	+ p: Node*
Output:
	+ l: Stack&
 */
void push(Stack &s, Node *p)
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

/* Buoc 5: Viet ham day mot phan tu vao Stack
Input:
	+ l: Stack&
	+ value: float
Output:
	+ l: Stack&
 */
void push(Stack &s, float value)
{
	Node *p = initNode(value);

	if (p == NULL)
	{
		return;
	}

	push(s, p);
}

/* Buoc 6: Viet ham lay mot phan tu ra khoi Stack
Input:
	+ l: Stack&
Output:
	+ l: Stack&
	+ return: bool
 */
bool pop(Stack &s)
{
	if (s.pTop == NULL)
	{
		return false;
	}

	Node *p = s.pTop;
	s.pTop = s.pTop->pNext;

	delete p;
	return true;
}

/* Buoc 7: Lay gia tri phan tu Top cua Stack
Input:
	+ s: Stack&
	+ value: float&
Output:
	+ return: boolean
*/
bool getTopValue(Stack &s, float &value)
{
	if (s.pTop == NULL)
	{
		return false;
	}

	value = s.pTop->data;
	return true;
}

/* Buoc 7: Lay gia tri phan tu Top cua Stack
Input:
	+ l: Stack&
Output:
	+ return: float
 */
void printStack(Stack s)
{

	cout << endl;
	cout << "Stack: ";
	if (s.pTop == NULL)
	{
		cout << "Stack rong" << endl;
		return;
	}
	Node *p = s.pTop;

	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->pNext;
	}

	cout << endl;
}

int main()
{
	Stack s;
	initStack(s);

	while (1)
	{
		cout << endl
				 << "========== Menu ==========" << endl;
		cout << "1. Kiem tra Stack rong" << endl;
		cout << "2. Kiem tra Stack full khong" << endl;
		cout << "3. Them phan tu vao Stack" << endl;
		cout << "4. Lay phan tu ra khoi Stack" << endl;
		cout << "5. Lay gia tri phan tu Top trong Stack" << endl;
		cout << "6. In ra Stack" << endl;
		cout << "7. Thoat" << endl;

		int choice;
		cout << "Nhap lua chon: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
		{
			if (isEmpty(s))
			{
				cout << "Stack rong" << endl;
			}
			else
			{
				cout << "Stack khong rong" << endl;
			}
			break;
		}
		case 2:
		{
			if (isFullStack(s))
			{
				cout << "Stack full" << endl;
			}
			else
			{
				cout << "Stack khong full" << endl;
			}
			break;
		}
		case 3:
		{
			float value;
			cout << "Nhap gia tri can them: ";
			cin >> value;

			Node *p = initNode(value);
			push(s, p);
			break;
		}
		case 4:
		{
			if (pop(s))
			{
				cout << "Lay phan tu thanh cong" << endl;
			}
			else
			{
				cout << "Lay phan tu khong thanh cong" << endl;
			}
			break;
		}
		case 5:
		{
			float topValue;
			if (getTopValue(s, topValue))
			{
				cout << "Phan tu Top: " << topValue << endl;
			}
			else
			{
				cout << "Khong lay duoc phan tu Top" << endl;
			}
			break;
		}
		case 6:
		{
			printStack(s);
			break;
		}
		case 7:
		{
			cout << "Thoat khoi chuong trinh" << endl;
			return 0;
		}
		default:
			break;
		}
	}
	return 0;
}