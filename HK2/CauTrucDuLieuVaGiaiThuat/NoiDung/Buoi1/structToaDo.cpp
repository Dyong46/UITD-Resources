#include <iostream>
using namespace std;

struct ToaDo
{
	
	int x;
	int y;
};

void inToaDo(ToaDo a) {
	cout << "(" << a.x << ", " << a.y << ")" << endl;
}

int main()
{
	int x = 8;
	cout << x << "\n";

	ToaDo a = {1, 2};
	// cout << a << "\n"; // Do ToaDo chưa được định nghĩa
	inToaDo(a);
	
	ToaDo* p = new ToaDo;

	p ->x = 3;
	p ->y = 4;
	// or
	*p = {3, 4};
	// or
	(*p).x = 3;
	(*p).y = 4;

	inToaDo(*p);

	return 0;	
}