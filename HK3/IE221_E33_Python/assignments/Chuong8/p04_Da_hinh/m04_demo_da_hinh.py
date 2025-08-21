class NhanVien:
    def __init__(self, ma_nv, ho_ten, luong_cb):
        self._ma_nv = ma_nv
        self._ho_ten = ho_ten
        self._luong_cb = luong_cb
        self._luong_ht = None

    def in_nv(self):
        print("NV: ", [self._ma_nv, self._ho_ten, self._luong_cb, self._luong_ht], end=" ")


class NVVanPhong(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_ng):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_ng = so_ng

    def in_nv(self):
        """Over right absolute"""
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_ng, self._luong_ht], end=" ")

    def in_nv_vp(self):
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_ng, self._luong_ht], end=" ")

    def tinh_luong_ht_nv_vp(self):
        self._luong_ht = self._luong_cb + self.__so_ng * 180_000
        return self._luong_ht


class NVBanHang(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_sp):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_sp = so_sp

    def in_nv(self):
        """Ghi de hoan toan"""
        print([self.__so_sp, self._luong_cb, self._luong_ht, self.__so_sp, self._luong_ht], end=" ")

    def in_nv_bh(self):
        print([self.__so_sp, self._luong_cb, self._luong_ht, self.__so_sp, self._luong_ht], end=" ")

    def tinh_luong_ht_nv_bh(self):
        self._luong_ht = self._luong_cb + self.__so_sp * 25_000

if __name__ == '__main__':
    nv1 = NVVanPhong(123, 'Nguyen Van A', 6_000_000, 23)
    nv2 = NVBanHang(124, 'Nguyen Van B', 7_000_000, 256)

    nv1.tinh_luong_ht_nv_vp()
    nv2.tinh_luong_ht_nv_bh()

    ds = [nv1, nv2]

