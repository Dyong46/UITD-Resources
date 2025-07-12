#include <iostream>
#include <forward_list>

using namespace std;

struct SinhVien
{
	int maSV;
	string hoTen;
	float diemTB;
	string xepLoai;
};

int main()
{
	forward_list<SinhVien> ds;

	forward_list<int> l;

	l.push_front(1);
	l.push_front(2);
	l.push_front(3);
	l.push_front(5);
	l.push_front(7);
	l.push_front(9);

	for(int x : l)
	{
		cout << x << " ";
	}
	return 0;
}