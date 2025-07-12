#include <iostream>
#include <stack>
#include <ctime>

using namespace std;

struct Node
{
	int data;
	Node *pLeft;
	Node *pRight;
};

struct Tree
{
	Node *pRoot;
};

Node* initNode(int value)
{
	Node *p = new Node;
	p->data = value;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
};

void initTree(Tree &t)
{
	t.pRoot = NULL;
};

/* Cau 1: Viết hàm chèn node chứa giá trị (dữ liệu kiểu số thực) vào cây. Trường hợp node giá trị cần chèn bằng một node nào đó trong cây thì BỎ QUA
Input:
	+ Tree& t
	+ Node* p
Output:
	+ Tree& t
*/
void addNode(Tree& t, Node* p)
{
	if(t.pRoot == NULL)
	{
		t.pRoot = p;
	}
	else
	{
		Node* pGoto = t.pRoot;
		Node* pLoca = NULL;
		while(pGoto != NULL)
		{
			pLoca = pGoto;
			if(p->data < pGoto->data)
				pGoto = pGoto->pLeft;
			else if(p->data > pGoto->data)
				pGoto = pGoto->pRight;
		}

		if(p->data < pLoca->data)
			pLoca->pLeft = p;
		else
			pLoca->pRight = p;
	}
}

void addValue(Tree& t, int value)
{
	Node* p = initNode(value);
	addNode(t, p);
}

/* Cau 2: Viết hàm tạo cây tự động. Các giá trị được chọn ngẫu nhiên trong đoạn [512; 723]. Số lượng [50; 60].
Input:
	+ Tree& t
Output:
	+ Tree& t
*/
void initDataTreeAuto(Tree& t)
{
	srand(time(0));
	int n = rand() % (60 - 50 + 1) + 50;
	for(int i = 0; i < n; i++)
	{
		int value = rand() % (723 - 512 + 1) + 512;
		addValue(t, value);
	}
}

/* Cau 3: Viết hàm tạo cây tự động từ một mảng n phần tử.
Input:
	+ Tree& t
	+ int* arr
	+ int n
Output:
	+ Tree& t
*/
void initDataTreeArr(Tree& t, int* arr, int n)
{
	for(int i = 0; i < n; i++)
	{
		addValue(t, arr[i]);
	}
}

/* Cau 4: Viết hàm duyệt cây theo NLR, LRN, LNR. Chú ý: In kèm thêm 3 địa chỉ của NODE, địa chỉ Left và địa chỉ Right.
Input:
	+ Tree t
Output:
	+ void
*/
void printLNR(Node* p)
{
	if(p != NULL)
	{
		printLNR(p->pLeft);
		cout << p->data << " ";
		printLNR(p->pRight);
	}
}

void printNLR(Node* p)
{
	if(p != NULL)
	{
		cout << p->data << " ";
		printNLR(p->pLeft);
		printNLR(p->pRight);
	}
}

void printLRN(Node* p)
{
	if(p != NULL)
	{
		printLRN(p->pLeft);
		printLRN(p->pRight);
		cout << p->data << " ";
	}
}

/* Cau 5: Viết hàm tìm kiếm từ giá trị X. X do người dùng nhập và truyền vào hàm. Nếu tìm thấy giá trị X thì trả về địa chỉ của node. Nếu không tìm thấy trả về null.
Input:
	+ Tree t
	+ int value
Output:
	+ Node* p
*/
Node* searchValue(Tree t, int value)
{
	Node* p = t.pRoot;
	while(p != NULL)
	{
		if(value == p->data)
			return p;
		else if(value < p->data)
			p = p->pLeft;
		else
			p = p->pRight;
	}
	return NULL;
}

/* Cau 6: Viết hàm đếm toàn bộ số node của cây.
Input:
	+ Tree t
Output:
	+ int count
*/
int countNode(Tree& t)
{
	stack<Node*> s;
	Node* p = t.pRoot;
	int count = 0;
	while(p != NULL || !s.empty())
	{
		while(p != NULL)
		{
			s.push(p);
			p = p->pLeft;
		}

		p = s.top();
		s.pop();

		count++;
		
		p = p->pRight;
	}
	return count;
}

/* Cau 7: Viết hàm in ra các node nhánh còn lại từ một node nhập từ bàn phím, cách duyệt LNR.
Input:
	+ Tree t
	+ Node* p
Output:
	+ void
*/
void printNodeBranch(Node* p)
{
	if(p != NULL)
	{
		printNodeBranch(p->pLeft);
		cout << p->data << " ";
		printNodeBranch(p->pRight);
	}
}

/* Cau 8: Viết hàm đếm số node có giá trị lớn hơn X và nhỏ hơn Y (X <node< Y). X, Y do người dùng nhập vào và được truyền vào hàm.
*/
int countNodeInRange(Tree& t, int x, int y)
{
	stack<Node*> s;
	Node* p = t.pRoot;
	int count = 0;
	while(p != NULL || !s.empty())
	{
		while(p != NULL )
		{
			s.push(p);
			p = p->pLeft;
		}

		p = s.top();
		s.pop();

		if(p->data > x && p->data < y)
			count++;
		
		p = p->pRight;
	}
	return count;
}

/* Cau 9: Viết hàm đếm các node có giá trị chẵn và lẻ. Trường hợp "<" trả về -1; "=" trả về 0; ">" trả về 1.
Input:
	+ Tree t
	+ int& countChan
	+ int& countLe
Output:
	+ int result
*/


/* Cau 10: Trong hàm main thế hiện các menu lựa chọn các hàm từ câu 2 đến 9. Trong menu lựa chọn Câu #3: tạo mảng demo gồm các phần tử sau: 50, 75, 25, 30, 10, 90, 70, 60, 30, 70, 90.
*/
int main()
{
	int arr[] = {50, 75, 25, 30, 10, 90, 70, 60, 30, 70, 90};
	Tree t;
	initTree(t);

	while(1)
	{
		cout << "===================== MENU ====================" << endl;
		cout << "1. Khoi tao cay tu dong" << endl;
		cout << "2. Khoi tao cay tu mang" << endl;
		cout << "3. Duyet cay theo LNR" << endl;
		cout << "4. Duyet cay theo NLR" << endl;
		cout << "5. Duyet cay theo LRN" << endl;
		cout << "6. Tim kiem node" << endl;
		cout << "7. Dem so node" << endl;
		cout << "8. Dem so node trong khoang" << endl;
		cout << "9. Dem so node chan va le" << endl;
		cout << "10. In ra cac node nhan cua node" << endl;
		cout << "11. Thoat" << endl;
		cout << "===============================================" << endl;
		int choice;
		cout << "Nhap lua chon: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			{
				initDataTreeAuto(t);
				cout << "Cay da duoc khoi tao tu dong!" << endl;
				break;
			}
		case 2:
			{
				initDataTreeArr(t, arr, 11);
				cout << "Cay da duoc khoi tao tu mang!" << endl;
				break;
			}
		case 3:
			{
				cout << "Cay duyet theo LNR: ";
				printLNR(t.pRoot);
				cout << endl;
				break;
			}
		case 4:
			{
				cout << "Cay duyet theo NLR: ";
				printNLR(t.pRoot);
				cout << endl;
				break;
			}
		case 5:
			{
				cout << "Cay duyet theo LRN: ";
				printLRN(t.pRoot);
				cout << endl;
				break;
			}
		case 6:
			{
				int value;
				cout << "Nhap gia tri can tim: ";
				cin >> value;
				Node* p = searchValue(t, value);
				if(p != NULL)
					cout << "Tim thay node co gia tri " << value << "!" << endl;
				else
					cout << "Khong tim thay node co gia tri " << value << "!" << endl;
				break;
			}
		case 7:
			{
				int count = countNode(t);
				cout << "So node trong cay: " << count << endl;
				break;
			}
		case 8:
			{
				int x, y;
				cout << "Nhap gia tri x: ";
				cin >> x;
				cout << "Nhap gia tri y: ";
				cin >> y;
				int count = countNodeInRange(t, x, y);
				cout << "So node trong khoang [" << x << ", " << y << "]: " << count << endl;
				break;
			}
		case 9:
			{
				int countChan = 0, countLe = 0;
				int result = countNodeInRange(t, countChan, countLe);
				cout << "So node chan: " << countChan << endl;
				cout << "So node le: " << countLe << endl;
				break;
			}
		case 10:
			{
				int value;
				cout << "Nhap gia tri node can in: ";
				cin >> value;
				Node* p = searchValue(t, value);
				if(p != NULL)
				{
					cout << "Cac node nhan cua node " << value << ": ";
					printNodeBranch(p);
					cout << endl;
				}
				else
					cout << "Khong tim thay node co gia tri " << value << "!" << endl;
				break;
			}
		case 11:
			{
				cout << "Thoat!" << endl;
				return 0;
			}
		default:
			{
				cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
				break;
			}
		}
	}
	return 0;
}