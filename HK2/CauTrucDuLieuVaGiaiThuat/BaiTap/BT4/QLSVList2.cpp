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
	Node *pPrev;
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
	p->pPrev = NULL;

	return p;
}

void initList(List &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

/* Cau 4: Viết hàm thêm sinh viên vào đầu danh sách.
 */
void pushHead(List &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		p->pNext = l.pHead;
		l.pHead->pPrev = p;
		l.pHead = p;
	}
}

/* Cau 5: Viết hàm thêm sinh viên vào cuối danh sách.
 */
void pushTail(List &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		p->pPrev = l.pTail;
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
int initDataListSV(List& l) {
	SinhVien sv1 = {1, "Nguyen Van A", 8.5, ""};
	SinhVien sv2 = {2, "Nguyen Van B", 7.5, ""};
	SinhVien sv3 = {3, "Nguyen Van C", 6.5, ""};
	SinhVien sv4 = {4, "Nguyen Van D", 5.5, ""};
	SinhVien sv5 = {5, "Nguyen Van E", 4.5, ""};
	SinhVien sv6 = {6, "Nguyen Van F", 10, ""};
	SinhVien sv7 = {7, "Nguyen Van G", 9.5, ""};

	pushHead(l, initNode(sv1));
	pushHead(l, initNode(sv2));
	pushHead(l, initNode(sv3));
	pushHead(l, initNode(sv4));
	pushHead(l, initNode(sv5));
	pushHead(l, initNode(sv6));
	pushHead(l, initNode(sv7));

	pushHead(l, initNode({8, "Nguyen Van H", 8.5, ""}));
	pushHead(l, initNode({9, "Nguyen Van I", 10, ""}));
	pushHead(l, initNode({10, "Nguyen Van K", 4.5, ""}));

	return 10;
}

void inSV(SinhVien sv)
{
	printf("[%d, %s, %.2f, %s]\n", sv.maSV, sv.hoTen.c_str(), sv.diemTB, sv.xepLoai.c_str());
}

/* Cau 7: Viết hàm in danh sách sinh viên.
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

	cout << endl << "In tu pHead den pTail:" << endl;
	for (Node *p = l.pHead; p != NULL; p = p->pNext)
	{
		
		inSV(p->data);
	}

	cout << endl << "In tu pTail ve pHead:" << endl;
	for (Node *p = l.pTail; p != NULL; p = p->pPrev)
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
Node *findSV(List l, int maSV)
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
			pushTail(dsSVMax, initNode(p->data));
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
			pushTail(dsSVMin, initNode(p->data));
		}
	}

	return dsSVMin;
}

int main()
{
	List dsSV;
	initList(dsSV);

	cout << "\nTest: 6. Khoi tao data cho sv: " << endl;
	int siSo = initDataListSV(dsSV);
	cout << "Si so: " << siSo << endl;

	cout << "\nTest: 7. In ds sv: " << endl;
	printDSSV(dsSV);
	
	cout << "\nTest: 8. Cap nhat xep loai sv:  " << endl;
	updateXepLoai(dsSV);
	printDSSV(dsSV);

	cout << "\nTest: 9. Tim diem trung binh cao nhat: " << endl;
	cout << "Diem trung binh cao nhat: " << diemTBCaoNhat(dsSV) << endl;

	cout << "\nTest: 10. Tim sinh vien theo ma sinh vien: " << endl;
	Node *p = findSV(dsSV, 3);
	if (p != NULL)
	{
		cout << "Sinh vien co ma sinh vien 3: " << endl;
		inSV(p->data);
	}
	else
	{
		cout << "Khong tim thay sinh vien co ma sinh vien 3" << endl;
	}

	Node *p2 = findSV(dsSV, 15);
	if (p2 != NULL)
	{
		cout << "Sinh vien co ma sinh vien 15: " << endl;
		inSV(p2->data);
	}
	else
	{
		cout << "Khong tim thay sinh vien co ma sinh vien 15" << endl;
	}

	cout << "\nTest: 11. Tim sinh vien co diem trung binh cao nhat: " << endl;
	List dsSVMax = findSVMax(dsSV);
	cout << "Cac sinh vien co diem trung binh cao nhat: " << endl;
	printDSSV(dsSVMax);

	cout << "\nTest: 12. Tim sinh vien co diem trung binh thap nhat: " << endl;
	List dsSVMin = findSVMin(dsSV);
	cout << "Cac sinh vien co diem trung binh thap nhat: " << endl;
	printDSSV(dsSVMin);

	return 0;
}