#include <iostream>
using namespace std;

int main()
{
	int x = 10;

	// int* là kiểu dữ liệu con trỏ trỏ đến kiểu dữ liệu int
	// Khai báo con trỏ kiểu int*
	// int* p || int *p || int * p
	int* p = &x;

	//  p1, p2 là con trỏ kiểu int
	// p3 là biến kiểu int
	int *p1, * p2, p3;

	// Thay đổi giá trị của biến x thông qua con trỏ p
	*p = 30; 

	cout << "Value of x: " << x << "\n";
	cout << "Value of x: " << *p << "\n";

	// In ra địa chỉ của biến x
	cout << "Value of x: " << p << "\n";
	cout << "Address of x: " << &p << "\n";
	
	return 0;	
}