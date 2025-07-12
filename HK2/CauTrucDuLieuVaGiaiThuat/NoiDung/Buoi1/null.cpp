#include <iostream>
using namespace std;

int main()
{
	// Khi khai báo kiểu con trỏ và không gán giá trị địa chỉ nào hết thì con trỏ đó chưa khởi tạo.
	int* p1 ;

  // Nếu gán giá trị NULL cho con trỏ thì gọi là con trỏ NULL, sẽ không trỏ vào địa chỉ của biến nào cả.
	int* p2 = NULL;

	int n = 36;
	int* p3 = &n;

	cout << p1 << "\n";
	cout << p2 << "\n";
	cout << p3 << "\n";
	
	return 0;	
}