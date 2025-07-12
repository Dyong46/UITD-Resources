#include <iostream>
using namespace std;

struct NhanVien {
	int maNV;
	string hoTen;
	float luongCB;
	int soNL;
	float luongHT;
};

void initNhanVien(NhanVien& a) {
	printf("Nhap ma nhan vien: ");
	cin >> a.maNV;
	printf("Nhap ho ten: ");
	cin.ignore();
	getline(cin, a.hoTen);
	printf("Nhap luong co ban: ");
	cin >> a.luongCB;
	printf("Nhap so ngay lam: ");
	cin >> a.soNL;
}

void initArrNhanVien(NhanVien a[], int& soNV) {
	printf("========== Nhap thong tin nhan vien ==========\n");
	for (int i = 0; i < soNV; i++) {
		printf("======== Nhap thong tin nhan vien thu %d =========\n", i + 1);
		initNhanVien(a[i]);
	}
}

void inNhanVien(NhanVien a) {
	printf("Ma nhan vien: %d\n", a.maNV);
	printf("Ho ten: %s\n", a.hoTen.c_str());
	printf("Luong co ban: %.2f\n", a.luongCB);
	printf("So ngay lam: %d\n", a.soNL);
	printf("Luong hang thang: %.2f\n", a.luongHT);
};

void inArrNV(NhanVien a[], int soNV) {
	printf("\n========== Thong tin nhan vien ==========\n");
	for (int i = 0; i < soNV; i++)
	{
		printf("========== Thong tin nhan vien thu %d ========\n", i + 1);
		inNhanVien(a[i]);
	}
}

void tinhLuongHT(NhanVien a[], int soNV) {
	printf("\n========== Tinh luong hang thang ==========\n");
	for (int i = 0; i < soNV; i++)
	{
		float luongHT = a[i].luongCB + (a[i].soNL * 180000);
		printf("Luong hang thang cua nhan vien %s la: %.2f\n", a[i].hoTen.c_str(), luongHT);

		if (luongHT > 8000000) {
			a[i].luongHT = luongHT * 1.05;
		} else if (luongHT < 5000000) {
			a[i].luongHT = luongHT * 1.1;
		}
	}

	inArrNV(a, soNV);
}

void findNV(NhanVien a[], int soNV) {
	printf("\n========== Tim nhan vien theo ma nhan vien ==========\n");
	int maNV;
	printf("\nNhap ma nhan vien can tim: ");
	cin >> maNV;

	for (int i = 0; i < soNV; i++) {
		if (a[i].maNV == maNV) {
			printf("\n========== Thong tin nhan vien can tim ==========\n");
			inNhanVien(a[i]);
			return;
		}
	}
}

void findNVByLuongHTMin(NhanVien a[], int soNV) {
	printf("\n========== Tim cac nhan vien co luong hang thang thap nhat =========\n");

	float minLuongHT = a[0].luongHT;

	for (int i = 1; i < soNV; i++) {
		if (minLuongHT > a[i].luongHT) {
			minLuongHT = a[i].luongHT;
		}
	}

	printf("Luong hang thanh thap nhat: %.2f\n", minLuongHT);

	for (int i = 0; i < soNV; i++) {
		if (minLuongHT == a[i].luongHT) {
			printf("Nhan vien %s co maNV: %d\n", a[i].hoTen.c_str(), a[i].maNV);
		}
	}
}

void findNVByLuongCBMax(NhanVien a[], int soNV) {
	printf("\n========== Tim nhan vien co luong co bang cao nhat ==========\n");
	float maxLuongCB = a[0].luongCB;

	for(int i = 1; i < soNV; i++) {
		if (maxLuongCB < a[i].luongCB) {
			maxLuongCB = a[i].luongCB;
		}
	}

	printf("Luong co ban cao nhat: %.2f\n", maxLuongCB);

	for (int i = 0; i < soNV; i++) {
		if(maxLuongCB == a[i].luongCB) {
			printf("Nhan vien %s co maNV: %d\n", a[i].hoTen.c_str(), a[i].maNV);
		}
	}
}

int main() {
	NhanVien arrNV[100];
	int soNV = 2;

	// Yeu cau 1: Nhap thong tin nhan vien
	initArrNhanVien(arrNV, soNV);

	// // Yeu cau 2: In thong tin nhan vien
	inArrNV(arrNV, soNV);

	// Yeu cau 3: Tinh luong cho nhan vien
	tinhLuongHT(arrNV, soNV);

	// Yeu cau 4: Tinh tong tien hang thang cty phai tra cho toan bo nhan vien
	float tongTien = 0;
	for (int i = 0; i < soNV; i++)
	{
		tongTien += arrNV[i].luongHT;
	}
	printf("\nTong tien hang thang cty phai tra cho toan bo nhan vien la: %.2f\n", tongTien);

	// Yeu cau 5: Tinh tong luong hang thang cty phai tra cho nhan vien co luongCB < 5.000.000
	float tongTienNV = 0;
	for (int i = 0; i < soNV; i++) {
		if (arrNV[i].luongCB < 5000000) {
			tongTienNV += arrNV[i].luongHT;
		}
	}
	printf("\nTong tien hang thang cty phai tra cho nhan vien co luong co ban < 5.000.000 la: %.2f\n", tongTienNV);

	// Yeu cau 6: Tim cac nhan vien theo ma nhan vien
	findNV(arrNV, soNV);

	// Yeu cau 7: Tim cac nhan vien co luong hang thang thap nhat
	findNVByLuongHTMin(arrNV, soNV);

	// yeu cau 8: Tim cac nhan vien co luong co ban cao nhat
	findNVByLuongCBMax(arrNV, soNV);

	return 0;	
}