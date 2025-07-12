package com.uitd.lab2;

import java.util.Scanner;

public class Bai4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Chọn bài tập muốn chạy:");
        System.out.println("1. Bài 1 - Phương trình bậc nhất");
        System.out.println("2. Bài 2 - Phương trình bậc hai");
        System.out.println("3. Bài 3 - Tính tiền điện");
        System.out.println("4. Kết thúc chương trình");
        System.out.print("Nhập lựa chọn (1-4): ");

        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                Bai1.main(new String[]{});
                break;
            case 2:
                Bai2.main(new String[]{});
                break;
            case 3:
                Bai3.main(new String[]{});
                break;
            case 4:
                System.out.println("Kết thúc chương trình.");
                break;
            default:
                System.out.println("Lựa chọn không hợp lệ!");
        }

        scanner.close();
    }
}
