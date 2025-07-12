package com.uitd.lab1;

import java.util.Scanner;

public class Bai4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Nhap a: ");
        double a = scanner.nextDouble();

        System.out.print("Nhap b: ");
        double b = scanner.nextDouble();

        System.out.print("Nhap c: ");
        double c = scanner.nextDouble();

        double denta = Math.pow(b, 2) - 4 * a * c;
        double sqrtDenta = Math.sqrt(Math.abs(denta));

        System.out.printf("Denta: %.2f%n", denta);
    }
}
