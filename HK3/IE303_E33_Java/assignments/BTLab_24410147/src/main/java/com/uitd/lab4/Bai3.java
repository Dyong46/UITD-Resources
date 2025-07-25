package com.uitd.lab4;

public class Bai3 {
    public static void main(String[] args) {
        SanPham sanPham1 = new SanPham("Sản phẩm A", 100000, 5000);
        SanPham sanPham2 = new SanPham("Sản phẩm B", 200000);

        System.out.println("Thông tin sản phẩm 1:");
        sanPham1.xuat();
        System.out.println("Thông tin sản phẩm 2:");
        sanPham2.xuat();
    }
}
