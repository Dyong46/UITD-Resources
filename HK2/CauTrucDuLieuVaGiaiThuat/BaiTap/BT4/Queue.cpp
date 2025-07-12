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

/* Cau 1: Viết hàm khởi tạo Queue
*/
void initQueue(Queue &q)
{
	q.pFront = NULL;
	q.pRear = NULL;
};

/* 2. Viết hàm kiểm tra Queue rỗng
Input:
	+ q: Queue
Output:
	+ return true: Queue rỗng
	+ return false: Queue không rỗng
*/
bool isEmpty(Queue q)
{
	return q.pFront == NULL;
};

/* 3. Viết hàm thêm phần tử vào Queue
Input:
	+ q: Queue&
	+ p: Node
Output:
	+ q: Queue&
*/
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

/* 4. Viết hàm lấy phần tử ra khỏi Queue
Input:
	+ q: Queue&
Output:
	+ return true: Lấy phần tử thành công
	+ return false: Lấy phần tử không thành công
*/
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

/* 5. Viết hàm in ra phần tử REAR và FRONT của Queue
Input:
	+ q: Queue
Output:
	+ In ra phần tử REAR và FRONT của Queue
*/
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
	cout << "<<Rear<<" << endl;
}


/* 5. Trong hàm main, viết menu thể hiện các lựa chọn câu trên
*/
int main()
{
	Queue q;
	initQueue(q);

	while(true) {
		cout << endl << "========== Menu ==========" << endl;
		cout << "1. Kiem tra Queue rong" << endl;
		cout << "2. Them phan tu vao Queue" << endl;
		cout << "3. Lay phan tu ra khoi Queue" << endl;
		cout << "4. In ra phan tu REAR va FRONT cua Queue" << endl;
		cout << "5. Thoat" << endl;

		int choice;
		cout << "Nhap lua chon: ";
		cin >> choice;
		cout << endl;

		switch(choice) {
			case 1:
					if (isEmpty(q))
					{
							cout << "Queue rong" << endl;
					}
					else
					{
							cout << "Queue khong rong" << endl;
					}
					break;
			case 2:
			{
					int value;
					cout << "Nhap gia tri can them: ";
					cin >> value;
	
					Node *p = initNode(value);
					enQueue(q, p);
					break;
			}
			case 3:
					if (deQueue(q))
					{
							cout << "Lay phan tu thanh cong" << endl;
					}
					else
					{
							cout << "Lay phan tu khong thanh cong" << endl;
					}
					break;
			case 4:
					printfQueue(q);
					break;
			case 5:
					return 0;
			default:
					cout << "Lua chon khong hop le" << endl;
					break;
		}
	}

	return 0;
}