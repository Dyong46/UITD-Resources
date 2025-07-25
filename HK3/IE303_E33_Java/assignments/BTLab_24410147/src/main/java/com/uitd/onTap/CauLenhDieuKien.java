package com.uitd.onTap;


public class CauLenhDieuKien {

    public static void main(String[] args) {
        int a = 10;
        int b = 20;

        // Câu lệnh if
        if (a > b) {
            System.out.println("a lớn hơn b");
        } else if (a < b) {
            System.out.println("a nhỏ hơn b");
        } else {
            System.out.println("a bằng b");
        }

        // Câu lệnh switch
        int day = 3;
        switch (day) {
            case 1:
                System.out.println("Thứ Hai");
                break;
            case 2:
                System.out.println("Thứ Ba");
                break;
            case 3:
                System.out.println("Thứ Tư");
                break;
            default:
                System.out.println("Ngày không hợp lệ");
                break;
        }
    }


}
