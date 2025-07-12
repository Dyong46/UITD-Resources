#include <iostream>
#include <time.h>

using namespace std;

/* Cau1: Viết hàm nhập giá trị tự động cho mảng, các giá trị thuộc [100; 999], số lượng phần tử thuộc [30; 50].
*/
void initDataAuto1(int* a, int& n)
{
	n = rand() % (50 - 30 + 1) + 30;

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (999 - 100 + 1) + 100;
	}
}

/* Cau 2: Viết hàm nhập giá trị tự động tăng dần cho mảng, phần tử đầu tiên ≤ 130, các phần tử kề nhau không quá 15, các giá trị thuộc [100; 999], số lượng phần tử thuộc [30; 50].
*/
void initDataAuto2(int* a, int& n)
{
	n = rand() % (50 - 30 + 1) + 30;
	a[0] = rand() % (130 - 100 + 1) + 100;

	for (int i = 1; i < n; i++)
	{
		a[i] = a[i - 1] + rand() % (15 - 1 + 1) + 1;
	}
}

/* Cau 2(nang cao): Viết hàm nhập giá trị tự động tăng dần cho mảng, phần tử đầu tiên ≤ 130, các phần tử kề nhau không quá 15, các giá trị thuộc [100; 250], số lượng phần tử thuộc [30; 50].
*/
void initDataAuto3(int* a, int& n)
{
	n = rand() % (50 - 30 + 1) + 30;
	a[0] = rand() % (130 - 100 + 1) + 100;

	for (int i = 1; i < n; i++)
	{
		a[i] = a[i - 1] + rand() % (15 - 1 + 1) + 1;
	}
}

/*n Cau 3: Viết hàm xuất mảng.
*/
void printArr(int a[], int n)
{
	cout << "Number: " << n << endl;
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
};

/* Cau 4: Viết hàm tìm kiếm một phần tử trong mảng bằng tìm kiếm tuyến tính.
Input:
	+ a[]: int array
	+ n: int
	+ value: int
Output:
	+ return: bool
*/
bool linearSearch1(int a[], int n, int value)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == value)
			return true;
	}
	return false;
};

/* Cau 5: Viết hàm tìm kiếm một phần tử trong mảng bằng tìm kiếm nhị phân.
Input:
	+ a[]: int array
	+ n: int
	+ value: int
Output:
	+ return: bool
*/
bool binarySearch1(int a[], int n, int value)
{
	int left = 0;
	int right = n - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (a[mid] == value)
			return true;
		else if (a[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return false;
};

/* Cau 6: Viết hàm tìm kiếm một phần tử trong mảng bằng tìm kiếm nội suy.
Input:
	+ a[]: int array
	+ n: int
	+ value: int
Output:
	+ return: bool
*/
bool interplationSearch1(int a[], int n, int value)
{
	int left = 0;
	int right = n - 1;
	int mid;

	while (left <= right)
	{
		// L + ((R - L) / (a[R] - a[L])) * (value - a[L])
		mid = left + ((right - left) / (a[right] - a[left])) * (value - a[left]);
		if (a[mid] == value)
			return true;
		else if (a[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return false;
};

/* Cau 7: Viết hàm so sánh số lần thực hiện tìm kiếm cùng một giá trị cho 3 thuật toán tìm kiếm trên.
Input:
	+ a[]: int array
	+ n: int
	+ value: int
Output:
*/
void compareSearch(int a[], int n, int value)
{
	int linearCount = 0;
	int binaryCount = 0;
	int interplationCount = 0;

	// Linear Search
	for (int i = 0; i < n; i++)
	{
		linearCount++;
		if (a[i] == value)
			break;
	}

	// Binary Search
	int left = 0;
	int right = n - 1;
	while (left <= right)
	{
		binaryCount++;
		int mid = (left + right) / 2;
		if (a[mid] == value)
			break;
		else if (a[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}

	// Interpolation Search
	left = 0;
	right = n - 1;
	while (left <= right)
	{
		interplationCount++;
		int mid = left + ((right - left) / (a[right] - a[left])) * (value - a[left]);
		if (a[mid] == value)
			break;
		else if (a[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}

	cout << "Linear Search Count: " << linearCount << endl;
	cout << "Binary Search Count: " << binaryCount << endl;
	cout << "Interpolation Search Count: " << interplationCount << endl;
}

int main(){
	srand(time(0));
	int* a1 = new int[100];
	int n1 = 0;

	cout << "Test 1: Init data auto value from [100; 999], and quantity [30; 50]" << endl;
	initDataAuto1(a1, n1);
	cout << "Test 1: printArr" << endl;
	printArr(a1, n1);

	cout << endl;

	int* a2 = new int[100];
	int n2 = 0;
	cout << "Test 2: Init data auto value from [100; 999], and quantity [30; 50]. The first value <= 130, each value must not differ by more than 15" << endl;
	initDataAuto2(a2, n2);
	cout << "Test 2: printArr" << endl;
	printArr(a2, n2);

	cout << endl;

	int* a3 = new int[100];
	int n3 = 0;
	cout << "Test 3: Init data auto value from [100; 250], and quantity [30; 50]. The first value <= 130, each value must not differ by more than 15" << endl;
	initDataAuto3(a3, n3);
	cout << "Test 3: printArr" << endl;
	printArr(a3, n3);

	cout << endl;

	cout << "Test 4: Search value: 9 in array 2: " << linearSearch1(a1, n2, 9) << endl;
	cout << "Test 4: Search value: 117 in array 2: " << linearSearch1(a2, n2, 117) << endl;
	cout << endl;

	cout << "Test 5: Search value: 9 in array 2: " << binarySearch1(a3, n2, 99) << endl;
	cout << "Test 5: Search value: 117 in array 2: " << binarySearch1(a3, n2, 117) << endl;
	cout << endl;

	cout << "Test 6: Search value: 9 in array 2: " << interplationSearch1(a3, n2, 9) << endl;
	cout << "Test 6: Search value: 117 in array 2: " << interplationSearch1(a3, n2, 117) << endl;
	cout << endl;

	cout << "Test 7: Compare search value: 9 in array 2" << endl;
	compareSearch(a1, n2, 9);

	cout << endl;

	cout << "Test 7: Compare search value: 117 in array 2" << endl;
	compareSearch(a1, n2, 117);
	cout << endl;

	return 0;
}