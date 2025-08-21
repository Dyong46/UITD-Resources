package com.uitd.onTap;

import java.util.HashMap;
import java.util.Map;

public class DeQuy {
    public static void main(String[] args) {
        int n = 5; // Ví dụ với n = 5
        System.out.println("Giai thừa của " + n + " là: " + giaiThua(n));

        System.out.println("2^" + n + " là: " + powOf2(n));

        int m = 10;
        System.out.println("Số chữ số của " + n + " là: " + countDigits(m));

        Map<Integer, String> user = new HashMap<>();
        user.put(20, "Duong");
        user.put(21, "20");
        System.out.println(user.get(20)); // Duong
        System.out.println(user.get(21)); // 20
    }

    // Hàm tính giai thừa sử dụng đệ quy
    // n = 5
    public static int giaiThua(int n) {
        if (n == 0 || n == 1) {
            return 1; // Giai thừa của 0 và 1 là 1
        } else {
            return n * giaiThua(n - 1); // Công thức đệ quy
            // 5*4*3*2*1
        }
    }

    private static int powOf2(int n) {
        if (n == 0) {
            return 1; // 2^0 = 1
        } else {
            return 2 * powOf2(n - 1); // Công thức đệ quy
        }
    }

    private static int countDigits(int n) {
        if (n < 10) {
            return 1;
        }

        if(n > 0) {
            return 1 + countDigits(n / 10);
            // B1: 1 + countDigits(1) = 1
        }
        return 0;
    }
}
