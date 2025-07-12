package com.uitd.lab2;

import java.util.Scanner;

public class Bai3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== BÀI 3: TÍNH TIỀN ĐIỆN THEO PHƯƠNG PHÁP LŨY TIẾN ===");
        System.out.print("Nhập số điện sử dụng trong tháng (kWh): ");
        int soDien = scanner.nextInt();

        if (soDien < 0) {
            System.out.println("Số điện không hợp lệ!");
        } else {
            int tienDien = tinhTienDien(soDien);
            System.out.println("Số điện sử dụng: " + soDien + " kWh");
            System.out.println("Tiền điện phải trả: " + tienDien + " VND");
        }

        scanner.close();
    }

    public static int tinhTienDien(int soDien) {
        int tien;

        if (soDien <= 50) {
            tien = soDien * 1000;
        } else {
            tien = 50 * 1000 + (soDien - 50) * 1200;
        }

        return tien;
    }
}
