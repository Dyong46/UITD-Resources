#include <iostream>

using namespace std;

/*
	Viết chương trình cài đặt bảng băm (Kích thước SIZE = 9) theo phương pháp nối kết để lưu trữ các số kiếu int. Thực hiện các yêu cầu sau:
*/
const int SIZE = 9;

struct Node
{
	int data;
	Node *pNext;
};

Node *initNode(int value)
{
	Node *p = new Node;

	p->data = value;
	p->pNext = NULL;

	return p;
};

struct Hashtable
{
	struct Bucket
	{
		Node *pHead;
		Node *pTail;
	};

	Bucket buckets[SIZE];
};

void initHashtable(Hashtable &h)
{
	for (int i = 0; i < SIZE; i++)
	{
		h.buckets[i].pHead = NULL;
		h.buckets[i].pTail = NULL;
	}
}

/* Câu 1. Viết hàm băm theo phương pháp chia.
 */
int hashFunc(int value)
{
	return value % SIZE;
}

int hashFunc(Node *p)
{
	return p->data % SIZE;
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

void printHashtable(Hashtable h)
{
	cout << "Size of Hashtable: " << SIZE << endl;

	for (int i = 0; i < SIZE; i++)
	{
		cout << "Bucket[" << i << "]: ";

		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			cout << p->data << "\t";
		}
		cout << endl;
	}
}

/* Câu 2. Viết hàm khởi tạo giá trị cho bảng băm theo phương pháp tự động. Các giá trị được chọn ngẫu nhiên trong đoạn [856; 988]. Số lượng giá trị cần nhập [45; 95].
Input:
	+ HT& h
Output:
	+ HT& h
*/
void initDataHTAuto(Hashtable &h)
{
	int n = rand() % (95 - 45 + 1) + 45;

	for (int i = 0; i < n; i++)
	{
		int value = rand() % (988 - 856 + 1) + 856;
		add(h, value);
	}
}

/* Câu 3. Viết hàm nhập giá trị cho bảng băm từ mảng 1D n phần tử.
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

/* Câu 4. Viết hàm nhập giá trị cho bảng băm theo phương pháp nhập thủ công từ bàn phím (Điều kiện kết thúc nhập tự qui định).
Input:
	+ HT& h
Output:
	+ HT& h
*/
void initDataHTManual(Hashtable &h)
{
	int value;

	while (true)
	{
		cout << "Nhap gia tri (hoac nhap -1 de ket thuc): ";
		cin >> value;

		if (value == -1)
			break;

		add(h, value);
	}
}

/* Câu 5. Viết hàm kiếm tra bảng băm có rỗng hay không? Nếu rỗng thì trả về true. Nếu không không rỗng trả về false.
Input:
	+ HT h
Output:
	+ return bool
*/
bool isEmpty(Hashtable h)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (h.buckets[i].pHead != NULL)
			return false;
	}
	return true;
}

/* Câu 6. Viết hàm đếm các giá trị được lưu trữ trong bảng băm.
Input:
	+ HT h
Output:
	+ return int
*/
int count(Hashtable h)
{
	int count = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			count++;
		}
	}

	return count;
}

/* Câu 7. Viết hàm tìm giá trị X trong bảng băm. Nếu tìm thấy giá trị X thì trả về true. Nếu không tìm thấy trả về false.
Input:
	+ HT h
	+ int value
Output:
	+ return bool
*/
bool findValue(Hashtable h, int value)
{
	int viTri = hashFunc(value);

	for (Node *p = h.buckets[viTri].pHead; p != NULL; p = p->pNext)
	{
		if (p->data == value)
			return true;
	}

	return false;
}

/* Câu 8. Viết hàm tìm max mà min trong bảng băm (viết 1 hàm).
Input:
	+ HT h
	+ int &max
	+ int &min
Output:
	+ int &max
	+ int &min
*/
void findMaxMin(Hashtable h, int &max, int &min)
{
	max = h.buckets[0].pHead->data;
	min = h.buckets[0].pHead->data;

	for (int i = 0; i < SIZE; i++)
	{
		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			if (p->data > max)
				max = p->data;

			if (p->data < min)
				min = p->data;
		}
	}
}

/* Câu 9. Viết hàm đếm các giá trị trong bảng băm có giá trị chăn và lẻ (dựa vào phần nguyên của số thực để kiếm tra chẵn-lẽ). Trường hợp "<" trả về true; "=" trả về 1; ">" false.
Input:
	+ HT h
	+ int &chan
	+ int &le
Output:
	+ int &chan
	+ int &le
*/
void countChanLe(Hashtable h, int &chan, int &le)
{
	chan = 0;
	le = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (Node *p = h.buckets[i].pHead; p != NULL; p = p->pNext)
		{
			if (p->data % 2 == 0)
				chan++;
			else
				le++;
		}
	}
}

/* Câu 10. Trong hàm main, thiết kế các testcase gọi các hàm từ câu 2 đến 9. Dữ liệu Câu #3: tạo mảng demo gồm các phần tử sau: 50, 75, 25, 30, 10, 90, 70, 60, 30, 70, 90.
 */

int main()
{
	Hashtable h;
	initHashtable(h);

	while (1)
	{
		cout << "===================== MENU =====================" << endl;
		cout << "\t1. Tao bang bam tu dong" << endl;
		cout << "\t2. Tao bang bam tu mang 1 chieu" << endl;
		cout << "\t3. Tao bang bam tu nhap tu ban phim" << endl;
		cout << "\t4. Kiem tra bang bam co rong hay khong" << endl;
		cout << "\t5. Dem so luong phan tu trong bang bam" << endl;
		cout << "\t6. Tim gia tri trong bang bam" << endl;
		cout << "\t7. Tim max va min trong bang bam" << endl;
		cout << "\t8. Dem so luong phan tu chan va le trong bang bam" << endl;
		cout << "\t9. In bang bam" << endl;
		cout << "\t10. Thoat" << endl;
		cout << "=================================================" << endl;
		cout << "Nhap lua chon: ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			initDataHTAuto(h);
			cout << "Bang bam da duoc tao tu dong." << endl;
			break;
		}
		case 2:
		{
			int a[] = {50, 75, 25, 30, 10, 90, 70, 60, 30, 70, 90};
			int n = sizeof(a) / sizeof(a[0]);
			initDataHTArr(h, a, n);
			cout << "Bang bam da duoc tao tu mang." << endl;
			break;
		}
		case 3:
		{
			initDataHTManual(h);
			cout << "Bang bam da duoc tao tu nhap tu ban phim." << endl;
			break;
		}
		case 4:
		{
			if (isEmpty(h))
				cout << "Bang bam rong." << endl;
			else
				cout << "Bang bam khong rong." << endl;
			break;
		}
		case 5:
		{
			cout << "So luong phan tu trong bang bam: " << count(h) << endl;
			break;
		}
		case 6:
		{
			int value;
			cout << "Nhap gia tri can tim: ";
			cin >> value;
			if (findValue(h, value))
				cout << "Tim thay gia tri " << value << " trong bang bam." << endl;
			else
				cout << "Khong tim thay gia tri " << value << " trong bang bam." << endl;
			break;
		}
		case 7:
		{
			int max, min;
			findMaxMin(h, max, min);
			cout << "Max: " << max << ", Min: " << min << endl;
			break;
		}
		case 8:
		{
			int chan, le;
			countChanLe(h, chan, le);
			cout << "So luong phan tu chan: " << chan << ", So luong phan tu le: " << le << endl;
			break;
		}
		case 9:
		{
			printHashtable(h);
			break;
		}
		case 10:
		{
			cout << "Thoat chuong trinh." << endl;
			return 0;
		}
		default:
		{
			cout << "Lua chon khong hop le. Vui long chon lai." << endl;
			break;
		}
		}
		cout << "=================================================" << endl;
		cout << endl;
	}

	return 0;
}