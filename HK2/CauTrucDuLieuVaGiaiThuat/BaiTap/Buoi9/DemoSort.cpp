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

void selectionSort(int a[], int n)
{
	int m;
	for (int i = 0; i < n - 1; i++)
	{
		m = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[m])
			{
				m = j;
			}
		}
		if (m != i)
		{
			int temp = a[i];
			a[i] = a[m];
			a[m] = temp;
		}
	}
}

void insertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int item = a[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (a[j] < item)
				break;

			a[j + 1] = a[j];
		}
		a[j + 1] = item;
	}
}

double timeSort(int a[], int n, int loai) {
	if(loai == 1) {
		double s = clock();
		selectionSort(a, n);
		double e = clock();

		return (double) (e - s)/CLOCKS_PER_SEC;
	} else if(loai == 2) {
		double s = clock();
		insertionSort(a, n);
		double e = clock();

		return (double) (e - s)/CLOCKS_PER_SEC;
	}
	return 0.0;
}

int main()
{
	cout << "Hello, World!" << endl;
	int a[100] = {12, 90, 50, 28, 45, 68};
	printArr(a, 6);

	cout << "Time: " << timeSort(a, 6, 1) << endl;
	printArr(a, 6);

	cout << "Time: " << timeSort(a, 6, 2) << endl;
	printArr(a, 6);

	return 0;
}