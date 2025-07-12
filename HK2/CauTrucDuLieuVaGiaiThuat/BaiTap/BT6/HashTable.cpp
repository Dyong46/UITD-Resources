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
struct Hashtable
{
	struct Bucket
	{
		Node *pHead;
		Node *pTail;
	};

	Bucket *buckets;
	int size;
};

// Buoc 4: Khoi tao Hashtable
void initHashtable(Hashtable &h, int size)
{
	h.size = size;
	h.buckets = new Hashtable::Bucket[size];
	for (int i = 0; i < size; i++)
	{
		h.buckets[i].pHead = NULL;
		h.buckets[i].pTail = NULL;
	}
}

int hashFunc(int value, int size)
{
	return value % size;
}

int hashFunc(Node *p, int size)
{
	return p->data % size;
}

void add(Hashtable &h, Node *p)
{
	int viTri = hashFunc(p, h.size);

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
	int viTri = hashFunc(value, h.size);

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

// Add destructor function to free memory
void deleteHashtable(Hashtable &h)
{
	for (int i = 0; i < h.size; i++)
	{
		Node *p = h.buckets[i].pHead;
		while (p != NULL)
		{
			Node *temp = p;
			p = p->pNext;
			delete temp;
		}
	}
	delete[] h.buckets;
}

/* Cau 1: Viêt hàm tạo dữ liệu dạng tự động cho bảng bặm. Các giá trị được chọn ngâu nhiên trong đoạn [856; 988]. Sổ lượng giá trị cần nhập |45; 95].
Input:
	+ HT& h
Output:
	+ HT& h
*/
void initDataHTAuto(Hashtable &h)
{
	int n = rand() % 51 + 45;

	for (int i = 0; i < n; i++)
	{
		int value = rand() % (988 - 856 + 1) + 856;
		add(h, value);
	}
}

/* Cau 2: Viết hàm tạo dữ liệu cho bảng băm từ mảng 1 chiều.
Input:
	+ HT& h
	+ int a[]
	+ int n
Output:
	+ HT& h
*/
void initDataHTArr(Hashtable &h, int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		add(h, a[i]);
	}
}

/* Cau 3: Viết hàm tạo dữ liệu dạng thủ công nhập từ bàn phím.
Input:
	+ HT& h
Output:
	+ HT& h
*/
void initDataHTManual(Hashtable &h)
{
	int n;
	cout << "Nhap so luong phan tu: ";
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int value;
		cout << "Nhap phan tu thu " << i + 1 << ": ";
		cin >> value;
		add(h, value);
	}
}

/* Cau 4: Viết hàm in bảng băm.
Input:
	+ HT h
Output:
*/
void printHashtable(Hashtable h)
{
	cout << "Size of Hashtable: " << h.size << endl;

	for (int i = 0; i < h.size; i++)
	{
		cout << "Bucket[" << i << "]: ";

		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			cout << p->data << "\t";
		}
		cout << endl;
	}
}

/* Cau 5: Viết hàm xóa giá trị trong bảng băm.
Input:
	+ HT& h
	+ int value
Output:
	+ HT& h
*/
void deleteValue(Hashtable &h, int value)
{
	int viTri = hashFunc(value, h.size);

	Node *p = h.buckets[viTri].pHead;
	Node *prev = NULL;

	while (p != NULL && p->data != value)
	{
		prev = p;
		p = p->pNext;
	}

	if (p == NULL)
	{
		cout << "Khong tim thay gia tri " << value << " trong bang băm." << endl;
		return;
	}

	if (prev == NULL)
	{
		h.buckets[viTri].pHead = p->pNext;
	}
	else
	{
		prev->pNext = p->pNext;
	}

	delete p;
	cout << "Da xoa gia tri " << value << " trong bang băm." << endl;
}

/* Cau 6: Viết hàm tìm một giá trị trong bảng băm.
Input:
	+ HT h
	+ int value
Output:
	+ return bool
*/
bool findValue(Hashtable h, int value)
{
	int viTri = hashFunc(value, h.size);

	for (Node *p = h.buckets[viTri].pHead; p != NULL; p = p->pNext)
	{
		if (p->data == value)
		{
			return true;
		}
	}
	return false;
}

/* Cau 7: Viết hàm tính tổng các giá trị lẻ trong bảng băm.
Input:
	+ HT h
Output:
	+ int sum
*/
int sumOddValues(Hashtable h)
{
	int sum = 0;

	for (int i = 0; i < h.size; i++)
	{
		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			if (p->data % 2 != 0)
			{
				sum += p->data;
			}
		}
	}

	return sum;
}

/* Cau 8: Viết hàm kiểm tra bảng băm có rỗng không.
Input:
	+ HT h
Output:
	+ bool isEmpty
*/
bool isEmpty(Hashtable h)
{
	for (int i = 0; i < h.size; i++)
	{
		if (h.buckets[i].pHead != NULL)
		{
			return false;
		}
	}
	return true;
}

/* Cau 9: Viêt hàm xử lý bảng băm theo một điêu kiện nào đó (ví dụ: chăn/lẻ, sô âm/dương, nguyên tô...) theo yêu câu người dùng (GV hướng dân trên lớp).
Tìm và in tất cả các giá trị thuộc một khoảng [a, b]
Input:
	+ HT h
	+ int a
	+ int b
Output:
	+ return HT
*/
Hashtable findInRange(Hashtable h, int a, int b)
{
	Hashtable result;
	initHashtable(result, h.size);

	for (int i = 0; i < h.size; i++)
	{
		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			if (p->data >= a && p->data <= b)
			{
				add(result, p->data);
			}
		}
	}

	return result;
}

/* Cau 10: Trong hàm main thể hiện các menu lựa chọn các hàm câu 1-9.
 */
int main()
{
	Hashtable h;
	initHashtable(h, 9);

	while (true)
	{
		cout << "\n ================== HASH TABLE ==================" << endl;
		cout << "\t 1. Create Hash table auto" << endl;
		cout << "\t 2. Create Hash table from array" << endl;
		cout << "\t 3. Create Hash table manual" << endl;
		cout << "\t 4. Print Hash table" << endl;
		cout << "\t 5. Delete value from Hash table" << endl;
		cout << "\t 6. Find value in Hash table" << endl;
		cout << "\t 7. Sum odd values in Hash table" << endl;
		cout << "\t 8. Check if Hash table is empty" << endl;
		cout << "\t 9. Find values in range" << endl;
		cout << "\t 10. Clear Hash table" << endl;
		cout << "\t 11. Exit" << endl;

		int choice;
		cout << "Nhap lua chon: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			initDataHTAuto(h);
			break;
		}
		case 2:
		{
			int arr[] = {50, 75, 25, 30, 10, 90, 70, 60, 30, 70, 90};
			initDataHTArr(h, arr, sizeof(arr) / sizeof(arr[0]));
			break;
		}
		case 3:
		{
			initDataHTManual(h);
			break;
		}
		case 4:
		{
			printHashtable(h);
			break;
		}
		case 5:
		{
			int valueToDelete;
			cout << "Nhap gia tri can xoa: ";
			cin >> valueToDelete;
			deleteValue(h, valueToDelete);
			break;
		}
		case 6:
		{
			int valueToFind;
			cout << "Nhap gia tri can tim: ";
			cin >> valueToFind;
			if (findValue(h, valueToFind))
				cout << "Tim thay gia tri " << valueToFind << " trong bang băm." << endl;
			else
				cout << "Khong tim thay gia tri " << valueToFind << " trong bang băm." << endl;
			break;
		}
		case 7:
		{
			cout << "Tong cac gia tri le trong bang băm: " << sumOddValues(h) << endl;
			break;
		}
		case 8:
		{
			if (isEmpty(h))
				cout << "Bang băm rong." << endl;
			else
				cout << "Bang băm khong rong." << endl;
			break;
		}
		case 9:
		{
			int a, b;
			cout << "Nhap khoang [a, b]: ";
			cin >> a >> b;

			Hashtable result = findInRange(h, a, b);
			printHashtable(result);

			deleteHashtable(result);

			break;
		}
		case 10:
		{
			deleteHashtable(h);
			initHashtable(h, 9);
			cout << "Bang băm da duoc xoa." << endl;
			break;
		}
		case 11:
		{
			deleteHashtable(h);
			cout << "Bang băm da duoc xoa." << endl;
			return 0;
		}
		default:
		{
			cout << "Lua chon khong hop le!" << endl;
			break;
		}
		}
	}

	return 0;
}