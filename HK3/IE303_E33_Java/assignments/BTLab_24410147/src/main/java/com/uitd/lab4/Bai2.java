package com.uitd.lab4;

public class Bai2 {
    public static void main() {
        SanPham sanPham1 = new SanPham();
        SanPham sanPham2 = new SanPham();

        System.out.println("Nhập thông tin sản phẩm 1:");
        sanPham1.nhap();
        System.out.println("Nhập thông tin sản phẩm 2:");
        sanPham2.nhap();

        System.out.println("Thông tin sản phẩm 1:");
        sanPham1.xuat();
        System.out.println("Thông tin sản phẩm 2:");
        sanPham2.xuat();
    }
}
