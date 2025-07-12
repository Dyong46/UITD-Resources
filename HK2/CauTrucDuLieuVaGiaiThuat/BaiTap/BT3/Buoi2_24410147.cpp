#include <iostream>
#include <cmath>

using namespace std;

/* Yeu cau 1: Xây dựng cấu trúc node và cấu trúc danh sách liên kết đơn.

*/

struct Node
{
	int data;
	Node* pNext;
};

struct List
{
	Node* pHead;
	Node* pTail;
};

/* Yeu cau 4: Viết hàm chèn node vào đầu danh sách.
	Input:
		+ l: List&
		+ p: Node*
	Output:
		+ l: List&
*/
void addHead(List& l, Node*p) {
	if(l.pHead == NULL) {
		l.pHead = p;
		l.pTail = p;
	} else {
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

/* Yeu cau 4: Viết hàm chèn node vào cuối danh sách.
	Input:
		+ l: List&
		+ p: Node*
	Output:
		+ l: List&
*/
void addTail(List& l, Node*p) {
	if(l.pHead == NULL) {
		l.pHead = p;
		l.pTail = p;
	} else {
		l.pTail->pNext = p;
		l.pTail = p;
	}

	// Đảm bảo node cuối cùng không trỏ đến phần tử nào
	l.pTail->pNext = NULL;
}

/* Yeu cau 6: Viết hàm in giá trị danh sách.
	Input:
		+	l: List
	Output:
		+	
*/
void printList(List l) {
	if(l.pHead == NULL) {
		cout << "Danh sach rong" << endl;
		return;
	}

	for(Node* p = l.pHead;p != NULL; p = p->pNext) {
		cout << p->data;
		if (p->pNext != NULL) cout << ", ";
	}
	cout << endl;
}

/* yeu cau: Dem chan
	Input:
		+ l: List
	Output:
		+ chan: int
*/
int countEven(List l) {
	int chan = 0;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->data % 2 == 0) {
			chan++;
		}
	}

	return chan;
}

/*
	Viet ham dem cac so nguyen to trong danh sach lien ket
	Input:
		+ l: List
	Output:
		+ dem: int
*/
int demNode(List l) {
	int dem = 0;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		dem++;
	}

	return dem;
}

/* Yeu cau: Tim gia tri lon nhat
	Input:
		+ l: List
	Output:
		+ return int
*/
int timMax(List l) {
	int max = l.pHead->data;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->data > max) {
			max = p->data;
		}
	}

	return max;
}

/* Yeu cau: Tinhs tong
	Input:
		+ l: List
	Output:
		+ return sum
*/
int tinhTong(List l) {
	int sum = 0;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		sum += p->data;
	}

	return sum;
}

/* yeu cau: Xoa node tai vi tri dau cua List
	Input:
		+ l: List&
	Output:
		+ l: List&
		+ return bool
*/
bool popHead(List& l) {
	if(l.pHead == NULL) {
		return false;
	}

	Node* p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;

	if(l.pHead == NULL) {
		l.pTail = NULL;
	}

	return true;
}

/* yeu cau: Xoa node tai vi tri cuoi cua List
	Input:
		+ l: List&
	Output:
		+ l: List&
		+ return bool
*/
bool popTail(List& l) {
	if(l.pHead == NULL) {
		return false;
	}

	Node* p = l.pHead;
	Node* q = l.pTail;

	// Kiem node ke cuoi
	while(p->pNext != l.pTail) {
		p = p->pNext;
	}

	l.pTail = p;
	l.pTail->pNext = NULL;
	delete q;

	if(l.pHead == NULL) {
		l.pTail = NULL;
	}

	return true;
}

int main() {

	cout << "Test: Yeu cau 2. Khởi tạo danh sách lien kết đơn và khởi tạo địa chỉ node:" << endl;
	cout << "Khởi tạo danh sách lien kết đơn: " << endl;
	List l = {NULL, NULL};

	cout << "Khởi tạo 3 địa chỉ node từ một số thực: {11.5, 79.3, 39.02} " << endl;
	Node* p1 = new Node({11, NULL});
	Node* p2 = new Node({79, NULL});

	cout << endl;
	
	cout << "Test: Yeu cau 3,4. Chèn các node p1, p2, p3 vào đầu và cuối danh sách:" << endl;
	addHead(l,p1);
	addHead(l,p2);

	cout << "In danh sách liên kết l" << endl;
	printList(l);
	cout << endl;

	cout << "\nTest: Dem chan(1) = " << countEven(l) << endl;

	cout << "\nTest: Max(79) = " << timMax(l) << endl;

	cout << "\nTest: Xoa: " << popHead(l) << endl;

	cout << "\nTest: Xoa: " << popHead(l) << endl;
	
	printList(l);
	
	cout << "\nTest: Xoa: " << popHead(l) << endl;
	printList(l);

	return 0;
}