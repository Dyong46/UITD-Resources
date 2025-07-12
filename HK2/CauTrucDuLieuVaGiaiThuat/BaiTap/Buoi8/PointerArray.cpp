#include <iostream>

using namespace std;

void printArr(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
};

void printArray(int *a, int n)
{

	for (int i = 0; i < n; i++)
	{
		cout << *(a + i) << " ";
	}
	cout << endl;
};

bool linearSearch1(int a[], int n, int value)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == value)
			return true;
	}
	return false;
};

int* linearSearch2(int *a, int n, int value)
{
	for (int i = 0; i < n; i++)
	{
		if (*(a + i) == value)
			return a + i;
	}
	return NULL;
};

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

int* binarySearch2(int *a, int n, int value)
{
	int left = 0;
	int right = n - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (*(a + mid) == value)
			return a + mid;
		else if (*(a + mid) < value)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return NULL;
};

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

int* interplationSearch2(int *a, int n, int value)
{
	int left = 0;
	int right = n - 1;
	int mid;

	while (left <= right)
	{
		// L + ((R - L) / (a[R] - a[L])) * (value - a[L])
		mid = left + ((right - left) / (*(a + right) - *(a + left))) * (value - *(a + left));
		if (*(a + mid) == value)
			return a + mid;
		else if (*(a + mid) < value)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return NULL;
};

int main(){
	int a[100] = {5,3,7,5,9,1};
	int n = 6;

	
	cout << "Test 1: printArr" << endl;
	printArr(a, n);
	printArray(a, n);

	cout << "Test 2: linear Search" << endl;
	cout << "Ket qua tim 6(0): " << linearSearch1(a, n, 6) << endl;
	cout << "Ket qua tim 9(1): " << linearSearch1(a, n, 9) << endl;

	cout << "Ket qua tim 6(0): " << linearSearch2(a, n, 6) << endl;
	cout << "Ket qua tim 9(0x...): " << linearSearch2(a, n, 9) << endl;

	int b[100] = {23,45,67,89,91,99};
	int m = 6;
	cout << "Test 3: binary Search" << endl;
	cout << "Ket qua tim 6(0): " << binarySearch1(b, m, 6) << endl;
	cout << "Ket qua tim 91(1): " << binarySearch1(b, m, 91) << endl;

	cout << "Ket qua tim 6(0): " << binarySearch2(b, m, 6) << endl;
	cout << "Ket qua tim 91(0x...): " << binarySearch2(b, m, 91) << endl;

	cout << "Test 4: interplation Search" << endl;
	cout << "Ket qua tim 6(0): " << interplationSearch1(b, m, 6) << endl;
	cout << "Ket qua tim 91(1): " << interplationSearch1(b, m, 91) << endl;

	cout << "Ket qua tim 6(0): " << interplationSearch2(b, m, 6) << endl;
	cout << "Ket qua tim 91(0x...): " << interplationSearch2(b, m, 91) << endl;

	return 0;
}