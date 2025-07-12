package com.uitd.lab1;

import java.util.Scanner;

public class Bai3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Nhap canh: ");
        double side = scanner.nextDouble();

        double area = Math.pow(side, 3);

        System.out.printf("Dien tich hinh lap phuong: %.2f%n", area);
    }
}
