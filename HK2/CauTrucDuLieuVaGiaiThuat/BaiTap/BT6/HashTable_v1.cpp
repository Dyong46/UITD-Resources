#include <iostream>

using namespace std;

// Buoc 1: Dinh nghia cau truc Node
struct Node
{
	int data;
	Node *pNext;
};

// Buoc 2: Cap phat dong Node de luu gia tri can luu
Node *initNode(int value)
{
	Node *p = new Node;

	p->data = value;
	p->pNext = NULL;

	return p;
};

// Buoc 3: Dinh nghia Bucket
struct Bucket
{
	Node *pHead;
	Node *pTail;
};

// Buoc 4: Khoi tao Bucket
void initBucket(Bucket &bk)
{
	bk.pHead = NULL;
	bk.pTail = NULL;
};

// Buoc 5: Dinh nghia kieu Hashtable
const int Size = 5;
struct Hashtable
{
	Bucket buckets[Size];
};

// Buoc 6: Khoi tao Hashtable
void initHashtable(Hashtable &h)
{
	for (int i = 0; i < Size; i++)
	{
		initBucket(h.buckets[i]);
	}
};

int hashFunc(int value)
{
	return value % Size;
};

int hashFunc(Node *p)
{
	return p->data % Size;
};

void push(Bucket &bk, Node *p)
{
	if (bk.pHead == NULL)
	{
		cout << "push" << p->data << endl;
		bk.pHead = p;
		bk.pTail = p;
	}
	else
	{
		cout << "push" << p->data << endl;
		bk.pTail->pNext = p;
		bk.pTail = p;
	}
};

void add(Hashtable &h, Node *p)
{
	// B1: Tinh vi tri bucket
	int viTri = hashFunc(p);
	// B2: push vao bucket da xac dinh
	push(h.buckets[viTri], p);

	// Cach goi bucket h.bucket[viTri]
	// if(h.buckets[viTri].pHead == NULL)
	// {
	// 	h.buckets[viTri].pHead = p;
	// 	h.buckets[viTri].pTail = p;
	// }
};

void add(Hashtable &h, int value)
{
	// B1: Tinh vi tri bucket
	int viTri = hashFunc(value);
	cout << value << ", " << viTri << endl;

	// B2: push vao bucket da xac dinh
	push(h.buckets[viTri], initNode(value));
};

void printHashtable(Hashtable h)
{
	cout << "Size of Hashtable: " << Size << endl;

	for (int i = 0; i < Size; i++)
	{
		cout << "Bucket[" << i << "]: ";

		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			cout << p->data << "\t";
		}
		cout << endl;
	}
}

int main()
{
	Hashtable h;
	initHashtable(h);

	// 50 73 35 36 64 28 90 21 53 13
	Node *p1 = initNode(50);
	Node *p2 = initNode(73);
	Node *p3 = initNode(35);
	Node *p4 = initNode(36);
	Node *p5 = initNode(64);

	add(h, p1);
	add(h, p2);
	add(h, p3);
	add(h, p4);
	add(h, p5);

	add(h, 90);
	add(h, 21);
	add(h, 53);
	add(h, 13);

	printHashtable(h);

	return 0;
}