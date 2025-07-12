package com.uitd.lab3;

import java.util.Scanner;

public class Bai3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== BÀI 3: XỬ LÝ MẢNG SỐ NGUYÊN ===");
        System.out.print("Nhập số phần tử của mảng: ");
        int n = scanner.nextInt();

        if (n <= 0) {
            System.out.println("Số phần tử không hợp lệ!");
            return;
        }

        int[] mang = new int[n];

        // Nhập mảng
        System.out.println("Nhập " + n + " phần tử:");
        for (int i = 0; i < n; i++) {
            System.out.print("Phần tử thứ " + (i + 1) + ": ");
            mang[i] = scanner.nextInt();
        }

        // Xuất mảng ban đầu
        System.out.println("\nMảng ban đầu:");
        xuatMang(mang);

        // Sắp xếp mảng
        java.util.Arrays.sort(mang);
        System.out.println("\nMảng sau khi sắp xếp:");
        xuatMang(mang);

        // Tìm phần tử nhỏ nhất
        int min = timMin(mang);
        System.out.println("\nPhần tử nhỏ nhất: " + min);

        double tbcChiaHet3 = tinhTrungBinhChiaHet3(mang);
        if (tbcChiaHet3 != -1) {
            System.out.println("Trung bình cộng các phần tử chia hết cho 3: " + tbcChiaHet3);
        } else {
            System.out.println("Không có phần tử nào chia hết cho 3!");
        }

        scanner.close();
    }

    public static void xuatMang(int[] mang) {
        for (int i = 0; i < mang.length; i++) {
            System.out.print(mang[i] + " ");
        }
        System.out.println();
    }

    public static int timMin(int[] mang) {
        int min = mang[0];
        for (int i = 1; i < mang.length; i++) {
            min = Math.min(min, mang[i]);
        }
        return min;
    }

    public static double tinhTrungBinhChiaHet3(int[] mang) {
        int tong = 0;
        int dem = 0;

        for (int i = 0; i < mang.length; i++) {
            if (mang[i] % 3 == 0) {
                tong += mang[i];
                dem++;
            }
        }

        if (dem == 0) {
            return -1;
        }

        return (double) tong / dem;
    }
}
