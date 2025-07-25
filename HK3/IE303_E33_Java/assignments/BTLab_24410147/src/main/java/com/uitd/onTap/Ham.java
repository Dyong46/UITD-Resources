package com.uitd.onTap;

public class Ham {
    public static void main(String[] args) {
        // Gọi hàm tính tổng
        int a = 5;
        int b = 10;
        int tong = tinhTong(a, b);
        System.out.println("Tổng của " + a + " và " + b + " là: " + tong);

        // Gọi hàm kiểm tra số chẵn lẻ
        int so = 7;
        String ketQua = kiemTraChanLe(so);
        System.out.println("Số " + so + " là: " + ketQua);
    }

    // Hàm tính tổng hai số
    static int tinhTong(int x, int y) {
        return x+y;
    }

//    Pham vi truy cap ->
//    public: Phạm vi truy cập công khai, có thể truy cập từ bất kỳ đâu trong chương trình.
//    protected: Phạm vi truy cập bảo vệ, có thể truy cập từ cùng một gói hoặc từ các lớp con.
//    default: Phạm vi truy cập mặc định, chỉ có thể truy cập trong cùng một gói (package).
//    private: Phạm vi truy cập riêng tư, chỉ có thể truy cập trong cùng một class.

    // static: Phạm vi truy cập tĩnh, có thể truy cập mà không cần tạo đối tượng của lớp.
    // final: Biến hoặc phương thức không thể thay đổi giá trị hoặc không thể ghi đè trong lớp con.

    // Hàm kiểm tra số chẵn hay lẻ
    static  String kiemTraChanLe(int so) {
        if (so % 2 == 0) {
            return "Chẵn";
        } else {
            return "Lẻ";
        }
    }

}
