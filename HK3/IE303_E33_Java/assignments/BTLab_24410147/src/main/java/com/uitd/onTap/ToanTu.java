package com.uitd.onTap;

public class ToanTu {
    public static void main(String[] args) {
        // Toán tử số học
        int a = 10;
        int b = 5;

        System.out.println("Tổng: " + (a + b)); // Cộng
        System.out.println("Hiệu: " + (a - b)); // Trừ
        System.out.println("Tích: " + (a * b)); // Nhân
        System.out.println("Thương: " + (a / b)); // Chia
        System.out.println("Chia lấy dư: " + (a % b)); // Chia lấy dư

        // Toán tử so sánh
        System.out.println("a > b: " + (a > b)); // Lớn hơn
        System.out.println("a < b: " + (a < b)); // Nhỏ hơn
        System.out.println("a >= b: " + (a >= b)); // Lớn hơn hoặc bằng
        System.out.println("a <= b: " + (a <= b)); // Nhỏ hơn hoặc bằng
        System.out.println("a == b: " + (a == b)); // Bằng
        System.out.println("a != b: " + (a != b)); // Khác

        // Toán tử logic
        boolean x = true;
        boolean y = false;

        System.out.println("x && y: " + (x && y)); // AND
        System.out.println("x || y: " + (x || y)); // OR
        System.out.println("!x: " + (!x)); // NOT

        // Toán tử gán
        int c = 20;
        c += 5; // Tương đương với c = c + 5;
        System.out.println("Giá trị của c sau khi gán: " + c);

        // Toán tử tăng giảm
        int d = 10;
        System.out.println("Giá trị của d trước khi tăng: " + d); // d = 10
        d++; // Tăng d lên 1 -> Tang khi nao
        System.out.println("Giá trị của d sau khi tăng: " + d); // d = 11

        System.out.println("d lan 1: " + d++); // d = ? 11
        System.out.println("d lan 1.2: " + d); // d = ? 12

        System.out.println("d lan 2" + ++d);
        System.out.println("d lan 2.2" + d);
    }
}
