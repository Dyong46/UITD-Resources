#include <iostream>
#include <stack>
#include <ctime>

using namespace std;

/* Cau 1: Tạo cấu trúc node và cây.
 */
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

/* Cau 2: Viết hàm chuyển một giá trị nguyên sang node
 */
Node *initNode(int value)
{
	Node *p = new Node;
	p->data = value;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
};

/* Cau 3: Viết hàm khởi tạo cây.
 */
void initTree(Tree &t)
{
	t.pRoot = NULL;
};

/* Cau 4: Viết hàm chèn node chứa giá trị (dữ liệu) vào cây (không dùng đệ qui).
Input:
	+ Tree& t
	+ Node* p
Output:
	+ Tree& t
*/
void addNode(Tree &t, Node *p)
{
	if (t.pRoot == NULL)
	{
		t.pRoot = p;
	}
	else
	{
		Node *pGoto = t.pRoot;
		Node *pLoca = NULL;

		while (pGoto != NULL)
		{
			pLoca = pGoto;
			if(p->data == pGoto->data)
				return;
			
			if (p->data < pGoto->data)
				pGoto = pGoto->pLeft;
			else if (p->data > pGoto->data)
				pGoto = pGoto->pRight;
		}

		if (p->data < pLoca->data)
		{
			pLoca->pLeft = p;
		}
		else if (p->data > pLoca->data)
		{
			pLoca->pRight = p;
		}
	}
};

void addValue(Tree &t, int value)
{
	Node *p = initNode(value);
	addNode(t, p);
};

/* Cau 5: Viết hàm khởi tạo giá trị tự động cho cây. Các giá trị được chọn ngẫu nhiên trong đoạn [-38; 68]. Số lượng cho một lần tạo tự động [10; 20].
Input:
	+ Tree& t
Output:
	+ Tree& t
	+ int n
*/
int initDataTreeAuto(Tree &t)
{
	srand(time(0));
	int n = rand() % (20 - 10 + 1) + 10;

	for (int i = 0; i < n; i++)
	{
		int value = rand() % (68 - -38 + 1) + -38;
		addNode(t, initNode(value));
	}
	return n;
}

/* Cau 6: Viết hàm khởi tạo giá trị cho cây từ mảng 1 chiều.
Input:
	+ Tree& t\
	+ int arr[]
	+ int n
Output:
	+ Tree& t
*/
void initDataTreeArr(Tree &t, int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		addNode(t, initNode(arr[i]));
	}
};

/* Cau 7: Viết hàm duyệt cây theo LNR.
Input:
	+ Tree& t
Output:
	+ void
*/
void printTree(Tree t)
{
	stack<Node *> s;
	Node *p = t.pRoot;

	while (p != NULL || s.empty() == false)
	{
		// Left
		while (p != NULL)
		{
			s.push(p);
			p = p->pLeft;
		}

		// Get the top node and delete it
		p = s.top();
		s.pop();

		// Print the node
		cout << p->data << " ";

		// Move to the right node
		p = p->pRight;
	}
	cout << endl
			 << endl;
}

void LNR(Node *p)
{
	if (p != NULL)
	{
		LNR(p->pLeft);
		cout << p->data << " ";
		LNR(p->pRight);
	}
}

/* Cau 8: Viết hàm tìm kiếm giá trị trong cây.
Input:
	+ Tree t
	+ int value
Output:
	+ return bool
*/
bool timGiaTri(Tree t, int value)
{
	Node *p = t.pRoot;

	while (p != NULL)
	{
		if (value == p->data)
			return true;

		if (value < p->data)
			p = p->pLeft;
		else if (value > p->data)
			p = p->pRight;
	}
	return false;
};

/* Cau 9: Viết hàm đếm toàn bộ số node của cây.
Input:
	+ Tree t
Output:
	+ int count
*/
int countNode(Tree t)
{
	stack<Node *> s;
	Node *p = t.pRoot;
	int count = 0;

	while (p != NULL || s.empty() == false)
	{
		while (p != NULL)
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
};

/* Cau 10: Viết hàm đếm số node lá của cây.
Input:
	+ Tree t
Output:
	+ int count
 */
int countNodeLa(Tree t)
{
	stack<Node *> s;
	Node *p = t.pRoot;
	int count = 0;

	while (p != NULL || s.empty() == false)
	{
		while (p != NULL)
		{
			s.push(p);
			p = p->pLeft;
		}

		p = s.top();
		s.pop();

		if (p->pLeft == NULL && p->pRight == NULL)
			count++;

		p = p->pRight;
	}

	return count;
};

/* Cau 11: Viết hàm in ra nhánh (LNR) của một node.
Input:
	+ Tree t
Output:
	+
*/

/* Cau 12: Viết hàm đếm số node có giá trị nhỏ hơn X.
Input:
	+ Tree t
	+ int x
Output:
	+ int count
*/
int countNodeLessX(Tree t, int x)
{
	stack<Node *> s;
	Node *p = t.pRoot;
	int count = 0;

	while (p != NULL || s.empty() == false)
	{
		while (p != NULL)
		{
			s.push(p);
			p = p->pLeft;
		}

		p = s.top();
		s.pop();

		cout << p->data << " ";

		if (p->data < x)
			count++;
		else
			break;

		p = p->pRight;
	}
	return count;
};

/* Cau 13: Viết hàm tính tổng các node trong cây.
Input:
	+ Tree t
Output:
	+ int sum
*/
int sumNode(Tree &t)
{
	stack<Node *> s;
	Node *p = t.pRoot;
	int sum = 0;

	while (p != NULL || s.empty() == false)
	{
		while (p != NULL)
		{
			s.push(p);
			p = p->pLeft;
		}

		p = s.top();
		s.pop();

		sum += p->data;

		p = p->pRight;
	}

	return sum;
};

/* Cau 14: Viết hàm tính tổng các node chẵn trong cây.
Input:
	+ Tree t
Output:
	+ int sum
*/
int sumNodeChan(Tree &t)
{
	stack<Node *> s;
	Node *p = t.pRoot;
	int sum = 0;

	while (p != NULL || s.empty() == false)
	{
		while (p != NULL)
		{
			s.push(p);
			p = p->pLeft;
		}

		p = s.top();
		s.pop();

		if (p->data % 2 == 0)
			sum += p->data;

		p = p->pRight;
	}
	return sum;
};

/* Cau 15: Viết hàm tìm node có giá trị lớn nhất và nhỏ nhất trong cây
Input:
	+ Tree t
	+ int& min
	+ int& max
Output:
	+ int& max
	+ int& min
*/
void findMaxMin(Tree t, int &min, int &max)
{
	Node *pMin = t.pRoot;

	while (pMin != NULL)
	{
		if (pMin->pLeft != NULL)
			pMin = pMin->pLeft;
		else
			break;
	}
	min = pMin->data;

	Node *pMax = t.pRoot;
	while (pMax != NULL)
	{
		if (pMax->pRight != NULL)
			pMax = pMax->pRight;
		else
			break;
	}
	max = pMax->data;
};

int main()
{
	cout << "Test 5. Khoi tao gia tri tu dong cho cay t1: " << endl;
	Tree t1;
	initTree(t1);
	int n = initDataTreeAuto(t1);
	cout << "Cay da duoc tao voi " << n << " node." << endl;
	cout << "Duyet cay theo LNR: ";
	printTree(t1);

	cout << "Test 6. Khoi tao gia tri tu mang[50, 26, 73, 18, 39, 66, 88, 28, 72, 81, 96, 33] cho cay t2: " << endl;
	int arr[] = {50, 26, 73, 18, 39, 66, 88, 28, 72, 81, 96, 33};
	Tree t2;
	initTree(t2);
	initDataTreeArr(t2, arr, 12);
	cout << "Cay da duoc tao tu mang voi 12 node." << endl;
	cout << "Duyet cay theo LNR: ";
	printTree(t2);

	cout << "Test 8. Tim kiem gia tri 39(1) trong cay t2: " << timGiaTri(t2, 39) << endl << endl;
	cout << "Test 8. Tim kiem gia tri 100(0) trong cay t2: " << timGiaTri(t2, 100) << endl << endl;

	cout << "Test 9. Dem so node trong cay t2: " << countNode(t2) << endl << endl;

	cout << "Test 10. Dem so node la trong cay t2: " << countNodeLa(t2) << endl << endl;

	cout << "Test 11. In ra nhanh(LNR) cua node" << endl << endl;

	cout << "Test 12. Dem so node co gia tri nho hon 50(5) trong cay t2: " << countNodeLessX(t2, 50) << endl << endl;

	cout << "Test 13. Tinh tong cac node trong cay t2: " << sumNode(t2) << endl << endl;

	cout << "Test 14. Tinh tong cac node chan trong cay t2: " << sumNodeChan(t2) << endl << endl;

	int min = t2.pRoot->data;
	int max = t2.pRoot->data;
	findMaxMin(t2, min, max);
	cout << "Test 15. Tim node co gia tri nho nhat trong cay t2: " << min << endl;
	cout << "Test 15. Tim node co gia tri lon nhat trong cay t2: " << max << endl << endl;

	return 0;
}