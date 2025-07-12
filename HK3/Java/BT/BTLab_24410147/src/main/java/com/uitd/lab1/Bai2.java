package com.uitd.lab1;

import java.util.Scanner;

public class Bai2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Nhap chieu dai: ");
        double length = scanner.nextDouble();

        System.out.print("Nhap chieu rong: ");
        double width = scanner.nextDouble();

        double area = length * width;
        double perimeter = 2 * (length + width);
        double minSide = Math.min(length, width);

        System.out.printf("Dien tich: %.2f, Chu vi: %.2f, Canh nho nhat: %.2f%n", area, perimeter, minSide);
    }
}
