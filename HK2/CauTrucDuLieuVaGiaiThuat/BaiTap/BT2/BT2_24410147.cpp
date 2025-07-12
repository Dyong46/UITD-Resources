#include <iostream>
#include <cmath>

using namespace std;

/* Yeu cau 1: Xây dựng cấu trúc node và cấu trúc danh sách liên kết đơn.

*/

struct Node
{
	float data;
	Node* pNext;
};

struct List
{
	Node* pHead;
	Node* pTail;
};

/* Yeu cau 2: Viết hàm khởi tạo danh sách liên kết đơn và hàm khởi tạo địa chỉ node từ một số nguyên.

*/
Node* initNode(float value) {
	Node* p = new Node;
	p->data = value;
	p->pNext = NULL;

	return p;
}

void initList(List& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

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

/* Yeu cau 5: Viết hàm khởi tạo giá trị cho danh sách từ mảng một chiều.
	Input:
		+	l: List&
		+ a[]: int
		+ n: int
	Output:
		+	l: List&
*/
void addValueFormArr(List& l, float a[], int n) {
	for(int i = 0; i < n; i++) {
		Node* p = initNode(a[i]);
		addTail(l, p);
	}
}

/* Yeu cau 6: Viết hàm in giá trị danh sách.
	Input:
		+	l: List
	Output:
		+	
*/
void printList(List l) {
	for(Node* p = l.pHead;p != NULL; p = p->pNext) {
		cout << p->data;
		if (p->pNext != NULL) cout << ", ";
	}
	cout << endl;
}

/* Yeu cau 7: Viết hàm in giá trị kèm địa chỉ của từng node trong danh sách.
	Input:
		+ l: List
	Output:
		+
*/
void printListWithAddress(List l) {
	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		cout << p << " - " << p->data;
		if (p->pNext != NULL) cout << ", ";
	}
	cout << endl;
}

/* Yeu cau 8: Viết hàm kiểm tra danh sách có rỗng hay không.
	Input:
		+	l: List
	Output:
		+	isEmpty: bool
*/
bool isEmpty(List l) {
	return l.pHead == NULL;
}

/* Yeu cau 9: Viết hàm trả về node thứ n trong danh sách.
	Input:
		+	l: List
		+	n: int
	Output:
		+	p: Node*
*/
Node* getNode(List l, int n) {
	int count = 1;
	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(count == n) {
			return p;
		}
		count++;
	}
	return NULL;
}

/* Yeu cau 10: Viết hàm tìm kiếm một node có giá trị X trong danh sách.
	Input:
		+	l: List
		+	value: float
	Output:
		+ check: bool
*/
Node* findValue(List l, float value) {
	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(value == p->data) {
			return p;
		}
	}
	return nullptr;
}

/* Yeu cau 11: Viết hàm tìm kiếm các địa chỉ node có giá trị X trong danh sách.
	Input:
		+	l: List
		+	value: float
	Output:
		+ arr: List
*/
List findNodeAddressByValue(List l, float value) {
	List arr;
	initList(arr);

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(value == p->data) {
			addHead(arr, p);
		}
	}
	return arr;
}

/* Yeu cau 12: Viết hàm đếm số lượng các node có giá trị âm, dương.
	Input:
		+ l: List
		+ positive: int&
		+ negative: int&
	Output:
		+	positive: int&
		+	negative: int&
*/
void countPositiveNegative(List l, int& positive, int& negative) {
	positive = 0;
	negative = 0;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->data > 0) {
			positive++;
		} else {
			negative++;
		}
	}
}

/* Yeu cau 13: Viết hàm tìm node có giá trị âm lớn nhất, tìm node có giá trị lẻ nhỏ nhất trong danh sách.
	Input:
		+	l: List
		+	negativeMax: Node*&
		+	oddMin: Node*&
	Output:
		+ negativeMax: Node*&
		+ oddMin: Node*&
*/
void findNegativeMaxOddMin(List l, Node*& negativeMax, Node*& oddMin) {
	negativeMax = NULL;
	oddMin = NULL;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->data < 0 && (negativeMax == NULL || negativeMax->data < p->data)) {
			negativeMax = p;
		}

		if (((int)p->data % 2 != 0) && (oddMin == NULL || oddMin->data > p->data)) {
			oddMin = p;
		}
	}
}

/* Yeu cau 14: Viết hàm cập nhật giá trị cho một node có giá trị là X bằng giá trị Y mới.
	Input:
		+	l: List&
		+	x: float
		+	y: float
	Output:
		+ l: List&
*/
bool updateValue(List& l, float x, float y) {
	Node* p = findValue(l, x);
	if (p) {
		p->data = y;
		return true;
	} else {
		return false;
	}
}

/* Yeu cau 15: Viết hàm copy danh sách.
	Input:
		+ l: List
		+ h: List&
	Output:
		+ h: List&
*/
void copyList(List l, List& h) {
	initList(h);
	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		Node* q = initNode(p->data);
		addTail(h, q);
	}
}

/* Bo sung: Viết hàm xóa danh sách - Giải phóng bộ nhớ
	Input:
		+ l: List&
	Output:
		+ l: List&
*/
void deleteList(List& l) {
	Node* temp;
	while (l.pHead != NULL) {
		temp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete temp;
	}
	l.pTail = NULL;
}

int main() {

	cout << "Test: Yeu cau 2. Khởi tạo danh sách lien kết đơn và khởi tạo địa chỉ node:" << endl;
	cout << "Khởi tạo danh sách lien kết đơn: " << endl;
	List l;
	initList(l);

	cout << "Khởi tạo 3 địa chỉ node từ một số thực: {11.5, 79.3, 39.02} " << endl;
	Node* p1 = initNode(11.5);
	Node* p2 = initNode(79.3);
	Node* p3 = initNode(39.02);

	cout << endl;
	
	cout << "Test: Yeu cau 3,4. Chèn các node p1, p2, p3 vào đầu và cuối danh sách:" << endl;
	addHead(l,p1);
	addHead(l,p2);
	addTail(l,p3);

	cout << "In danh sách liên kết l" << endl;
	printList(l);
	cout << endl;

	cout << "Test: Yeu cau 5. Khởi tạo giá trị cho danh sách từ mảng một chiều:" << endl;
	cout << "Tạo mảng danh sách sô nguyên có 7 giá trị sau: {1.5, 2.3, 3.2, 4.1, 5.0, -8.0, -2.0} " << endl;
	float a[] = {1.5, 2.3, 3.2, 4.1, 5.0, -8.0, -2.0};
	int n = 7;
	cout << "Khởi tạo danh sách liên kết l2" << endl;
	List l2;
	initList(l2);
	cout << "Thêm giá trị vào danh sách liên kết l2" << endl;
	addValueFormArr(l2, a, n);
	cout << "In danh sách liên kết l2" << endl;
	printList(l2);
	cout << endl;

	cout << "Test: Yêu cầu 4. In danh sách liên kết đơn l:" << endl;
	printList(l);
	cout << endl;

	cout << "Test: Yeu cau 7. In danh sách liên kết đơn l kèm địa chỉ các node:" << endl;
	printListWithAddress(l);
	cout << endl;

	cout << "Test: Yeu cau 8. Kiểm tra danh sách có rỗng hay không:" << endl;
	cout << "Kiểm tra danh sách l có rỗng hay không: " << isEmpty(l) << endl;
	cout << "Tạo danh sach rỗng l3" << endl;
	List l3;
	initList(l3);
	cout << "Kiểm tra danh sách l3 có rỗng hay không: " << isEmpty(l3) << endl;
	cout << endl;

	cout << "Test: Yeu cau 9. Trả về node thứ n trong danh sách:" << endl;
	cout << "Trả về node thứ 2 trong danh sách l: " << getNode(l, 2) << endl;
	cout << endl;

	cout << "Test: Yeu cau 10. Tìm kiếm một node có giá trị X trong danh sách:" << endl;
	Node* p = findValue(l, 11.5);
	cout << "Tìm kiếm node có giá trị 11.5 trong danh sách l: " << p << ": " << p->data << endl;
	cout << "Tìm kiếm node có giá trị 3.0 không có trong danh sách l: " << findValue(l, 3.0) << endl;
	cout << endl;

	cout << "Test: Yeu cau 11. Tìm kiếm các địa chỉ node có giá trị X trong danh sách:" << endl;
	List arr = findNodeAddressByValue(l, 11.5);
	cout << "In danh sách các địa chỉ node có giá trị 11.5 trong danh sách l: " << endl;
	printListWithAddress(arr);
	cout << endl;

	cout << "Test: Yeu cau 12. Đếm số lượng các node có giá trị âm, dương:" << endl;
	int positive, negative;
	cout << "Đếm số lượng các node có giá trị âm, dương trong danh sách l2" << endl;
	countPositiveNegative(l2, positive, negative);
	cout << "Số lượng các node có giá trị dương: " << positive << endl;
	cout << "Số lượng các node có giá trị âm: " << negative << endl;
	cout << endl;

	cout << "Test: Yeu cau 13. Tìm node có giá trị âm lớn nhất, tìm node có giá trị lẻ nhỏ nhất trong danh sách:" << endl;
	Node* negativeMax, *oddMin;
	findNegativeMaxOddMin(l2, negativeMax, oddMin);
	cout << "Node có giá trị âm lớn nhất trong danh sách l2: " << negativeMax << ": " << negativeMax->data << endl;
	cout << "Node có giá trị lẻ nhỏ nhất trong danh sách l2: " << oddMin << ": " << oddMin->data << endl;
	cout << endl;

	cout << "Test: Yeu cau 14. Cập nhật giá trị cho một node có giá trị là X bằng giá trị Y mới:" << endl;

	cout << "Cập nhật giá trị cho node có giá trị 11.5 bằng giá trị 12.5" << endl;
	cout << "Kết quả: " << updateValue(l, 11.5, 12.5) << endl;
	cout << "In danh sách liên kết l sau khi cập nhật giá trị" << endl;
	printList(l);

	cout << "Cập nhật gia tri cho node có giá trị 3.0 không có trong danh sách l" << endl;
	cout << "Kết quả: " << updateValue(l, 3.0, 4.0) << endl;
	cout << "In danh sách liên kết l sau khi cập nhật giá trị" << endl;
	printList(l);
	cout << endl;

	cout << "Test: Yeu cau 15. Copy danh sách:" << endl;
	cout << "Copy danh sách l sang danh sách l4" << endl;
	List l4;
	copyList(l, l4);
	cout << "In danh sách liên kết l4" << endl;
	printList(l4);
	cout << endl;

	return 0;
}