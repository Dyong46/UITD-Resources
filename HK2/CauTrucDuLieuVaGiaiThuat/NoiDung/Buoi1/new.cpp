#include <iostream>
using namespace std;

int main()
{
	// Cấp phát tĩnh sau khi khởi tạo biến thì không thể xóa khỏi bộ nhớ
	int x = 10;
	float y = 8.5;

	int a[100];

	// Cấp phát động sau khi khởi tạo biến thì có thể xóa khỏi bộ nhớ
	// cấp phát: new
	// giải phóng: delete
	new int;
	new double;

	int* p = new int;
	*p = 10;

	printf("Address in new int: %p\n", p);
	printf("Value in new int: %d\n", *p);

	// Thu hồi p, giải phóng bộ nhớ
	delete p;
	// p = NULL;

	printf("Address in 'new int' after delete: %p\n", p);
	printf("Value in 'new int' after delete: %d\n", *p);
	
	return 0;	
}