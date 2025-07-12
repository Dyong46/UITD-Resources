#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* pNext;
};

Node* initNode(int value) {
	Node* p = new Node;
	p->data = value;
	p->pNext = NULL;

	return p;
}

struct List
{
	Node* pHead;
	Node* pTail;
};

void initList(List& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

void addHead(List& l, Node*p) {
	if(l.pHead == NULL) {
		l.pHead = p;
		l.pTail = p;
	} else {
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

void addTail(List& l, Node*p) {
	if(l.pHead == NULL) {
		l.pHead = p;
		l.pTail = p;
	} else {
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void printList(List l) {
	for(Node* p = l.pHead;p != NULL; p = p->pNext) {
		printf("Data: %d\n", p->data);
	}
}

bool findValue(List l, int value) {
	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(value == p->data) {
			return true;
		}
	}
	return false;
}

/* Yeu cau: Viet ham tim gia tri node ke cuoi
Input:
	+1: List
Output:
	+ return bool
	+ x: int&
*/

/* Yeu cau: Tim gia tri nho nhat
Input:
	+1: List
Output:
	+ x: int&
*/

bool giaTriNutKeCuoi(List l, int& x) {
	
}

int main() {
	Node* p1 = initNode(10);

	Node* p2 = initNode(79);

	Node* p3 = initNode(39);

	List l;
	initList(l);

	addHead(l,p1);
	addHead(l,p2);
	addTail(l,p3);

	printList(l);

	bool check = findValue(l, 10);
	bool check2 = findValue(l, 12);

	cout << "check" << check;
	cout << "check" << check2;

	return 0;
}
