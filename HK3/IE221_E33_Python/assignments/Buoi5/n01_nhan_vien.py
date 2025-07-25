class NhanVien:
    so_nv = 0
    def __init__(self, ma_nv, ho_ten, luong_cb, so_ng):
        self.ma_nv = ma_nv
        self.ho_ten = ho_ten
        self.luong_cb = luong_cb
        self.so_ng = so_ng
        self.luong_ht = 0

        NhanVien.so_nv += 1

    def __str__(self):
        return str([self.ma_nv, self.ho_ten, self.luong_cb, self.so_ng, self.luong_ht])

    def in_nv(self):
        print("Thông tin nhân viên: ")
        print("\tMã nhân viên: ", self.ma_nv)
        print("\tHọ tên: ", self.ho_ten)
        print("\tLương cơ bản: ", self.luong_cb)
        print("\tLương hàng tháng: ", self.luong_ht)
        print("\tSố ngày làm việc: ", self.so_ng)

    def tinh_luong_ht(self):
        self.luong_ht = self.luong_cb + self.so_ng*180_000
        return self.luong_ht

    @classmethod
    def in_so_nv(cls):
        print(cls.so_nv)
        print(NhanVien.so_nv)

    @staticmethod
    def tinh_thue_tn(tien):
        print("Thuế thu nhập cá nhân là: ", tien * 0.1)


if __name__ == '__main__':
    nv = NhanVien(123, 'Nguyễn văn A', 8_000_000, 23)
    nv.in_nv()
    nv.tinh_luong_ht()
    nv.in_nv()

    print(nv)

    nv2 = NhanVien(124,'Nguyễn Văn B', 7_000_000, 25)

    #print(nv.so_nv)
    #print(nv2.so_nv)
    #print(NhanVien.so_nv)

    nv.in_so_nv()

    NhanVien.tinh_thue_tn(19_000_000)


