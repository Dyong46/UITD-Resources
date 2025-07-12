#include <iostream>

using namespace std;

/* Cau 1: Xây dựng cấu trúc dữ liệu có tên SinhVien lưu trữ các thông tin sau:
maSV, hoTen, diemTB, xepLoai... (hoặc lưu trữ thêm các thông tin khác nếu muốn).
*/
struct SinhVien
{
	int maSV;
	string hoTen;
	float diemTB;
	string xepLoai;
};

/* Cau 2: Xay dựng cấu trúc node để lưu trữ sinh viên và cấu trúc danh sách liên kết đơn quản lý sinh viên.
 */
struct Node
{
	SinhVien data;
	Node *pNext;
};

struct List
{
	Node *pHead;
	Node *pTail;
};

/* Cau 3: Viết hàm khởi tạo danh sách liên kết đơn và hàm khởi tạo địa chỉ node từ kiểu Sinh Vien.
 */
Node *initNode(SinhVien sv)
{
	Node *p = new Node;
	p->data = sv;
	p->pNext = NULL;

	return p;
}

void initList(List &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

/* Cau 4: Viết hàm thêm sinh viên vào đầu danh sách.
 */

void addHead(List &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

/* Cau 5: Viết hàm thêm sinh viên vào cuối danh sách.
 */
void addTail(List &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

/* Cau 6: Viết hàm khởi tạo dữ liệu cho danh sách sinh viên (Dữ liệu kiềm thử xem cuối bài).
Input:
	+ l: List&
Output:
	+ l: List&
 */
void initDataListSV(List &dsSV)
{
	SinhVien sv1 = {1, "Nguyen Van A", 8.5, ""};
	SinhVien sv2 = {2, "Nguyen Van B", 7.5, ""};
	SinhVien sv3 = {3, "Nguyen Van C", 6.5, ""};
	SinhVien sv4 = {4, "Nguyen Van D", 5.5, ""};
	SinhVien sv5 = {5, "Nguyen Van E", 4.5, ""};
	SinhVien sv6 = {6, "Nguyen Van F", 10, ""};
	SinhVien sv7 = {7, "Nguyen Van G", 9.5, ""};

	addHead(dsSV, initNode(sv1));
	addHead(dsSV, initNode(sv2));
	addHead(dsSV, initNode(sv3));
	addHead(dsSV, initNode(sv4));
	addHead(dsSV, initNode(sv5));
	addHead(dsSV, initNode(sv6));
	addHead(dsSV, initNode(sv7));

	addHead(dsSV, initNode({8, "Nguyen Van H", 8.5, ""}));
	addHead(dsSV, initNode({9, "Nguyen Van I", 10, ""}));
	addHead(dsSV, initNode({10, "Nguyen Van K", 4.5, ""}));
}

/* Cau 7: Viết hàm in danh sách sinh viên.
Input:
	+ l: List
Output:
	+ 
 */
void inSV(SinhVien sv)
{
	cout << "Thong tin sinh vien" << endl;
	cout << "\t+ Ma sinh vien   : " << sv.maSV << endl;
	cout << "\t+ Ho ten         : " << sv.hoTen << endl;
	cout << "\t+ Diem trung binh: " << sv.diemTB << endl;
	cout << "\t+ Xep loai       : " << sv.xepLoai << endl;
}

/*
Input:
	+ l: List
Output:
	+
*/
void printDSSV(List l)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong" << endl;
		return;
	}

	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		inSV(p->data);
	}
}

/* Cau 8: Viết hàm cập nhật xếp loại học lực.
Input:
	+ l: List&
Output:
	+ l: List&
 */
void updateXepLoai(List &l)
{
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		float diemTB = p->data.diemTB;
		if (diemTB >= 9)
		{
			p->data.xepLoai = "Xuat sac";
		}
		else if (diemTB >= 8)
		{
			p->data.xepLoai = "Gioi";
		}
		else if (diemTB >= 6.5)
		{
			p->data.xepLoai = "Kha";
		}
		else if (diemTB >= 5)
		{
			p->data.xepLoai = "Trung binh";
		}
		else
		{
			p->data.xepLoai = "Yeu";
		}
	}
}

/* Cau 9: Viết hàm tìm điểm trung bình cao nhất.
Input:
	+ l: List
Output:
	+ return float
 */
float diemTBCaoNhat(List l)
{
	float max = l.pHead->data.diemTB;
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.diemTB > max)
		{
			max = p->data.diemTB;
		}
	}

	return max;
}

/* Cau 10: Viết hàm tìm kiếm sinh viên theo mã sinh viên.
Input:
	+ l: List
Output:
	+ return Node*
 */
Node* findSV(List l, int maSV)
{
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.maSV == maSV)
		{
			return p;
		}
	}

	return NULL;
}

/* Cau 11: Viết hàm tìm SV có trung bình cao nhất.
	Note: Nếu có nhiều sinh viên có điểm trung bình cao nhất thì trả tẩt cả các sinh viên đó.
Input:
	+ l: List
Output:
	+ return List
 */

List findSVMax(List l)
{
	List dsSVMax = {NULL, NULL};

	float diemMax = diemTBCaoNhat(l);
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.diemTB == diemMax)
		{
			addTail(dsSVMax, initNode(p->data));
		}
	}

	return dsSVMax;
}

/* Bo sung: Viết hàm tìm điểm trung bình thấp nhất.
Input:
	+ l: List
Output:
	+ return float
*/

float diemTBThapNhat(List l)
{
	float min = l.pHead->data.diemTB;
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.diemTB < min)
		{
			min = p->data.diemTB;
		}
	}

	return min;
}

/* Cau 12: Viết hàm tìm SV có đểm trung bình thấp nhất.
	Note: Nếu có nhiều sinh viên có điểm trung bình thấp nhất thì trả tẩt cả các sinh viên đó.
Input:
	+ l: List
Output:
	+ return List
 */
List findSVMin(List l)
{
	List dsSVMin = {NULL, NULL};

	float diemMin = diemTBThapNhat(l);

	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.diemTB == diemMin)
		{
			addTail(dsSVMin, initNode(p->data));
		}
	}

	return dsSVMin;
}

int main()
{
	List dsSV;
	initList(dsSV);

	// 6
	cout << "\nTest: 6. Khoi tao data cho sv: " << endl;
	initDataListSV(dsSV);

	// 7
	cout << "\nTest: 7. In ds sv: " << endl;
	printDSSV(dsSV);

	// 8
	cout << "\nTest: 8. Cap nhat xep loai sv:  " << endl;
	updateXepLoai(dsSV);
	printDSSV(dsSV);

	// 9
	cout << "\nTest: 9. Tim diem trung binh cao nhat: " << endl;
	cout << "Diem trung binh cao nhat: " << diemTBCaoNhat(dsSV) << endl;

	// 10
	cout << "\nTest: 10. Tim kiem sv theo ma sv(3):  " << endl;
	Node *p = findSV(dsSV, 3);
	if (p != NULL)
	{
		inSV(p->data);
	}
	else
	{
		cout << "Khong tim thay sinh vien" << endl;
	}

	// 11
	cout << "\nTest: Viet ham tim sinh vien co diem trung binh cao nhat." << endl;
	List dsSVMax = findSVMax(dsSV);
	cout << "Danh sach sinh vien co diem trung binh cao nhat: " << endl;
	printDSSV(dsSVMax);

	// 12
	cout << "\nTest: Viet ham tim sinh vien co diem trung binh thap nhat. " << endl;
	List dsSVMin = findSVMin(dsSV);
	cout << "Danh sach sinh vien co diem trung binh thap nhat: " << endl;
	printDSSV(dsSVMin);

	return 0;
}