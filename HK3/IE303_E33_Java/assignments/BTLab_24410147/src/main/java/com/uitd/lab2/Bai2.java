package com.uitd.lab2;

import java.util.Scanner;

public class Bai2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== BÀI 2: GIẢI PHƯƠNG TRÌNH BẬC HAI ax² + bx + c = 0 ===");
        System.out.print("Nhập hệ số a: ");
        double a = scanner.nextDouble();
        System.out.print("Nhập hệ số b: ");
        double b = scanner.nextDouble();
        System.out.print("Nhập hệ số c: ");
        double c = scanner.nextDouble();

        giaiPhuongTrinhBacHai(a, b, c);

        scanner.close();
    }

    public static void giaiPhuongTrinhBacHai(double a, double b, double c) {
        if (a == 0) {
            System.out.println("Đây là phương trình bậc nhất:");
            // Sử dụng lại phương thức từ Bai1
            Bai1.giaiPhuongTrinhBacNhat(b, c);
        } else {
            double delta = b * b - 4 * a * c;

            if (delta < 0) {
                System.out.println("Phương trình vô nghiệm");
            } else if (delta == 0) {
                double x = -b / (2 * a);
                System.out.println("Phương trình có nghiệm kép: x = " + x);
            } else {
                double x1 = (-b + Math.sqrt(delta)) / (2 * a);
                double x2 = (-b - Math.sqrt(delta)) / (2 * a);
                System.out.println("Phương trình có 2 nghiệm phân biệt:");
                System.out.println("x1 = " + x1);
                System.out.println("x2 = " + x2);
            }
        }
    }
}
