package com.uitd.onTap;

public class KieuDuLieu extends Ham {
    public static void main(String[] args) {
        // Kiểu dữ liệu nguyên thủy
        int a = 10; // Kiểu số nguyên
        double b = 20.5; // Kiểu số thực
        char c = 'A'; // Kiểu ký tự
        boolean d = true; // Kiểu logic

        int[] ac = {1, 2, 3, 4, 5}; // Mảng kiểu số nguyên





        // In ra các giá trị
        System.out.println("Giá trị của a: " + a);
        System.out.println("Giá trị của b: " + b);
        System.out.println("Giá trị của c: " + c);
        System.out.println("Giá trị của d: " + d);

        // Kiểu dữ liệu tham chiếu
        String e = "Hello, World!"; // Kiểu chuỗi
        Integer f = 100; // Kiểu đối tượng Integer
        Double g = 50.5; // Kiểu đối tượng Double
        Boolean h = false; // Kiểu đối tượng Boolean



        int hang = 3, cot = 3;
        int[][] mang2chieu =
                {
                    {1, 2, 3}, // 0
                    {4, 5, 6}, // 1
                    {7, 8, 9}  // 2
                };

        int sum = 0; // 3
        for(int i = 0; i < hang; i++) {
            for(int j = 0; j < cot; j++) {
                sum += mang2chieu[i][j];
                sum = sum + mang2chieu[i][j]; // Cộng dồn giá trị của từng phần tử
            }
        }



        /*
        Step 1:
            i = 0, j = 0 -> sum = 0 + 1 = 1
        Step 2:
            i = 0, j = 1 -> sum = 1 + 2 = 3
        Step 3:
            i = 0, j = 2 -> sum = 3 + 3 = 6
        Step 4:
            i = 0, j = 3 -> sum = 6 + 4 = 10
        Step 4:
            i = 0, j = 4 -> j = cot = 4, nên kết thúc vòng lặp j
        Step 5:
            i = 1, j = 0 -> sum = 10 + 4 = 14
        * */
        System.out.println("Giá trị tổng của mảng 2 chiều là: " + sum);
    }
}
