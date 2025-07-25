package com.uitd.onTap;

public class Mang {
    public static void main(String[] args) {
        // Khởi tạo mảng
//        int[] mangSoNguyen = {1, 2, 3, 4, 5};
//
//        // In các phần tử của mảng
//        System.out.println("Các phần tử trong mảng:");
//        for (int i = 0; i < mangSoNguyen.length; i++) {
//            System.out.println("Phần tử tại chỉ số " + i + ": " + mangSoNguyen[i]);
//        }
//
//        // Tính tổng các phần tử trong mảng
//        int tong = 0;
//        for (int so : mangSoNguyen) {
//            tong += so;
//        }
//        System.out.println("Tổng các phần tử trong mảng: " + tong);

        int[][] mangHaiChieu = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        mangHaiChieu[0][0] = 1;

        mangHaiChieu[0][0] = 1;

        for(int i=0; i < 3; i++)
        {
            for(int j=0; j < 3; j++){
                System.out.println("Phần từ tại dòng " + i + ", cột " + j + " la: " + mangHaiChieu[i][j] );
            }
        }

        for(int i = 0; i < mangHaiChieu.length; i++) {
            for(int j = 0; j < mangHaiChieu[i].length; j++) {
                System.out.print(mangHaiChieu[i][j] + " ");
            }
            System.out.println(); // Xuống dòng sau khi in mỗi hàng
        }

//        int[][] mangHaiChieu = {
//                {1, 2, 3},
//                {4, 5, 6},
//                {7, 8, 9}
//        };
        for(int[] hang : mangHaiChieu) {
            for (int cot : hang) {
                System.out.print(cot + " ");
            }
            System.out.println(); // Xuống dòng sau khi in mỗi hàng

        }

        // In mảng hai chiều
        int sum = 0;
        for(int i = 0; i < mangHaiChieu.length ; i++)
        {
            for(int j = 0; j < mangHaiChieu[i].length; j++){
                sum += mangHaiChieu[i][j];
            }
            System.out.println("Tổng là" + sum);
        }
    }
}
