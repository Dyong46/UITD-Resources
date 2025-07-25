package com.uitd.lab4;

import java.util.Scanner;

public class SanPham {
    private String tenSanPham;
    private double donGia;
    private double giamGia;

    public SanPham(String tenSanPham, double donGia, double giamGia) {
        this.tenSanPham = tenSanPham;
        this.donGia = donGia;
        this.giamGia = giamGia;
    }

    public SanPham(String tenSp, double donGia) {
        this(tenSp, donGia, 0);
    }

    public String getTenSanPham() {
        return tenSanPham;
    }

    public void setTenSanPham(String tenSanPham) {
        this.tenSanPham = tenSanPham;
    }

    public double getDonGia() {
        return donGia;
    }

    public void setDonGia(double donGia) {
        this.donGia = donGia;
    }

    public double getGiamGia() {
        return giamGia;
    }

    public void setGiamGia(double giamGia) {
        this.giamGia = giamGia;
    }

    private double getThueNhapKhau() {
        return donGia * 0.1;
    }

    public  void xuat() {
        System.out.println("Tên sản phẩm: " + tenSanPham);
        System.out.println("Đơn giá: " + donGia);
        System.out.println("Giảm giá: " + giamGia);
        System.out.println("Thuế nhập khẩu: " + getThueNhapKhau());
    }

    public void nhap() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Nhập tên sản phẩm: ");
        this.tenSanPham = scanner.nextLine();
        System.out.print("Nhập đơn giá: ");
        this.donGia = Double.parseDouble(scanner.nextLine());
        System.out.print("Nhập giảm giá: ");
        this.giamGia = Double.parseDouble(scanner.nextLine());
    }
}
