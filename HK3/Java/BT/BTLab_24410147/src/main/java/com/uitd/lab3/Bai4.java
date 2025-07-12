package com.uitd.lab3;

import java.util.Scanner;

public class Bai4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== BÀI 4: QUẢN LÝ SINH VIÊN ===");
        System.out.print("Nhập số lượng sinh viên: ");
        int n = scanner.nextInt();
        scanner.nextLine(); // Đọc bỏ ký tự xuống dòng

        if (n <= 0) {
            System.out.println("Số lượng sinh viên không hợp lệ!");
            return;
        }

        String[] hoTen = new String[n];
        double[] diem = new double[n];

        // Nhập thông tin sinh viên
        for (int i = 0; i < n; i++) {
            System.out.println("Sinh viên thứ " + (i + 1) + ":");
            System.out.print("Nhập họ tên: ");
            hoTen[i] = scanner.nextLine();
            System.out.print("Nhập điểm: ");
            diem[i] = scanner.nextDouble();
            scanner.nextLine(); // Đọc bỏ ký tự xuống dòng
        }

        // Xuất danh sách sinh viên với học lực
        System.out.println("\n=== DANH SÁCH SINH VIÊN ===");
        xuatDanhSachSinhVien(hoTen, diem);

        // Sắp xếp sinh viên theo điểm tăng dần
        sapXepTheoDiem(hoTen, diem);

        System.out.println("\n=== DANH SÁCH SINH VIÊN SAU KHI SẮP XẾP THEO ĐIỂM ===");
        xuatDanhSachSinhVien(hoTen, diem);

        scanner.close();
    }

    public static void xuatDanhSachSinhVien(String[] hoTen, double[] diem) {
        for (int i = 0; i < hoTen.length; i++) {
            System.out.println("Sinh viên " + (i + 1) + ":");
            System.out.println("Họ tên: " + hoTen[i]);
            System.out.println("Điểm: " + diem[i]);
            System.out.println("Học lực: " + xepLoaiHocLuc(diem[i]));
            System.out.println("------------------------");
        }
    }

    public static String xepLoaiHocLuc(double diem) {
        if (diem < 5) {
            return "Yếu";
        } else if (diem < 6.5) {
            return "Trung bình";
        } else if (diem < 7.5) {
            return "Khá";
        } else if (diem < 9) {
            return "Giỏi";
        } else {
            return "Xuất sắc";
        }
    }

    // Sắp xếp tăng dần theo điểm sử dụng thuật toán Bubble Sort
    public static void sapXepTheoDiem(String[] hoTen, double[] diem) {
        int n = diem.length;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (diem[j] > diem[j + 1]) {
                    // Hoán đổi điểm
                    double tempDiem = diem[j];
                    diem[j] = diem[j + 1];
                    diem[j + 1] = tempDiem;

                    // Hoán đổi họ tên tương ứng
                    String tempHoTen = hoTen[j];
                    hoTen[j] = hoTen[j + 1];
                    hoTen[j + 1] = tempHoTen;
                }
            }
        }
    }
}
