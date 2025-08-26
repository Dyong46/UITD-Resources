from abc import ABC, abstractmethod

class AbsNhanVien(ABC):
    @abstractmethod
    def tinh_luong_ht(self):
        pass

class NhanVien(AbsNhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb):
        self._ma_nv = ma_nv
        self._ho_ten = ho_ten
        self._luong_cb = luong_cb
        self._luong_ht = 0

    def in_nv(self):
        print([self._ma_nv, self._ho_ten, self._luong_cb, self._luong_ht], end=" ")

    def __str__(self):
        return str([self._ma_nv, self._ho_ten, self._luong_cb, self._luong_ht])

    def tinh_luong_ht(self):
        pass

class NVVanPhong(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_ng):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_ng = so_ng

    def in_nv(self):
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_ng, self._luong_ht], end=" ")

    def tinh_luong_ht(self):
        self._luong_ht = self._luong_cb + self.__so_ng * 180_000
        return self._luong_ht

class NVBanHang(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_sp):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_sp = so_sp

    def in_nv(self):
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_sp, self._luong_ht], end=" ")

    def tinh_luong_ht(self):
        self._luong_ht = self._luong_cb + self.__so_sp * 15_000
        return self._luong_ht

class Luong:
    def __init__(self, ma_ct, ten_ct):
        self._ma_ct = ma_ct
        self.__ten_ct = ten_ct
        self.__ds_nv = []

    @property
    def ds_nv(self):
        return self.__ds_nv

    def init_ds_nv(self):
        nv1 = NVVanPhong(123, 'Nguyen Van A', 6_000_000, 23)
        nv2 = NVBanHang(124, 'Nguyen Van B', 7_000_000, 256)
        nv3 = NVVanPhong(125, 'Nguyen Van C', 5_500_000, 25)
        self.__ds_nv.extend([nv1, nv2, nv3])
        return len(self.__ds_nv)

    def print_ds_nv(self):
        for nv in self.__ds_nv:
            nv.in_nv()
            print()

    def tinh_luong_ht(self):
        for nv in self.__ds_nv:
            nv.tinh_luong_ht()

    def tim_nv_theo_ma_nv(self, ma_nv):
        for nv in self.__ds_nv:
            if nv._ma_nv == ma_nv:
                return nv
        return None

    def tim_nv_theo_ma_nv_v2(self, _ma_nv):
        return list(filter(lambda nv: nv._ma_nv == _ma_nv, self.__ds_nv))

    def tim_luong_ht_max(self):
        if not self.__ds_nv:
            return None
        luong_ht_max = self.__ds_nv[0]._luong_ht
        for nv in self.__ds_nv:
            if nv._luong_ht > luong_ht_max:
                luong_ht_max = nv._luong_ht
        return luong_ht_max

    # 6. Cập nhật lương cơ bản theo mã NV
    def cap_nhat_luong_cb(self, ma_nv, luong_cb_moi):
        nv = next(filter(lambda x: x._ma_nv == ma_nv, self.__ds_nv), None)
        if nv:
            nv._luong_cb = luong_cb_moi
            return True
        return False

    # 7. Cập nhật số ngày làm của NV văn phòng theo mã NV
    def cap_nhat_so_ngay_nvvp(self, ma_nv, so_ngay_moi):
        nv = next(filter(lambda x: isinstance(x, NVVanPhong) and x._ma_nv == ma_nv, self.__ds_nv), None)
        if nv:
            nv._NVVanPhong__so_ng = so_ngay_moi
            return True
        return False

    # 8. Tính tổng lương hằng tháng của công ty
    def tong_luong_thang(self):
        return sum(map(lambda nv: nv._luong_ht, self.__ds_nv))

    # 9. Tìm NV có lương cơ bản cao nhất
    def nv_luong_cb_max(self):
        return max(self.__ds_nv, key=lambda nv: nv._luong_cb)

    # 10. Tìm NV bán hàng có lương hằng tháng thấp nhất
    def nv_banhang_luong_min(self):
        nv_bh = list(filter(lambda nv: isinstance(nv, NVBanHang), self.__ds_nv))
        return min(nv_bh, key=lambda nv: nv._luong_ht) if nv_bh else None

    # 11. Sắp xếp NV giảm dần theo lương cơ bản
    def sap_xep_giam_theo_luong_cb(self):
        self.__ds_nv = sorted(self.__ds_nv, key=lambda nv: nv._luong_cb, reverse=True)


if __name__ == '__main__':
    print("\nTest: 1. Khởi tạo dữ liệu:")
    ct = Luong(ma_ct="CID", ten_ct="TT 1")
    so_nv = ct.init_ds_nv()
    print("\t+ Kết quả:", so_nv, "nhân viên")

    print("\nTest: 2. In danh sách NV (chưa tính lương):")
    ct.print_ds_nv()

    print("\nTest: 3. Tính lương các NV:")
    ct.tinh_luong_ht()
    ct.print_ds_nv()

    print("\nTest: 4. Tìm NV theo mã:")
    print("\t+ Tìm 123:", ct.tim_nv_theo_ma_nv(123))
    print("\t+ Tìm 133:", ct.tim_nv_theo_ma_nv(133))
    print("\t+ Tìm v2 (123):", ct.tim_nv_theo_ma_nv_v2(123))

    print("\nTest: 5. Lương cao nhất:")
    print("\t+ Kết quả =", ct.tim_luong_ht_max())

    print("\nTest: 6. Cập nhật lương cơ bản NV mã 124:")
    print("\t+ Trước:", end=" "); ct.print_ds_nv()
    ct.cap_nhat_luong_cb(124, 8_000_000)
    ct.tinh_luong_ht()
    print("\t+ Sau:", end=" "); ct.print_ds_nv()

    print("\nTest: 7. Cập nhật số ngày làm của NVVP mã 125:")
    ct.cap_nhat_so_ngay_nvvp(125, 28)
    ct.tinh_luong_ht()
    ct.print_ds_nv()

    print("\nTest: 8. Tổng lương hằng tháng của công ty:")
    print("\t+ Kết quả =", ct.tong_luong_thang())

    print("\nTest: 9. NV có lương cơ bản cao nhất:")
    print("\t+ Kết quả =", end=" "); ct.nv_luong_cb_max().in_nv(); print()

    print("\nTest: 10. NV bán hàng có lương hằng tháng thấp nhất:")
    print("\t+ Kết quả =", end=" "); ct.nv_banhang_luong_min().in_nv(); print()

    print("\nTest: 11. Sắp xếp NV giảm dần theo lương cơ bản:")
    ct.sap_xep_giam_theo_luong_cb()
    ct.print_ds_nv()

