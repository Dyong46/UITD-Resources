#include <iostream>
using namespace std;

int main()
{
	char c = 'F';
	int x = 10;
	double y = 3.14;

	cout << "Value of x: " << x << "\n";
	cout << "Address of x: " << &x << "\n"; // & đứng trước biến x là địa chỉ của biến x
	cout << "Value of x: " << *(&x); // * đứng trước địa chỉ &x là dữ liệu của biến x
	
	return 0;	
}