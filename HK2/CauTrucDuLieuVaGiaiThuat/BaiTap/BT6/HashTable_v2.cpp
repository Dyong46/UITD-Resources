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

// Buoc 3: Dinh nghia cau truc Hashtable
const int Size = 5;
struct Hashtable
{
	struct Bucket
	{
		Node *pHead;
		Node *pTail;
	};

	Bucket buckets[Size];
	int size;
};

typedef Hashtable HT;

// Buoc 4: Khoi tao Hashtable
void initHashtable(Hashtable &h)
{
	for (int i = 0; i < Size; i++)
	{
		h.buckets[i].pHead = NULL;
		h.buckets[i].pTail = NULL;
	}
}

void initHashtable(Hashtable &h, int size)
{
	for (int i = 0; i < size; i++)
	{
		h.buckets[i].pHead = NULL;
		h.buckets[i].pTail = NULL;
	}
	h.size = size;
}

int hashFunc(int value)
{
	return value % Size;
}

int hashFunc(Node *p)
{
	return p->data % Size;
}

void add(Hashtable &h, Node *p)
{
	int viTri = hashFunc(p);

	if (h.buckets[viTri].pHead == NULL)
	{
		h.buckets[viTri].pHead = p;
		h.buckets[viTri].pTail = p;
	}
	else
	{
		h.buckets[viTri].pTail->pNext = p;
		h.buckets[viTri].pTail = p;
	}
}

void add(Hashtable &h, int value)
{
	int viTri = hashFunc(value);

	Node *p = initNode(value);

	if (h.buckets[viTri].pHead == NULL)
	{
		h.buckets[viTri].pHead = p;
		h.buckets[viTri].pTail = p;
	}
	else
	{
		h.buckets[viTri].pTail->pNext = p;
		h.buckets[viTri].pTail = p;
	}
}

int initDataHashtable(Hashtable &h)
{
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

	add(h, 28);
	add(h, 90);
	add(h, 21);
	add(h, 53);
	add(h, 13);

	return 9;
}

// 2. In bang bam
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

/* 3. Viet ham tao du lieu cho bang bam tu mang 1 chieu
Input:
	+ HT& h
	+ int a[]
	+ int n
Output:
	+ HT& h
*/
void initDataHTArr(HT &h, int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		add(h, a[i]);
	}
}

/* 5. Viết hàm tìm một giá trị trong bảng băm.
Input:
	+ HT h
	+ int value
Output:
	+ return bool
*/
bool timGiaTri(HT h, int value)
{
	int vt = hashFunc(value);
	for(Node* p = h.buckets[vt].pHead; p != NULL; p = p->pNext)
	{
		if(p->data == value) {
			return true;
		}
	}
	return false;
}

int main()
{
	Hashtable h;
	// Custom add size to initHashtable to init Size Hashtable
	initHashtable(h);

	cout << "Test: 1. Tao du lieu: " << endl;
	int soLuong = initDataHashtable(h);
	cout << "\t+ Ket qua: " << soLuong << endl;

	cout << "\nTest: 2. In mang bam: " << endl;
	printHashtable(h);

	cout << "\nTest: 3. Tao du lieu tu mang 1 chieu: " << endl;
	int a[] = {1, 7, 90, 56, 23, 78};
	int n = 6;
	initDataHTArr(h, a, n);
	printHashtable(h);

	cout << "\nTest: 5. Tim gia tri:" << endl;
	cout << "\t+ Ket qua tim 53(1): " << timGiaTri(h, 53) << endl;
	cout << "\t+ Ket qua tim 91(0): " << timGiaTri(h, 91) << endl;

	return 0;
}