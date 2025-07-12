package com.uitd.lab3;

import java.util.Scanner;

public class Bai2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== BÀI 2: IN BẢNG CỬU CHƯƠNG ===");
        System.out.print("Nhập số bạn muốn in bảng cửu chương: ");
        int number = scanner.nextInt();
        inBangCuuchuong(number);
    }

    public static void inBangCuuchuong(int number) {
        System.out.println("Bảng cửu chương của " + number + ":");
        for (int i = 1; i <= number; i++) {
            for(int j = 1; j <= 10; j++) {
                System.out.printf("%d x %d = %d\n", i, j, i * j);
            }
            System.out.println();
        }
    }
}
