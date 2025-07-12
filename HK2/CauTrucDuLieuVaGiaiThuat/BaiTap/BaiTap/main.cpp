#include <iostream>

using namespace std;

struct SanPham {
	int maSP;
	string tenSP;
	int soLuong;
	float donGia;
};

typedef SanPham SP;

struct Node {
	SP sp;
	Node *pNext;
	Node *pPrev;
};

Node* initNode(SP sp) {
	Node* p = new Node;
	p->sp = sp;
	p->pNext = NULL;
	p->pPrev = NULL;

	return p;
}

struct List {
	Node* pHead;
	Node* pTail;
};

void initList(List &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

/* Câu 1. Viết hàm chèn node chứa sản phẩm vào cuối danh sách. Nếu chèn thành công trả về 1, thất bại trả về -1.
Input:
	+ l: List&
	+ p: Node*
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
			p->pPrev = l.pTail;
			l.pTail = p;
		}
		return 1;
	}
	catch (...)
	{
		return -1;
	}
}

/* Cau 2. Viết hàm in danh sách các sản phẩm.
Input:
	+ l: List
Output:
	+ return: void
*/
void print(List l)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return;
	}

	cout << endl << "================ IN DANH SACH SAN PHAM ================" << endl;
	cout << "MaSP\tTenSP\tSoLuong\tDonGia" << endl;

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		printf("%d\t%s\t%d\t%.2f\n", p->sp.maSP, p->sp.tenSP.c_str(), p->sp.soLuong, p->sp.donGia);
	}
}

/* Câu 3. Viết hàm tìm kiếm sản phẩm theo mã sản phẩm. Nếu tìm thấy thì trả về địa chỉ của node, không tìm thấy trả về NULL.
Input:
	+ l: List
	+ maSP: int
Output:
	+ return: Node*
*/
Node* findByMaSP(List l, int maSP)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return NULL;
	}

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->sp.maSP == maSP)
			return p;
	}
	return NULL;
}

/* Câu 4. Viết hàm đếm số lượng các sản phẩm có trong danh sách.
Input:
	+ l: List
Output:
	+ count: int
*/
int countQuantityProducts(List l)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	int count = 0;
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		count ++;
	}
	return count;
}

/* Câu 5. Viết hàm tính tổng đơn giá của các sản phẩm có trong danh sách.
Input:
	+ l: List
Output:
	+ return: double
*/
double calculateTotalPrice(List l)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	double total = 0;
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		total += p->sp.donGia * p->sp.soLuong;
	}
	return total;
}

/* Câu 6. Viết hàm tìm tên sản phẩm có số lượng nhỏ nhất.
Input:
	+ l: List
Output:
	+ return: string
*/
string findMinQuantityProduct(List l)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return "";
	}

	SanPham minProductPrice = l.pHead->sp;

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->sp.soLuong < minProductPrice.soLuong)
		{
			minProductPrice = p->sp;
		}
	}
	return minProductPrice.tenSP;
}

/* Câu 7. Viết hàm tìm giá trị tổng tiền nhỏ nhất.
Input:
	+ l: List
Output:
	+ return: float
*/
float findMinTotalPrice(List l)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	float minTotalPrice = l.pHead->sp.donGia * l.pHead->sp.soLuong;

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		float totalPrice = p->sp.donGia * p->sp.soLuong;
		if (totalPrice < minTotalPrice)
		{
			minTotalPrice = totalPrice;
		}
	}
	return minTotalPrice;
}

/* Câu 8. Viết hàm cập nhật tên sản phẩm theo mã sản phẩm.
Input:
	+ l: List&
	+ maSP: int
	+ newName: string
Output:
	+ l: List&
	+ return: bool
*/
bool updateProductNameByMaSP(List &l, int maSP, string newName)
{
	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return 0;
	}

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->sp.maSP == maSP)
		{
			p->sp.tenSP = newName;
			return 1;
		}
	}
	return 0;
}

/* Câu 9. Viết hàm tạo một danh sách san pham mới có số luong sản phẩm > 70.
Input:
	+ l: List
Output:
	+ return: List
*/
List createInvoiceList(List l)
{
	List result;
	initList(result);

	if (l.pHead == NULL)
	{
		cout << "Danh sach rong";
		return result;
	}

	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->sp.soLuong > 70)
		{
			Node* newNode = initNode(p->sp);
			addTail(result, newNode);
		}
	}
	return result;
}

//  Dữ liệu kiểm thử: 6 sản phẩm có dữ liệu sau (không dùng cin):
// {500, "G31", 96, 5e6}
// {501, "N56", 82, 7e6}
// {502, "S12", 51, 9e5}
// {503, "B89", 51, 7e4}
// (504, "H12", 82, 8e5}
// (505, "T36", 96, 5e6}
int main()
{
	List l;
	initList(l);

	cout << "==== DE 2 ====" << endl;
	cout << "Goi ham cau 1" << endl;
	cout << "SP{500, 'G31', 96, 5e6} = " << addTail(l, initNode({500, "G31", 96, 5e6})) << endl;
	cout << "SP{501, 'N56', 82, 7e6} = " << addTail(l, initNode({501, "N56", 82, 7e6})) << endl;
	cout << "SP{502, 'S12', 51, 9e5} = " << addTail(l, initNode({502, "S12", 51, 9e5})) << endl;
	cout << "SP{503, 'B89', 51, 7e4} = " << addTail(l, initNode({503, "B89", 51, 7e4})) << endl;
	cout << "SP{504, 'H12', 82, 8e5} = " << addTail(l, initNode({504, "H12", 82, 8e5})) << endl;
	cout << "SP{505, 'T36', 96, 5e6} = " << addTail(l, initNode({505, "T36", 96, 5e6})) << endl;
	cout << endl;

	cout << "Goi ham cau 2" << endl;
	print(l);
	cout << endl;

	cout << "Goi ham cau 3" << endl;
	cout << "Tim SP co maSP = 501(N56): " << findByMaSP(l, 501)->sp.tenSP << endl;
	cout << "Tim SP co maSP = 100(0x0): " << findByMaSP(l, 100) << endl;
	cout << endl;

	cout << "Goi ham cau 4" << endl;
	cout << "So luong san pham(6): " << countQuantityProducts(l) << endl;
	cout << endl;

	cout << "Goi ham cau 5" << endl;
	printf("Tong don gia san pham(1649070000): %.2f\n", calculateTotalPrice(l));
	cout << endl;

	cout << "Goi ham cau 6" << endl;
	cout << "Ten san pham co so luong nho nhat(S12): " << findMinQuantityProduct(l) << endl;
	cout << endl;

	cout << "Goi ham cau 7" << endl;
	printf("Gia tri tong tien nho nhat: %.2f\n", findMinTotalPrice(l));
	cout << endl;

	cout << "Goi ham cau 8" << endl;
	cout << "Cap nhat ten san pham co maSP = 501, tenSP = N99: " << updateProductNameByMaSP(l, 501, "N99") << endl;
	cout << "Ten san pham co maSP = 501(N99): " << findByMaSP(l, 501)->sp.tenSP << endl;
	cout << endl;

	cout << "Cap nhat ten san pham co maSP = 100, tenSP = N100: " << updateProductNameByMaSP(l, 100, "N100-Updated") << endl;
	cout << endl;

	cout << "Goi ham cau 9" << endl;
	cout << "Tao danh sach hoa don moi co so luong san pham > 70:" << endl;
	List invoiceList = createInvoiceList(l);
	cout << "Danh sach hoa don:" << endl;
	print(invoiceList);

	return 0;
}