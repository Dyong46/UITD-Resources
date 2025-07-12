#include <iostream>
#include <iomanip>

using namespace std;

/* Cau 1: Viết hàm khởi tạo tự động 100000 phần tử kiểu số thực (lấy 3 số sau dấu thập phân) cho mảng.
Input:
	+ a[]: double array
	+ n: &int
Output:
	+ n: &int
*/
void initDatRandom100k(double a[], int &n)
{
	n = 100;
	for (int i = 0; i < n; i++)
	{
		a[i] = ((rand() % 10000000) / 1000.0);
	}
}

/* Cau 2: Viết hàm xuất các giá trị trong mảng.
*/
void printArr(double a[], int n)
{
	for (int i = 0; i < n * 0.1; i++)
	{
		cout << a[i] << "\n";
	}
	cout << endl;
};

/* Cau 3: Viết hàm sắp xếp mảng tăng/giảm dần bằng thuật toán chọn trực tiếp.
Input:
	+ a[]: double array
	+ n: int
Output:
	+ a[]: double array
*/
void selectionSort(double a[], int n)
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
			double temp = a[i];
			a[i] = a[m];
			a[m] = temp;
		}
	}
}

/* Cau 4: Viết hàm tính thời gian thực hiện sắp xếp mảng tăng/giảm dần bằng thuật toán chọn trực tiếp.
Input:
	+ a[]: double array
	+ n: int
Output:
	+ a[]: double array
*/
double timeselectionSort(double a[], int n)
{
	double s = clock();
	selectionSort(a, n);
	double e = clock();

	return (double)(e - s) / CLOCKS_PER_SEC;
}

/* Cau 5: Viết hàm sắp xếp mảng tăng/giảm dần bằng thuật toán chèn trực tiếp.
Input:
	+ a[]: double array
	+ n: int
Output:
	+ a[]: double array
*/
void insertionSort(double a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		double item = a[i];
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

/* Cau 6: Viết hàm tính thời gian thực hiện sắp xếp mảng tăng/giảm dần bằng thuật toán chèn trực tiếp.
Input:
	+ a[]: double array
	+ n: int
Output:
	+ a[]: double array
*/
double timeinsertionSort(double a[], int n)
{
	double s = clock();
	insertionSort(a, n);
	double e = clock();

	return (double)(e - s) / CLOCKS_PER_SEC;
}

/* Cau 7: Viêt hàm so sánh thời gian thực hiện sắp xêp mảng tăng/giảm dân của hai thuật toán chọn trực tiếp và chèn trực tiếp trên cùng một bộ dữ liệu mảng
Input:
	+ a[]: double array
	+ n: int
Output:
	+ a[]: double array
*/
void compareSort(double a[], int n)
{
	double time1 = timeselectionSort(a, n);
	double time2 = timeinsertionSort(a, n);

	cout << "Thoi gian thuc hien thuat toan chon truc tiep: " << time1 << endl;
	cout << "Thoi gian thuc hien thuat toan chen truc tiep: " << time2 << endl;

	if (time1 < time2)
	{
		cout << "Thuat toan chon truc tiep nhanh hon" << endl;
	}
	else
	{
		cout << "Thuat toan chen truc tiep nhanh hon" << endl;
	}
}

/* Cau 8: Áp dụng minh họa thực nghiệm cho 15 bộ dữ liệu được tạo tự động ngẫu nhiên
*/
double a[(int)1e6];
int main()
{

	int n = 0;
	initDatRandom100k(a, n);
	printArr(a, n);

	compareSort(a, n);
	
	return 0;
}