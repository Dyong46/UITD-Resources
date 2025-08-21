class NVVanPhong:
    def __init__(self, ma_nv, ho_ten, luong_cb, so_ng):
        self.ma_nv = ma_nv
        self.ho_ten = ho_ten
        self.luong_cb = luong_cb
        self.so_ng = so_ng
        self.luong_ht = 0

    def tinh_luong(self):
        self.luong_ht = self.luong_cb + self.so_ng * 150_000

    def in_nv_vp(self):
        return str([self.ma_nv, self.ho_ten, self.luong_cb, self.so_ng, self.luong_ht])

class NVBanHang:
    def __init__(self, ma_nv, ho_ten, luong_cb, so_sp):
        self.ma_nv = ma_nv
        self.ho_ten = ho_ten
        self.luong_cb = luong_cb
        self.so_sp = so_sp
        self.luong_ht = 0

    def tinh_luong(self):
        self.luong_ht = self.luong_cb + self.so_sp * 18_000

    def in_nv_bh(self):
        return str([self.ma_nv, self.ho_ten, self.luong_cb, self.so_sp, self.luong_ht])

class CongTy:
    def __init__(self, ma_ct, ten_ct):
        self.ma_ct = ma_ct
        self.ten_ct = ten_ct
        self.ds_nv = []

    def init_ds_nv(self):
        """"""
        nv1 = NVVanPhong(123, 'Nguyen Van A', 6_000_000, 23)
        nv2 = NVBanHang(124, 'Nguyen Van B', 7_000_000, 25)

        self.ds_nv.append(nv1)
        self.ds_nv.append(nv2)
        self.ds_nv.append(NVVanPhong(125, 'Nguyen Van C', 5_500_000, 24))

    def print_ds_nv(self):
        print(self.ds_nv)
        """"""
        for nv in self.ds_nv:
            if isinstance(nv, NVVanPhong):
                print(nv.in_nv_vp())

            if isinstance(nv, NVBanHang):
                print(nv.in_nv_bh())

    def tinh_luong_ht(self):
        """"""
        for nv in self.ds_nv:
            nv.tinh_luong()

    def tim_nv_theo_ma(self, ma_nv):
        """"""
        for nv in self.ds_nv:
            if nv.ma_nv == ma_nv:
                print(nv.in_nv_vp())
        print("Không tìm thấy nhân viên.")

    def nv_luong_cao_nhat(self):
        max_nv = self.ds_nv[0]
        for nv in self.ds_nv[1:]:
            if nv.luong_ht > max_nv.luong_ht:
                max_nv = nv
        print("Nhân viên có lương cao nhất:")
        print(max_nv.in_nv_vp())

    def nv_bh_luong_thap_nhat(self):
        list_nv_bh = [nv for nv in self.ds_nv if isinstance(nv, NVBanHang)]
        if not list_nv_bh:
            print("Không có nhân viên bán hàng.")
            return
        min_nv = list_nv_bh[0]
        for nv in list_nv_bh[1:]:
            if nv.luong_ht < min_nv.luong_ht:
                min_nv = nv
        print("Nhân viên bán hàng có lương thấp nhất:")
        print(min_nv.in_nv_bh())

if __name__ == '__main__':
    ct = CongTy('CITD', 'TT')

    ct.init_ds_nv()

    print("\n=== Danh sách nhân viên ===")
    ct.print_ds_nv()

    print("\n=== Tinh luong hang thang ===")
    ct.tinh_luong_ht()

    print("\n=== Danh sách nhân viên ===")
    ct.print_ds_nv()

    print("\n=== Tìm nhân viên theo mã 123 ===")
    ct.tim_nv_theo_ma(123)

    print("\n=== Nhân viên lương cao nhất ===")
    ct.nv_luong_cao_nhat()

    print("\n=== Nhân viên bán hàng lương thấp nhất ===")
    ct.nv_bh_luong_thap_nhat()


