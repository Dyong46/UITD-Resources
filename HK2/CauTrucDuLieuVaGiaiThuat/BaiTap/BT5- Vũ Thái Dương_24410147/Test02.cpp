#include <iostream>

using namespace std;

struct Student
{
	int maSV;
	string hoTen;
	float diemMH;
};

struct Node
{
	Student student;
	Node *pNext;
};

Node *initNode(Student student)
{
	Node *p = new Node;
	p->student = student;
	p->pNext = NULL;

	return p;
}

struct List
{
	Node *pHead;
	Node *pTail;
};

void initList(List &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

/* Cau 1: Viết hàm chèn node chứa SV vào cuối danh sách. Nếu chèn thành công trả về true, thất bại trả về false.
Input:
	+ l: List&
	+ p: Node
Output:
	+ l: List&
	+ return: bool
*/
bool addTail(List &l, Node *p)
{
	try
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

		return true;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
}

/* Cau 2: Viết hàm xuất (in) danh sách sinh viên.
Input:
	+ l: List
Output:
	+
*/
void printStudent(Student data)
{
	cout << data.maSV << '\t' << data.hoTen << '\t' << data.diemMH << endl;
}

void printList(List l) {
	cout << endl << "================ IN DANH SACH SINH VIEN ================" << endl;

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
	}

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		printStudent(p->student);
	}

	cout << endl;
}

/* Cau 3: Viết hàm tìm kiếm SV theo mã SV. Nếu tìm thấy trả về địa chỉ của node, không tìm thấy trả về NULL.
Input:
	+ l: List
	+ maSV: int
Output:
	+ return: Node*
*/
Node* findByMaSV(List l, int maSV)
{
	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return NULL;
	}

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->student.maSV == maSV) {
			return p;
		}
	}

	return NULL;
}

/* Cau 4: Viết hàm đếm SV có điểm môn học dưới trung bình.
Input:
	+ l: List&
Output:
	+	count: int
*/
int countUnderAverage(List l)
{
	cout << endl << "================ DEM SINH VIEN CO DIEM DUOI TRUNG BINH ================" << endl;

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	int count = 0;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->student.diemMH < 5) {
			count++;
		}
	}

	return count;
}

/* Cau 5: Viêt hàm tính điêm trung bình của cả lớp.
Input:
	+ l: List
Output:
	+ return: float
*/
float calculateAverage(List l)
{
	cout << endl << "================ TINH DIEM TRUNG BINH CUA LOP ================" << endl;

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	float sum = 0;
	int count = 0;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		sum += p->student.diemMH;
		count++;
	}

	return sum / count;
}


/* Cau 6: Viết hàm hàm tìm mã SV đầu tiên có điêm môn học lớn nhất.
Input:
	+ l: List
Output:
	+	return: int
*/
int findMaxScore(List l)
{
	cout << endl << "================ TIM MA SV CO DIEM LON NHAT ================" << endl;

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	int max = l.pHead->student.diemMH;
	int maSV = l.pHead->student.maSV;

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->student.diemMH > max) {
			max = p->student.diemMH;
			maSV = p->student.maSV;
		}
	}

	return maSV;
}

/* Cau 7: Viết hàm trả về các mã SV có điểm môn học trên 8.
Input:
	+ l: List
Output:
	+ return: List
*/
List findStudentsAbove8(List l)
{
	cout << endl << "================ TIM MA SV CO DIEM LON HON 8 ================" << endl;

	List result;
	initList(result);

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return result;
	}

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->student.diemMH > 8) {
			Node* newNode = initNode(p->student);
			addTail(result, newNode);
		}
	}

	return result;
}

/* Cau 8: Viết hàm cập nhật điểm môn học theo mã sinh viên.
Input:
	+ l: List&
	+ maSV: int
	+ newScore: float
Output:
	+ 
*/
void updateScoreByMaSV(List &l, int maSV, float newScore)
{
	cout << endl << "================ CAP NHAT DIEM MON HOC THEO MASV ================" << endl;

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return;
	}

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		if(p->student.maSV == maSV) {
			p->student.diemMH = newScore;
			break;
		}
	}
}

/* Cau 9: Viết hàm sao chép các SV sang một danh sách mới. Phân tích ý tưởng thực hiện.
Input:
	+ l: List
Output:
	+ return: List
*/
List copyList(List l)
{
	cout << endl << "================ SAO CHEP DANH SACH SINH VIEN ================" << endl;

	List result;
	initList(result);

	if(l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return result;
	}

	for(Node* p = l.pHead; p != NULL; p = p->pNext) {
		Node* newNode = initNode(p->student);
		addTail(result, newNode);
	}

	return result;
}

/* Cau 10: Trong hàm main, tạo 6 SV có dữ liệu sau (không dùng cin):
Input:
	+ l: List&
Output:
	+
*/

int main()
{
	List l;
	initList(l);

	cout << "Khoi tao data cho danh sach sinh vien: " << endl;
	addTail(l, initNode({123, "Nguyen Van A", 8.8}));
	addTail(l, initNode({124, "Nguyen Van B", 9.7}));
	addTail(l, initNode({125, "Nguyen Van C", 2.9}));
	addTail(l, initNode({126, "Nguyen Van D", 9.7}));
	addTail(l, initNode({127, "Nguyen Van E", 4.8}));
	addTail(l, initNode({128, "Nguyen Van F", 7.5}));

	cout << "Test 2: In danh sach sinh vien: " << endl;
	printList(l);

	cout << "Test 3: Tim kiem sinh vien theo maSV(124): " << endl;
	Node* p = findByMaSV(l, 124);
	if(p != NULL) {
		printStudent(p->student);
	} else {
		cout << "Khong tim thay sinh vien" << endl;
	}
	cout << endl;

	cout << "Test 4: Dem so sinh vien co diem duoi trung binh: " << countUnderAverage(l) << endl << endl;

	cout << "Test 5: Tinh diem trung binh cua lop: " << calculateAverage(l) << endl << endl;

	cout << "Test 6: Tim maSV co diem cao nhat: " << findMaxScore(l) << endl << endl;

	cout << "Test 7: Tim sinh vien co diem > 8: " << endl;
	List result = findStudentsAbove8(l);
	printList(result);
	cout << endl;

	cout << "Test 8: Cap nhat diem mon hoc theo maSV(123) - 10.0: " << endl;
	updateScoreByMaSV(l, 123, 10.0);
	cout << "Danh sach sinh vien sau khi cap nhat: " << endl;
	printList(l);
	cout << endl;

	cout << "Test 9: Sao chep danh sach sinh vien: " << endl;
	List copiedList = copyList(l);
	printList(copiedList);
	cout << "Danh sach sinh vien goc: " << endl;
	printList(l);
	cout << "Danh sach sinh vien da sao chep: " << endl;
	printList(copiedList);

	return 0;
}